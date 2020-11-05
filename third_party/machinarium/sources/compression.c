//
// Created by Daniil Zakhlystov on 10/27/20.
//
#include <machinarium.h>
#include <machinarium_private.h>

int
mm_compression_writev(mm_io_t *io, struct iovec *iov, int n, size_t *processed)
{
	int size     = mm_iov_size_of(iov, n);
	char *buffer = malloc(size);
	if (buffer == NULL) {
		errno = ENOMEM;
		return -1;
	}
	mm_iovcpy(buffer, iov, n);

	int rc;
	rc = zpq_write(io->zpq_stream, buffer, size, processed);
	free(buffer);
	return rc;
}

int
mm_compression_read_pending(mm_io_t *io)
{
    return zpq_buffered_rx(io->zpq_stream);
}

int
mm_compression_write_pending(mm_io_t *io)
{
    return zpq_buffered_tx(io->zpq_stream);
}

MACHINE_API
char machine_compression_choose_alg(char *client_compression_algorithms) {
    /*
     * If client request compression, it sends list of supported
     * compression algorithms. Each compression algorirthm is idetified
     * by one letter ('f' - Facebook zsts, 'z' - xlib)
     */

    // odyssey supported compression algos
    char server_compression_algorithms[ZPQ_MAX_ALGORITHMS];

    // chosen compression algo
    char compression_algorithm = ZPQ_NO_COMPRESSION;
    // char compression[6] = {'z',0,0,0,5,0}; /* message length = 5 */
    // int rc;

    /* Get list of compression algorithms, supported by server */
    zpq_get_supported_algorithms(server_compression_algorithms);

    /* Intersect lists */
    while (*client_compression_algorithms != '\0') {
        if (strchr(server_compression_algorithms,
                   *client_compression_algorithms)) {
            compression_algorithm = *client_compression_algorithms;
            break;
        }
        client_compression_algorithms += 1;
    }
	return compression_algorithm;
}
