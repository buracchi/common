#include <buracchi/common/argparser/argparser.h>

#include <ctype.h>
#include <libgen.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buracchi/common/utilities/try.h"
#include <buracchi/common/containers/list/linked_list.h>
#include <buracchi/common/utilities/strto.h>
#include <buracchi/common/utilities/utilities.h>

#include "struct_argparser.h"

static int parse_arg_n(cmn_argparser_t this, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links, size_t n);

static struct cmn_argparser_argument *match_arg(cmn_argparser_t this, size_t argc, char const *args, struct cmn_argparser_argument **argv_argument_links);

static int parse_action_store(cmn_argparser_t this, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links, size_t n, struct cmn_argparser_argument *argument);

static int parse_action_store_const(cmn_argparser_t this, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links, size_t n, struct cmn_argparser_argument *argument);

static int parse_action_help(cmn_argparser_t argparser);

static int handle_unrecognized_elements(cmn_argparser_t argparser, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links);

static int handle_required_missing_elements(cmn_argparser_t argparser, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links);

static int handle_optional_missing_elements(cmn_argparser_t this, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links);

static void convert_result(cmn_argparser_t argparser, struct cmn_argparser_argument *argument, char const *arg);

extern int print_usage(cmn_argparser_t argparser);

extern int cmn_argparser_parse_args1(cmn_argparser_t argparser) {
	return (cmn_argparser_parse_args3(argparser, (char **)argparser->sys_argv + 1, argparser->sys_argc - 1));
}

extern int cmn_argparser_parse_args3(cmn_argparser_t argparser, char *args[const], size_t args_size) {
	struct cmn_argparser_argument **argv_argument_links = NULL;
	try(argv_argument_links = malloc(args_size * sizeof(struct cmn_argparser_argument *)), NULL, fail);
	memset(argv_argument_links, 0, args_size * sizeof(struct cmn_argparser_argument *));
	for (size_t i = 0; i < args_size; i++) {
		if (parse_arg_n(argparser, args_size, args, argv_argument_links, i)) {
			break;
		}
	}
	handle_unrecognized_elements(argparser, args_size, args, argv_argument_links);
	handle_required_missing_elements(argparser, args_size, args, argv_argument_links);
	handle_optional_missing_elements(argparser, args_size, args, argv_argument_links);
	free(argv_argument_links);
	return 0;
fail:
	return 1;
}

static int parse_arg_n(cmn_argparser_t this, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links, size_t n) {
	struct cmn_argparser_argument *matching_arg;
	matching_arg = match_arg(this, argc, argv[n], argv_argument_links);
	if (matching_arg) {
		switch (matching_arg->action) {
		case CMN_ARGPARSER_ACTION_HELP:
			return parse_action_help(this);
		case CMN_ARGPARSER_ACTION_STORE:
			return parse_action_store(this, argc, argv, argv_argument_links, n, matching_arg);
		case CMN_ARGPARSER_ACTION_STORE_CONST:
			return parse_action_store_const(this, argc, argv, argv_argument_links, n, matching_arg);
		case CMN_ARGPARSER_ACTION_APPEND:
			// TODO
			break;
		case CMN_ARGPARSER_ACTION_APPEND_CONST:
			// TODO
			break;
		case CMN_ARGPARSER_ACTION_COUNT:
			// TODO
			break;
		case CMN_ARGPARSER_ACTION_EXTEND:
			// TODO
			break;
		default:
			break;
		}
	}
	return 0;
}

static struct cmn_argparser_argument *match_arg(cmn_argparser_t this, size_t argc, char const *args, struct cmn_argparser_argument **argv_argument_links) {
	bool match_positional = (args[0] != '-');
	bool match_optional = !match_positional && args[1];
	bool match_long_flag = match_optional && (args[1] == '-') && args[2];
	for (size_t i = 0; i < this->arguments_number; i++) {
		bool is_argument_parsed = false;
		for (size_t j = 0; j < argc; j++) {
			if (argv_argument_links[j] == &(this->arguments[i])) {
				is_argument_parsed = true;
				break;
			}
		}
		if (is_argument_parsed) {
			continue;
		}
		if ((match_positional && this->arguments[i].name) ||
		    (match_optional && this->arguments[i].flag &&
		     streq(args + 1, this->arguments[i].flag)) ||
		    (match_long_flag && this->arguments[i].long_flag &&
		     streq(args + 2, this->arguments[i].long_flag))) {
			return &(this->arguments[i]);
		}
	}
	return NULL;
}

