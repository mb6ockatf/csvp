#include "macro_defs.h"
const char *cdates_version = "csvp 0.1";
const char *cdates_bug_address = "<mdddmmmm@ya.ru>";
static char doc[] = "csvp -- pretty-print csv to stdout";
static char args_doc[] = "FILEPATH";
/* static struct argp_option options[0] = {}; */
struct arguments {
	char *args[1];
};
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	switch (key) {
	case ARGP_KEY_ARG:
		if (state -> arg_num >= 1) argp_usage(state);
		arguments->args[state->arg_num] = arg;
		break;
	case ARGP_KEY_END:
		if (state -> arg_num < 1) argp_usage(state);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = {0, parse_opt, args_doc, doc, NULL, 0, 0};

int main(int argc, char **argv)
{
	struct arguments arguments;
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	char *FILENAME = arguments.args[0];
	if (access(FILENAME, F_OK) != 0) {
		printf("%s: file does not exist\n", FILENAME);
		return 2;
	}
	FILE *file_ptr = fopen(FILENAME, "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, file_ptr)) != -1) {
		printf("Retrieved line of length %zu:\n", read);
		printf("%s", line);
	}
	char myString[100];
	fgets(myString, 100, file_ptr);
	printf("%s\n", myString);
	fclose(file_ptr);
	return 0;
}
