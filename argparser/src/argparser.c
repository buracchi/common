#include <buracchi/common/argparser/argparser.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <buracchi/common/containers/map/linked_list_map.h>
#include <buracchi/common/utilities/try.h>

#include "struct_argparser.h"

static struct cmn_argparser_argument help_arg = {
		.flag = "h",
		.long_flag = "help",
		.action = CMN_ARGPARSER_ACTION_HELP,
		.help = "show this help message and exit"
};

static int lexicographical_comparison(void* arg1, void* arg2, bool* result) {
	const char* _s1 = (const char*)arg1;
	const char* _s2 = (const char*)arg2;
	while (*_s1 && *_s2 && *(_s1++) == *(_s2++));
	*result = *_s1 == *_s2;
	return 0;
}

extern cmn_argparser_t cmn_argparser_init() {
	cmn_argparser_t this;
	try(this = malloc(sizeof * this), NULL, fail);
	this->program_name = NULL;
	this->usage = NULL;
	this->description = NULL;
	this->add_help = true;
	try(this->map = (cmn_map_t)cmn_linked_list_map_init(), NULL, fail2);
	cmn_map_set_key_comparer(this->map, &lexicographical_comparison);
	return this;
fail2:
	free(this);
fail:
	return NULL;
}

extern int cmn_argparser_destroy(cmn_argparser_t this) {
	try(cmn_map_destroy(this->map), 1, fail);
	free(this->arguments);
	free(this->program_name);
	free(this->description);
	free(this->usage);
	free(this);
	return 0;
fail:
	return 1;
}

extern int cmn_argparser_set_program_name(cmn_argparser_t argparser, const char* program_name) {
	try(argparser->program_name = malloc(strlen(program_name) + 1), NULL, fail);
	strcpy(argparser->program_name, program_name);
	return 0;
fail:
	return 1;
}

extern int cmn_argparser_set_usage(cmn_argparser_t argparser, const char* usage) {
	try(argparser->usage = malloc(strlen(usage) + 1), NULL, fail);
	strcpy(argparser->usage, usage);
	return 0;
fail:
	return 1;

}

extern int cmn_argparser_set_description(cmn_argparser_t argparser, const char* description) {
	try(argparser->description = malloc(strlen(description) + 1), NULL, fail);
	strcpy(argparser->description, description);
	return 0;
fail:
	return 1;
}

int cmn_argparser_add_arguments_with_size(cmn_argparser_t argparser, const struct cmn_argparser_argument* arguments, size_t arguments_number) {
	size_t i = 0;
	argparser->arguments_number = arguments_number + (argparser->add_help ? 1 : 0);
	try(argparser->arguments = malloc(sizeof * argparser->arguments * argparser->arguments_number), NULL, fail);
	if (argparser->add_help) {
		memcpy(&(argparser->arguments[i]), &help_arg, sizeof * argparser->arguments);
		i++;
	}
	for (; i < argparser->arguments_number; i++) {
		memcpy(&(argparser->arguments[i]), arguments, sizeof * argparser->arguments);
		arguments++;
	}
	// TODO: Check and throw error if: There are conflicts, ...
	return 0;
fail:
	return 1;
}
