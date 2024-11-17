#ifndef GETLINE_H
#define GETLINE_H
#include "macro_defs.h"
/* Read up to (and including) a '\n' from stream into *LINEPTR (and
 * NUL-terminate it). *LINEPTR is a pointer returned from malloc (or NULL),
 * pointing to *N characters of space. It is realloc'ed as necessary. Returns
 * the number of characters read (not including the null terminator), or -1 on
 * error or EOF. */
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
#endif
