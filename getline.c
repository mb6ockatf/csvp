#include "macro_defs.h"
#undef flockfile
#undef funlockfile
#define flockfile(x) ((void) 0)
#define funlockfile(x) ((void) 0)
#define getc_maybe_unlocked(stream) getc(stream)

void static alloc_failed(void)
{
#if defined _WIN32 && ! defined __CYGWIN__
	errno = ENOMEM;
#endif
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t result;
	size_t current_length = 0;
	if (lineptr == NULL || n == NULL || stream == NULL) {
		errno = EINVAL;
		return -1;
	}
	flockfile(stream);
	if (*lineptr == NULL || *n == 0) {
		*n = 120;
		char *new_lineptr = (char *) realloc(*lineptr, *n);
		if (new_lineptr == NULL) {
			alloc_failed();
			result = -1;
			goto unlock_return;
		}
		*lineptr = new_lineptr;
	}
	for (;;) {
		int character = getc_maybe_unlocked(stream);
		if (character == EOF) {
			result = -1;
			break;
		}
		if (current_length + 1 >= *n) {
			size_t needed_max = SIZE_MAX;
			size_t needed = 2 * *n + 1;
			char *new_lineptr;
			if (needed_max < needed) needed = needed_max;
			if (current_length + 1 >= needed) {
				result = -1;
				errno = EOVERFLOW;
				goto unlock_return;
			}
			new_lineptr = (char *) realloc(*lineptr, needed);
			if (new_lineptr == NULL) {
				alloc_failed();
				result = -1;
				goto unlock_return;
			}
			*lineptr = new_lineptr;
			*n = needed;
		}
		(*lineptr)[current_length] = character;
		current_length++;
		if (character == '\n') break;
	}
	(*lineptr)[current_length] = '\0';
	result = current_length ? current_length : result;
unlock_return:
	funlockfile(stream);
	return result;
}

