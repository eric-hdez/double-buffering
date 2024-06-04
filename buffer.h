#include <sys/types.h>

#ifndef __BUFFER_H__
#define __BUFFER_H__

#define BUFFER_SIZE 4096

struct buffer;

struct buffer *buffer_create(int ifstream);

ssize_t buffer_fill(struct buffer *buf);

char buffer_nextchar(struct buffer *buf);

void buffer_rollback(struct buffer *buf);

#endif
