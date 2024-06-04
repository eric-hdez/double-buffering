#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef __UTIL_H__
#define __UTIL_H__

ssize_t read_bytes(int fileno, uint8_t *buf, size_t nbytes);

#endif
