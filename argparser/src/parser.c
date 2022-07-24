#include <buracchi/common/argparser/argparser.h>

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <buracchi/common/containers/list/linked_list.h>
#include <buracchi/common/utilities/utilities.h>
#include "buracchi/common/utilities/try.h"

#include "struct_argparser.h"

static int parse_arg_n(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links, int n);
static struct cmn_argparser_argument* match_arg(cmn_argparser_t this, int argc, const char* args,
	struct cmn_argparser_argument** argv_argument_links);
static int parse_action_store(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links, int n,
	struct cmn_argparser_argument* argument);
extern int parse_action_help(cmn_argparser_t this, int argc, const char** argv);
static int handle_unrecognized_elements(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links);
static int handle_required_missing_elements(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links);
static int handle_optional_missing_elements(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links);

extern cmn_map_t cmn_argparser_parse(cmn_argparser_t this, int argc, const char** argv) {
	struct cmn_argparser_argument** argv_argument_links = NULL;
	try(argv_argument_links = malloc(sizeof * argv_argument_links * argc), NULL, fail);
	memset(argv_argument_links, 0, argc * sizeof * argv_argument_links);
	for (int i = 1; i < argc; i++) {
		if (parse_arg_n(this, argc, argv, argv_argument_links, i)) {
			break;
		}
	}
	handle_unrecognized_elements(this, argc, argv, argv_argument_links);
	handle_required_missing_elements(this, argc, argv, argv_argument_links);
	handle_optional_missing_elements(this, argc, argv, argv_argument_links);
	free(argv_argument_links);
	return this->map;
fail:
	return NULL;
}

