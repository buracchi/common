#include "main-mock.h"

#include <buracchi/common/argparser/argparser.h>

const char* mock_main(int argc, const char** argv) {
	char* arg;
	char* foo;
	cmn_argparser_t argparser;
	argparser = cmn_argparser_init();
	cmn_argparser_set_description(argparser, "An example program.");
	cmn_argparser_add_argument(argparser, &arg, CMN_ARGPARSER_ARGUMENT({.name = "arg", .help = "an important argument"}));
	cmn_argparser_add_argument(argparser, &foo, CMN_ARGPARSER_ARGUMENT({.flag = "f", .long_flag = "foo", .is_required = true, .help = "set the ammount of foo data"}));
	cmn_argparser_parse(argparser, argc, argv);
	cmn_argparser_destroy(argparser);
	return arg;
}
