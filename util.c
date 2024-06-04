#include "util.h"

ssize_t read_bytes(int fileno, uint8_t *buf, size_t nbytes) {
    ssize_t rbytes = 0;
    size_t total_bytes = 0;

    do {
        rbytes = read(fileno, buf + total_bytes, nbytes - total_bytes);
        total_bytes += rbytes;
    } while (total_bytes < nbytes && rbytes > 0 );

    return total_bytes;
}
