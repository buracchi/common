#pragma once

#include <buracchi/common/argparser/argparser.h>
#include <buracchi/common/containers/map.h>

struct cmn_argparser {
	char* program_name;
	char* program_description;
	char* usage;
	char* usage_details;
	struct cmn_argparser_argument* args;
	size_t args_number;
	cmn_map_t map;
};
