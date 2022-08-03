#include "main-mock.h"

#include <string.h>

#include <buracchi/common/argparser/argparser.h>

extern int mock_main(int argc, char **argv) {
	char *arg;
	char *foo;
	cmn_argparser_t argparser;
	argparser = cmn_argparser_init(argc, argv);
	cmn_argparser_set_description(argparser, "An example program.");
	cmn_argparser_add_argument(argparser, &arg, CMN_ARGPARSER_ARGUMENT({.name = "arg", .help = "an important argument"}));
	cmn_argparser_add_argument(argparser, &foo, CMN_ARGPARSER_ARGUMENT({.flag = "f", .long_flag = "foo", .is_required = true, .help = "set the amount of foo data"}));
	cmn_argparser_parse_args(argparser);
	cmn_argparser_destroy(argparser);
	return (strcmp(arg, "test") == 0 && strcmp(foo, "11") == 0) ? 0 : 1;
}

extern int test_parse_array_of_strings(int argc, char **argv) {
	char *arg;
	char *foo;
	cmn_argparser_t argparser;
	argparser = cmn_argparser_init(argc, argv);
	cmn_argparser_set_description(argparser, "An example program.");
	cmn_argparser_add_argument(argparser, &arg, CMN_ARGPARSER_ARGUMENT({.name = "arg", .help = "an important argument"}));
	cmn_argparser_add_argument(argparser, &foo, CMN_ARGPARSER_ARGUMENT({.flag = "f", .long_flag = "foo", .is_required = true, .help = "set the amount of foo data"}));
	cmn_argparser_parse_args(argparser, ((char *[]) {"test", "-f", "11"}));
	cmn_argparser_destroy(argparser);
	return (strcmp(arg, "test") == 0 && strcmp(foo, "11") == 0) ? 0 : 1;
}

extern int test_action_store_type_uint(int argc, char **argv) {
	unsigned int arg;
	cmn_argparser_t argparser;
	argparser = cmn_argparser_init(argc, argv);
	cmn_argparser_set_description(argparser, "An example program.");
	cmn_argparser_add_argument(argparser, &arg, CMN_ARGPARSER_ARGUMENT({.name = "arg"}));
	cmn_argparser_parse_args(argparser, ((char *[]) { "11" }));
	cmn_argparser_destroy(argparser);
	return (arg == 11) ? 0 : 1;
}

extern int test_action_store_true(int argc, char **argv) {
	bool f = false;
	cmn_argparser_t argparser;
	argparser = cmn_argparser_init(argc, argv);
	cmn_argparser_set_description(argparser, "An example program.");
	cmn_argparser_add_argument_action_store_true(argparser, &f, CMN_ARGPARSER_ARGUMENT({.flag = "f", .help = "set f true"}));
	cmn_argparser_parse_args(argparser, ((char *[]) { "-f" }));
	cmn_argparser_destroy(argparser);
	return (f == true) ? 0 : 1;
}

extern int test_action_store_false(int argc, char **argv) {
	bool f = true;
	cmn_argparser_t argparser;
	argparser = cmn_argparser_init(argc, argv);
	cmn_argparser_set_description(argparser, "An example program.");
	cmn_argparser_add_argument_action_store_false(argparser, &f, CMN_ARGPARSER_ARGUMENT({.flag = "f", .help = "set f true"}));
	cmn_argparser_parse_args(argparser, ((char *[]) { "-f" }));
	cmn_argparser_destroy(argparser);
	return (f == false) ? 0 : 1;
}
