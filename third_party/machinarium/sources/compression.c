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
