#include<stddef.h>
#include "functions.h"
#include "macro_defs.h"

unsigned int char_count(char *line, size_t line_length, char *search)
{
	unsigned int char_index;
	for (char_index = 0; char_index < line_length; char_index++) {
		char_index = char_index;
	}
	UNUSED(line);
	UNUSED(search);
	return 1;
}