static int parse_arg_n(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links, int n) {
	struct cmn_argparser_argument* matching_arg;
	matching_arg = match_arg(this, argc, argv[n], argv_argument_links);
	if (matching_arg) {
		switch (matching_arg->action) {
		case CMN_ARGPARSER_ACTION_HELP:
			return parse_action_help(this, argc, argv);
		case CMN_ARGPARSER_ACTION_STORE:
			return parse_action_store(this, argc, argv, argv_argument_links, n, matching_arg);
		case CMN_ARGPARSER_ACTION_STORE_CONST:
			// TODO
			break;
		case CMN_ARGPARSER_ACTION_STORE_TRUE:
			// TODO
			break;
		case CMN_ARGPARSER_ACTION_STORE_FALSE:
			// TODO
			break;
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

static struct cmn_argparser_argument* match_arg(cmn_argparser_t this, int argc, const char* args,
	struct cmn_argparser_argument** argv_argument_links) {
	bool match_positional = (args[0] != '-');
	bool match_optional = !match_positional && args[1];
	bool match_long_flag = match_optional && (args[1] == '-') && args[2];
	for (size_t i = 0; i < this->arguments_number; i++) {
		bool is_argument_parsed = false;
		for (int j = 1; j < argc; j++) {
			if (argv_argument_links[j] == &(this->arguments[i])) {
				is_argument_parsed = true;
				break;
			}
		}
		if (is_argument_parsed) {
			continue;
		}
		if ((match_positional && this->arguments[i].name)
			|| (match_optional && this->arguments[i].flag && streq(args + 1, this->arguments[i].flag))
			|| (match_long_flag && this->arguments[i].long_flag && streq(args + 2, this->arguments[i].long_flag))) {
			return &(this->arguments[i]);
		}
	}
	return NULL;
}

static int handle_unrecognized_elements(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links) {
	cmn_list_t error_arg_list = (cmn_list_t)cmn_linked_list_init();
	for (int i = 1; i < argc; i++) {
		if (!argv_argument_links[i]) {
			cmn_list_push_back(error_arg_list, (void*)argv[i]);
		}
	}
	if (!cmn_list_is_empty(error_arg_list)) {
		fprintf(stderr, "%s\n", this->usage);
		fprintf(stderr, "%s: %s", this->program_name, "error: unrecognized arguments: ");
		for (cmn_iterator_t i = cmn_list_begin(error_arg_list); !cmn_iterator_end(i); cmn_iterator_next(i)) {
			fprintf(stderr, "%s ", (const char*)cmn_iterator_data(i));
		}
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
	cmn_list_destroy(error_arg_list);
}

static int handle_required_missing_elements(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links) {
	cmn_iterator_t iterator;
	cmn_list_t missing_required_arg_list = (cmn_list_t)cmn_linked_list_init();
	cmn_list_t required_arg_list = (cmn_list_t)cmn_linked_list_init();
	for (size_t i = 0; i < this->arguments_number; i++) {
		// TODO: the check is incomplete
		if (this->arguments[i].name || this->arguments[i].is_required) {
			cmn_list_push_back(required_arg_list, (void*)&(this->arguments[i]));
		}
	}
	for (iterator = cmn_list_begin(required_arg_list); !cmn_iterator_end(iterator); cmn_iterator_next(iterator)) {
		struct cmn_argparser_argument* element = cmn_iterator_data(iterator);
		bool is_present = false;
		for (int i = 1; i < argc; i++) {
			if (argv_argument_links[i] == element) {
				is_present = true;
				break;
			}
		}
		if (!is_present) {
			cmn_list_push_back(missing_required_arg_list, (void*)element);
		}
	}
	cmn_iterator_destroy(iterator);
	cmn_list_destroy(required_arg_list);
	if (!cmn_list_is_empty(missing_required_arg_list)) {
		fprintf(stderr, "%s\n", this->usage);
		fprintf(stderr, "%s: %s", this->program_name, "error: the following arguments are required: ");
		for (iterator = cmn_list_begin(missing_required_arg_list); !cmn_iterator_end(iterator); cmn_iterator_next(iterator)) {
			struct cmn_argparser_argument* element = cmn_iterator_data(iterator);
			if (element->name) {
				fprintf(stderr, "%s ", element->name);
			}
			else {
				if (element->flag) {
					fprintf(stderr, "-%s", element->flag);
				}
				if (element->flag && element->long_flag) {
					fprintf(stderr, "/");
				}
				if (element->long_flag) {
					fprintf(stderr, "--%s", element->long_flag);
				}
				fprintf(stderr, " ");
			}
		}
		fprintf(stderr, "\n");
		exit(EXIT_FAILURE);
	}
	cmn_list_destroy(missing_required_arg_list);
}

static int handle_optional_missing_elements(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links) {
	cmn_iterator_t iterator;
	cmn_list_t missing_optional_arg_list = (cmn_list_t)cmn_linked_list_init();
	cmn_list_t optional_arg_list = (cmn_list_t)cmn_linked_list_init();
	for (size_t i = 0; i < this->arguments_number; i++) {
		if (!this->arguments[i].name && !this->arguments[i].is_required) {
			cmn_list_push_back(optional_arg_list, (void*)&(this->arguments[i]));
		}
	}
	for (iterator = cmn_list_begin(optional_arg_list); !cmn_iterator_end(iterator); cmn_iterator_next(iterator)) {
		struct cmn_argparser_argument* element = cmn_iterator_data(iterator);
		bool is_present = false;
		for (int i = 1; i < argc; i++) {
			if (argv_argument_links[i] == element) {
				is_present = true;
				break;
			}
		}
		if (!is_present) {
			cmn_list_push_back(missing_optional_arg_list, (void*)element);
		}
	}
	cmn_iterator_destroy(iterator);
	cmn_list_destroy(optional_arg_list);
	if (!cmn_list_is_empty(missing_optional_arg_list)) {
		for (iterator = cmn_list_begin(missing_optional_arg_list); !cmn_iterator_end(iterator); cmn_iterator_next(iterator)) {
			struct cmn_argparser_argument* element = cmn_iterator_data(iterator);
			bool is_positional = element->name;
			bool have_flag = element->flag;
			cmn_map_insert(
				this->map,
				is_positional ?
				(void*)element->name :
				have_flag ?
				(void*)element->flag :
				(void*)element->long_flag,
				(void*)element->default_value,
				NULL
			);
		}
	}
	cmn_iterator_destroy(iterator);
	cmn_list_destroy(missing_optional_arg_list);
}


static int parse_action_store(cmn_argparser_t this, int argc, const char** argv,
	struct cmn_argparser_argument** argv_argument_links, int n,
	struct cmn_argparser_argument* argument) {
	bool is_positional = argument->name;
	bool have_flag = argument->flag;
	switch (argument->action_nargs) {
	case CMN_ARGPARSER_ACTION_NARGS_SINGLE:
		if (is_positional) {
			cmn_map_insert(this->map, (void*)argument->name, (void*)argv[n], NULL);
			argv_argument_links[n] = argument;
		}
		else {
			if (n == argc - 1) {
				return 1;
			}
			if (have_flag) {
				cmn_map_insert(this->map, (void*)argument->flag, (void*)argv[n + 1], NULL);
			}
			else {
				cmn_map_insert(this->map, (void*)argument->long_flag, (void*)argv[n + 1], NULL);
			}
			argv_argument_links[n] = argument;
			argv_argument_links[n + 1] = argument;
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
