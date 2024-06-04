#include "buffer.h"
#include "util.h"

#include <err.h>
#include <inttypes.h>
#include <stdlib.h>

struct buffer {
    uint8_t lbuf[BUFFER_SIZE];
    uint8_t rbuf[BUFFER_SIZE];
    size_t input;
    size_t fence;
    int ifstream;
};

static inline uint8_t *which_buffer(struct buffer *buf) {
    return buf->input >= BUFFER_SIZE ? buf->rbuf : buf->lbuf;
}

struct buffer *buffer_create(int ifstream) {
    struct buffer *buf = (struct buffer *) calloc(1, sizeof(struct buffer));
    if (!buf) {
        return NULL;
    }

    buf->ifstream = ifstream;
    return buf;
}

ssize_t buffer_fill(struct buffer *buf) {
    return read_bytes(buf->ifstream, which_buffer(buf), BUFFER_SIZE);
}

char buffer_nextchar(struct buffer *buf) {
    if (buf->input % BUFFER_SIZE == 0) {
        buffer_fill(buf);
        buf->fence = (buf->input + BUFFER_SIZE) % (2 * BUFFER_SIZE);
    }
    
    char current = which_buffer(buf)[buf->input % BUFFER_SIZE];
    buf->input = (buf->input + 1) % (2 * BUFFER_SIZE);

    return current;
}

void buffer_rollback(struct buffer *buf) {
    if (buf->input == buf->fence) {
        warnx("Buffer rollback error occured.");
    }

    buf->input = (buf->input - 1) % (2 * BUFFER_SIZE);
}

