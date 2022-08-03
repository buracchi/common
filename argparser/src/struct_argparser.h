#pragma once

#include <buracchi/common/argparser/argparser.h>

struct cmn_argparser {
	char *program_name;
	char *usage;
	char *description;
	size_t arguments_number;
	struct cmn_argparser_argument *arguments;
	int sys_argc;
	char *const *sys_argv;
};
