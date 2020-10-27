//
// Created by Daniil Zakhlystov on 10/22/20.
//

#ifndef MM_COMPRESSION_H
#define MM_COMPRESSION_H

static inline int
mm_compression_is_active(mm_io_t *io)
{
    return io->zpq_stream != NULL;
}

int mm_compression_writev(mm_io_t *io, struct iovec *iov, int n, size_t *processed);

#endif // MM_COMPRESSION_H
