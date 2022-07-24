#include "main-mock.h"

#include <buracchi/common/argparser/argparser.h>
#include <buracchi/common/containers/map.h>

const char* mock_main(int argc, const char** argv) {
	const char* result = NULL;
	cmn_map_t option_map;
	cmn_argparser_t argparser;
	struct cmn_argparser_argument args[] = {
			{.name = "arg", .help = "an important argument", 0},
			{.flag = "f", .long_flag = "foo", .is_required = true, .help = "set the ammount of foo data"},
			{.long_flag = "set-bar", .action = CMN_ARGPARSER_ACTION_STORE_TRUE, .default_value = false, .help = "set the bar switch"}
	};
	argparser = cmn_argparser_init();
	cmn_argparser_add_arguments(argparser, &args);
	cmn_argparser_set_description(argparser, "An example program.");
	option_map = cmn_argparser_parse(argparser, argc, argv);
	cmn_map_at(option_map, (void*)"arg", (void**)&result);
	cmn_argparser_destroy(argparser);
	return result;
}
