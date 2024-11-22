#include "macro_defs.h"

unsigned int char_count(char *line, size_t line_length, char *search)
{
	unsigned int char_index, counter = 0;
	for (char_index = 0; char_index < line_length; char_index++) {
		if (line[char_index] == *search) counter++;
	}
	return counter;
}
