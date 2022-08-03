#include <buracchi/common/argparser/argparser.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libgen.h>
#include <stdio.h>

#include <buracchi/common/utilities/utilities.h>

#include "struct_argparser.h"

static int get_optionals_usage(struct cmn_argparser_argument const *arg, char **str, char *str_vararg);

static int get_optionals_descritpion(struct cmn_argparser_argument const *arg, char **str, char *str_vararg);

static int get_positionals_usage(char **str, char *str_vararg);

static int get_positionals_description(struct cmn_argparser_argument const *arg, char **str);

static char *get_positional_args_string(struct cmn_argparser_argument const *arg);

static char *get_flag_vararg(struct cmn_argparser_argument const *arg);

static char *get_narg_optional(char const *vararg);

static char *get_narg_list_n(char const *vararg, size_t n);

static char *get_narg_list(char const *vararg);

static char *get_narg_list_optional(char const *vararg);

extern int cmn_argparser_print_usage2(cmn_argparser_t argparser, FILE *file) {
	char *usage_message;
	usage_message = cmn_argparser_format_usage(argparser);
	fprintf(file, "%s\n", usage_message);
	free(usage_message);
	return 0;
}

extern int cmn_argparser_print_help2(cmn_argparser_t argparser, FILE *file) {
	char *help_message;
	help_message = cmn_argparser_format_help(argparser);
	fprintf(file, "%s", help_message);
	free(help_message);
	return 0;
}

extern char *cmn_argparser_format_usage(cmn_argparser_t argparser) {
	char *usage_message;
	char *optionals_usage = NULL;
	char *positionals_usage = NULL;
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
	for (size_t i = 0; i < argparser->arguments_number; i++) {
		struct cmn_argparser_argument const *parg = &(argparser->arguments[i]);
		char *str_vararg = get_positional_args_string(parg);
		char *old_usage;
		if (parg->name) {
			old_usage = positionals_usage;
			get_positionals_usage(&positionals_usage, str_vararg);
		}
		else {
			old_usage = optionals_usage;
			get_optionals_usage(parg, &optionals_usage, str_vararg);
		}
		free(str_vararg);
		free(old_usage);
	}
	asprintf(&usage_message,
	         "usage: %s%s%s",
	         program_name,
	         optionals_usage ? optionals_usage : "",
	         positionals_usage ? positionals_usage : ""
	);
	if (!argparser->program_name) {
		free(path);
	}
	free(optionals_usage);
	free(positionals_usage);
	return usage_message;
}

extern char *cmn_argparser_format_help(cmn_argparser_t argparser) {
	char *help_message;
	char *usage_message;
	char *optionals_description = NULL;
	char *positionals_description = NULL;
	usage_message = cmn_argparser_format_usage(argparser);
	for (size_t i = 0; i < argparser->arguments_number; i++) {
		struct cmn_argparser_argument *parg = &(argparser->arguments[i]);
		char *str_vararg = get_positional_args_string(parg);
		char *old_description;
		if (parg->name) {
			old_description = positionals_description;
			get_positionals_description(parg, &positionals_description);
		}
		else {
			old_description = optionals_description;
			get_optionals_descritpion(parg, &optionals_description, str_vararg);
		}
		free(str_vararg);
		free(old_description);
	}
	asprintf(&help_message,
	         "%s\n\n%s\n%s%s",
	         usage_message,
	         argparser->description,
	         positionals_description ? positionals_description : "",
	         optionals_description ? optionals_description : "");
	free(usage_message);
	free(optionals_description);
	free(positionals_description);
	return help_message;
}

static inline int get_optionals_usage(struct cmn_argparser_argument const *arg, char **str, char *str_vararg) {
	return asprintf(
			str,
			"%s %s%s%s%s%s%s",
			*str ? *str : "",
			!arg->is_required ? "[" : "",
			arg->flag ? "-" : "--",
			arg->flag ? arg->flag : arg->long_flag,
			str_vararg ? " " : "",
			str_vararg ? str_vararg : "",
			!arg->is_required ? "]" : ""
	);
}

