#pragma once

#include <buracchi/common/argparser/argparser.h>
#include <buracchi/common/containers/map.h>

struct cmn_argparser {
	char* program_name;
	char* usage;
	char* description;
	bool add_help;
	size_t arguments_number;
	struct cmn_argparser_argument* arguments;
	cmn_map_t map;
};