static int handle_unrecognized_elements(cmn_argparser_t argparser, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links) {
	cmn_list_t error_arg_list = (cmn_list_t)cmn_linked_list_init();
	for (size_t i = 0; i < argc; i++) {
		if (!argv_argument_links[i]) {
			cmn_list_push_back(error_arg_list, (void *)argv[i]);
		}
	}
	if (!cmn_list_is_empty(error_arg_list)) {
		char *program_name;
		if (argparser->program_name) {
			program_name = argparser->program_name;
		}
		else {
			char *path = malloc(strlen(argparser->sys_argv[0]) + 1);
			strcpy(path, argparser->sys_argv[0]);
			program_name = basename(path);
		}
		cmn_argparser_print_usage(argparser);
		fprintf(stdout, "%s: %s", program_name, "error: unrecognized arguments: ");
		for (cmn_iterator_t i = cmn_list_begin(error_arg_list); !cmn_iterator_end(i); cmn_iterator_next(i)) {
			fprintf(stdout, "%s ", (char const *)cmn_iterator_data(i));
		}
		fprintf(stdout, "\n");
		exit(EXIT_FAILURE);
	}
	cmn_list_destroy(error_arg_list);
}

static int handle_required_missing_elements(cmn_argparser_t argparser, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links) {
	cmn_iterator_t iterator;
	cmn_list_t missing_required_arg_list = (cmn_list_t)cmn_linked_list_init();
	cmn_list_t required_arg_list = (cmn_list_t)cmn_linked_list_init();
	for (size_t i = 0; i < argparser->arguments_number; i++) {
		// TODO: the check is incomplete
		if (argparser->arguments[i].name || argparser->arguments[i].is_required) {
			cmn_list_push_back(required_arg_list,
			                   (void *)&(argparser->arguments[i]));
		}
	}
	for (iterator = cmn_list_begin(required_arg_list); !cmn_iterator_end(iterator); cmn_iterator_next(iterator)) {
		struct cmn_argparser_argument *element = cmn_iterator_data(iterator);
		bool is_present = false;
		for (size_t i = 0; i < argc; i++) {
			if (argv_argument_links[i] == element) {
				is_present = true;
				break;
			}
		}
		if (!is_present) {
			cmn_list_push_back(missing_required_arg_list, (void *)element);
		}
	}
	cmn_iterator_destroy(iterator);
	cmn_list_destroy(required_arg_list);
	if (!cmn_list_is_empty(missing_required_arg_list)) {
		char *program_name;
		if (argparser->program_name) {
			program_name = argparser->program_name;
		}
		else {
			char *path = malloc(strlen(argparser->sys_argv[0]) + 1);
			strcpy(path, argparser->sys_argv[0]);
			program_name = basename(path);
		}
		cmn_argparser_print_usage(argparser);
		fprintf(stdout, "%s: %s", program_name, "error: the following arguments are required: ");
		for (iterator = cmn_list_begin(missing_required_arg_list); !cmn_iterator_end(iterator); cmn_iterator_next(iterator)) {
			struct cmn_argparser_argument *element = cmn_iterator_data(iterator);
			char const *element_name;
			if (element->name) {
				element_name = element->name;
			}
			else {
				asprintf((char **)&element_name,
				         "%s%s%s%s%s",
				         element->flag ? "-" : "",
				         element->flag ? element->flag : ""
				         , element->flag && element->long_flag ? "/" : "",
				         element->long_flag ? "--" : "",
				         element->long_flag ? element->long_flag : "");
			}
			fprintf(stdout, "%s ", element_name);
		}
		fprintf(stdout, "\n");
		exit(EXIT_FAILURE);
	}
	cmn_list_destroy(missing_required_arg_list);
}

static int handle_optional_missing_elements(cmn_argparser_t this, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links) {
	cmn_iterator_t iterator;
	cmn_list_t missing_optional_arg_list = (cmn_list_t)cmn_linked_list_init();
	cmn_list_t optional_arg_list = (cmn_list_t)cmn_linked_list_init();
	for (size_t i = 0; i < this->arguments_number; i++) {
		if (!this->arguments[i].name && !this->arguments[i].is_required) {
			cmn_list_push_back(optional_arg_list, (void *)&(this->arguments[i]));
		}
	}
	for (iterator = cmn_list_begin(optional_arg_list); !cmn_iterator_end(iterator); cmn_iterator_next(iterator)) {
		struct cmn_argparser_argument *element = cmn_iterator_data(iterator);
		bool is_present = false;
		for (size_t i = 0; i < argc; i++) {
			if (argv_argument_links[i] == element) {
				is_present = true;
				break;
			}
		}
		if (!is_present) {
			cmn_list_push_back(missing_optional_arg_list, (void *)element);
		}
	}
	cmn_iterator_destroy(iterator);
	cmn_list_destroy(optional_arg_list);
	if (!cmn_list_is_empty(missing_optional_arg_list)) {
		for (iterator = cmn_list_begin(missing_optional_arg_list); !cmn_iterator_end(iterator); cmn_iterator_next(iterator)) {
			struct cmn_argparser_argument *element = cmn_iterator_data(iterator);
			if (element->action == CMN_ARGPARSER_ACTION_STORE) {
				if (element->type == CMN_ARGPARSER_TYPE_CSTR) {
					*(element->result) =
						malloc(strlen((char *)element->default_value) + 1);
					strcpy((char *)*(element->result),
					       (char *)element->default_value);
				}
			}
		}
	}
	cmn_iterator_destroy(iterator);
	cmn_list_destroy(missing_optional_arg_list);
}

static int parse_action_help(cmn_argparser_t argparser) {
	cmn_argparser_print_help(argparser);
	exit(EXIT_SUCCESS);
}

