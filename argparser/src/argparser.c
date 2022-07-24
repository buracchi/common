#include <buracchi/common/argparser/argparser.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <buracchi/common/utilities/try.h>

#include "struct_argparser.h"

static struct cmn_argparser_argument help_arg = {
	.flag = "h",
	.long_flag = "help",
	.action = CMN_ARGPARSER_ACTION_HELP,
	.help = "show this help message and exit"
};

extern cmn_argparser_t cmn_argparser_init() {
	cmn_argparser_t this;
	try(this = malloc(sizeof * this), NULL, fail);
	this->program_name = NULL;
	this->usage = NULL;
	this->description = NULL;
	this->arguments_number = 1;
	try(this->arguments = malloc(sizeof * this->arguments), NULL, fail2);
	memcpy(&(this->arguments[0]), &help_arg, sizeof * this->arguments);
	return this;
fail2:
	free(this);
fail:
	return NULL;
}

extern int cmn_argparser_destroy(cmn_argparser_t this) {
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
	free(argparser->program_name);
	if (program_name) {
		try(argparser->program_name = malloc(strlen(program_name) + 1), NULL, fail);
		strcpy(argparser->program_name, program_name);
	}
	else {
		argparser->program_name = NULL;
	}
	return 0;
fail:
	return 1;
}

extern int cmn_argparser_set_usage(cmn_argparser_t argparser, const char* usage) {
	free(argparser->usage);
	if (usage) {
		try(argparser->usage = malloc(strlen(usage) + 1), NULL, fail);
		strcpy(argparser->usage, usage);
	}
	else {
		argparser->usage = NULL;
	}
	return 0;
fail:
	return 1;

}

extern int cmn_argparser_set_description(cmn_argparser_t argparser, const char* description) {
	free(argparser->description);
	if (description) {
		try(argparser->description = malloc(strlen(description) + 1), NULL, fail);
		strcpy(argparser->description, description);
	}
	else {
		argparser->description = NULL;
	}
	return 0;
fail:
	return 1;
}

extern int cmn_argparser_add_argument_action_store_cstr(cmn_argparser_t argparser, char** result, struct cmn_argparser_argument argument) {
	argparser->arguments_number++;
	argument.action = CMN_ARGPARSER_ACTION_STORE;
	argument.type = CMN_ARGPARSER_CSTR;
	argument.result = (void**)result;
	struct cmn_argparser_argument* arguments_reallocated_address;
	try(arguments_reallocated_address = realloc(argparser->arguments, sizeof * argparser->arguments * argparser->arguments_number), NULL, fail);
	argparser->arguments = arguments_reallocated_address;
	memcpy(&(argparser->arguments[argparser->arguments_number - 1]), &argument, sizeof * argparser->arguments);
	return 0;
fail:
	return 1;
}