static inline int get_optionals_descritpion(struct cmn_argparser_argument const *arg, char **str, char *str_vararg) {
	return asprintf(
			str,
			"%s  %s%s%s%s%s%s%s%s%s\t%s\n",
			*str ? *str : "\noptional arguments:\n",
			arg->flag ? "-" : "",
			arg->flag ? arg->flag : "",
			str_vararg ? " " : "",
			str_vararg ? str_vararg : "",
			arg->flag ? ", " : "",
			arg->long_flag ? "--" : "",
			arg->long_flag ? arg->long_flag : "",
			str_vararg ? " " : "",
			str_vararg ? str_vararg : "\t",
			arg->help ? arg->help : ""
	);
}

static inline int get_positionals_usage(char **str, char *str_vararg) {
	return asprintf(str, "%s %s", *str ? *str : "", str_vararg);
}

static inline int get_positionals_description(struct cmn_argparser_argument const *arg, char **str) {
	return asprintf(str,
	                "%s  %s\t\t\t%s\n",
	                *str ? *str : "\npositional arguments:\n",
	                arg->name,
	                arg->help ? arg->help : "");
}

static char *get_positional_args_string(struct cmn_argparser_argument const *arg) {
	char *vararg;
	bool is_positional = arg->name;
	if (is_positional) {
		asprintf(&vararg, "%s", arg->name);
	}
	else {
		bool needs_arg = (arg->action == CMN_ARGPARSER_ACTION_STORE)
		                 || (arg->action == CMN_ARGPARSER_ACTION_APPEND)
		                 || (arg->action == CMN_ARGPARSER_ACTION_EXTEND);
		if (!needs_arg) {
			return NULL;
		}
		vararg = get_flag_vararg(arg);
	}
	switch (arg->action_nargs) {
	case CMN_ARGPARSER_ACTION_NARGS_SINGLE:
		return vararg;
	case CMN_ARGPARSER_ACTION_NARGS_OPTIONAL:
		return get_narg_optional(vararg);
	case CMN_ARGPARSER_ACTION_NARGS_LIST_OF_N:
		return get_narg_list_n(vararg, arg->nargs_list_size);
	case CMN_ARGPARSER_ACTION_NARGS_LIST:
		return get_narg_list(vararg);
	case CMN_ARGPARSER_ACTION_NARGS_LIST_OPTIONAL:
		return get_narg_list_optional(vararg);
	default:
		return NULL;
	}
}

static char *get_flag_vararg(struct cmn_argparser_argument const *arg) {
	char *result;
	if (arg->long_flag) {
		asprintf(&result, "%s", arg->long_flag);
	}
	else {
		asprintf(&result, "%s", arg->flag);
	}
	char *ptr = result;
	while (*ptr) {
		*ptr = (*ptr == '-') ? '_' : toupper(*ptr);
		ptr++;
	}
	return result;
}

static char *get_narg_optional(char const *vararg) {
	char *result;
	size_t size = strlen(vararg) + 3;
	result = malloc(size);
	strcpy(result + 1, vararg);
	result[0] = '[';
	result[size - 2] = ']';
	result[size - 1] = 0;
	return result;
}

static char *get_narg_list_n(char const *vararg, size_t n) {
	char *result;
	size_t size = strlen(vararg) * n + (n - 1) + 1;
	result = malloc(size);
	for (size_t i = 0; i < n; i++) {
		strcpy(result + ((strlen(vararg) + 1) * i), vararg);
		result[strlen(vararg) * (i + 1) + i] = ' ';
	}
	result[size - 1] = 0;
	return result;
}

static char *get_narg_list(char const *vararg) {
	char *result;
	size_t size = strlen(vararg) * 2 + 6 + 1;
	result = malloc(size);
	strcpy(result, vararg);
	result[strlen(vararg)] = ' ';
	result[strlen(vararg) + 1] = '[';
	strcpy(result + strlen(vararg) + 2, vararg);
	result[size - 5] = '.';
	result[size - 4] = '.';
	result[size - 3] = '.';
	result[size - 2] = ']';
	result[size - 1] = 0;
	return result;
}

static char *get_narg_list_optional(char const *vararg) {
	char *result = get_narg_list(vararg);
	result = get_narg_optional(result);
	return result;
}