static int parse_action_store(cmn_argparser_t this, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links, size_t n, struct cmn_argparser_argument *argument) {
	bool is_positional = argument->name;
	bool have_flag = argument->flag;
	switch (argument->action_nargs) {
	case CMN_ARGPARSER_ACTION_NARGS_SINGLE:
		{
			char *arg;
			if (is_positional) {
				arg = argv[n];
			}
			else {
				if (n == argc - 1) {
					return 1;
				}
				arg = argv[n + 1];
			}
			switch (argument->type) {
			case CMN_ARGPARSER_TYPE_BOOL:
				// TODO
				break;
			case CMN_ARGPARSER_TYPE_CSTR:
				*(argument->result) = malloc(strlen(arg) + 1);
				strcpy((char *)*(argument->result), arg);
				break;
			case CMN_ARGPARSER_TYPE_INT:
			case CMN_ARGPARSER_TYPE_LONG:
			case CMN_ARGPARSER_TYPE_USHORT:
			case CMN_ARGPARSER_TYPE_UINT:
				convert_result(this, argument, arg);
				break;
			}
			if (is_positional) {
				argv_argument_links[n] = argument;
			}
			else {
				argv_argument_links[n] = argument;
				argv_argument_links[n + 1] = argument;
			}
			break;
		}
	case CMN_ARGPARSER_ACTION_NARGS_OPTIONAL:
		// TODO
		break;
	case CMN_ARGPARSER_ACTION_NARGS_LIST_OF_N:
		// TODO
		break;
	case CMN_ARGPARSER_ACTION_NARGS_LIST:
		// TODO
		break;
	case CMN_ARGPARSER_ACTION_NARGS_LIST_OPTIONAL:
		// TODO
		break;
	default:
		break;
	}
	return 0;
}

static int parse_action_store_const(cmn_argparser_t this, size_t argc, char *const *argv, struct cmn_argparser_argument **argv_argument_links, size_t n, struct cmn_argparser_argument *argument) {
	bool is_positional = argument->name;
	bool have_flag = argument->flag;
	switch (argument->action_nargs) {
	case CMN_ARGPARSER_ACTION_NARGS_SINGLE:
		if (is_positional) {
			// TODO
		}
		else {
			if (argument->type == CMN_ARGPARSER_TYPE_BOOL) {
				*((bool *)(argument->result)) = (bool)(argument->const_value);
			}
			argv_argument_links[n] = argument;
		}
		break;
	case CMN_ARGPARSER_ACTION_NARGS_OPTIONAL:
		// TODO
		break;
	case CMN_ARGPARSER_ACTION_NARGS_LIST_OF_N:
		// TODO
		break;
	case CMN_ARGPARSER_ACTION_NARGS_LIST:
		// TODO
		break;
	case CMN_ARGPARSER_ACTION_NARGS_LIST_OPTIONAL:
		// TODO
		break;
	default:
		break;
	}
	return 0;
}

static void convert_result(cmn_argparser_t argparser, struct cmn_argparser_argument *argument, char const *arg) {
	static char const
		*type_names[] = { [CMN_ARGPARSER_TYPE_UINT] = "unsigned int", [CMN_ARGPARSER_TYPE_USHORT] = "unsigned short", [CMN_ARGPARSER_TYPE_LONG] = "long" };
	enum cmn_strto_error ret;
	char const *type_name;
	char const *arg_name;
	switch (argument->type) {
	case CMN_ARGPARSER_TYPE_INT:
		ret = cmn_strto_n((int *)argument->result, arg);
		break;
	case CMN_ARGPARSER_TYPE_LONG:
		ret = cmn_strto_n((long *)argument->result, arg);
		break;
	case CMN_ARGPARSER_TYPE_USHORT:
		ret = cmn_strto_n((unsigned short *)argument->result, arg);
		break;
	case CMN_ARGPARSER_TYPE_UINT:
		ret = cmn_strto_n((unsigned int *)argument->result, arg);
		break;
	default:
		return; // unreachable
	}
	type_name = type_names[argument->type];
	if (ret != CMN_STRTO_SUCCESS) {
		cmn_argparser_print_usage(argparser);
		char *path;
		char *program_name;
		if (argparser->program_name) {
			program_name = argparser->program_name;
		}
		else {
			path = malloc(strlen(argparser->sys_argv[0]) + 1);
			strcpy(path, argparser->sys_argv[0]);
			program_name = basename(path);
		}
		if (argument->name) {
			arg_name = argument->name;
		}
		else {
			asprintf((char **)&arg_name,
			         "%s%s%s%s%s",
			         argument->flag ? "-" : "",
			         argument->flag ? argument->flag : "",
			         argument->flag && argument->long_flag ? "/" : "",
			         argument->long_flag ? "--" : "",
			         argument->long_flag ? argument->long_flag : "");
		}
		fprintf(stdout, "%s: error: argument %s: invalid %s value: '%s'", program_name, arg_name, type_name, arg);
		fflush(stdout);
		exit(EXIT_FAILURE);
	}
}
