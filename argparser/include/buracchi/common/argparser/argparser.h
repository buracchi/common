#ifndef BURACCHI_COMMON_ARGPARSER_H_INCLUDED
#define BURACCHI_COMMON_ARGPARSER_H_INCLUDED
/** @file
 *
 * @brief Argparser interface.
 * @details This file represent the public interface of the Argparser module.
 * The argparse module makes it easy to write user-friendly command-line interfaces.
 * The program defines what arguments it requires, and argparse will figure out
 * how to parse those out of argv. The argparse module also automatically generates
 * help and usage messages and issues errors when users give the program invalid
 * arguments.
 */

#include <stddef.h>
#include <stdbool.h>

typedef struct cmn_argparser* cmn_argparser_t;

/**
 * @enum cmn_argparser_action
 *
 * @brief Methods of handling command line arguments.
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_STORE
 *      @brief stores the argument’s value
 *      @details (e.g. '--foo 1' will be stored as a KV pair {"foo","1"})
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_STORE_CONST
 *      @brief stores the value specified by the const_value field
 *      @details (e.g. '--foo'   will be stored as a KV pair {"foo","cmn_argparser_argument::const_value"})
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_STORE_TRUE
 *      @brief special cases of @ref CMN_ARGPARSER_ACTION_STORE_CONST
 *		used for storing the value true
 *		@details set the default values to true
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_STORE_FALSE
 *      @brief special cases of @ref CMN_ARGPARSER_ACTION_STORE_CONST
 *		used for storing the value false
 *		@details set the default values to false
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_APPEND
 *      @brief stores a list, and appends each argument value to the list
 *      @details It is useful to allow an option to be specified multiple times.
 *		If the default value is non-empty, the default elements will be present
 *		in the parsed value for the option, with any values from the command line
 *		appended after those default values.
 *		(e.g. '--foo 1 --foo 2' will be stored as a KV pair {"foo",{"1", "2", NULL}})
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_APPEND_CONST
 *      @brief stores a list, and appends the value specified by the const_value
 *		argument to the list.
 *		@details It is useful when multiple arguments need to store constants
 *		to the same list.
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_COUNT
 *      @brief counts the number of times a keyword argument occurs
 *      @details (e.g. '-vvv' will be stored as a KV pair {"v",3})
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_HELP
 *      @brief This prints a complete help message for all the options in the
 *      current parser and then exits.
 *      @details By default a help action is automatically added to the parser.
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_VERSION
 *      @brief This expects a .version=keyword argument in the
 *		cmn_argparser_add_argument() call, and prints version information and exits
*		when invoked.
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_EXTEND
 *      @brief stores a list, and extends each argument value to the list
 *      @details (e.g. '--foo f1 --foo f2 f3 f4' will be stored as a KV pair {"foo",{"f1", "f2", "f3", "f4", NULL}})
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_BOOLEAN_OPTIONAL
 *      @brief add support for boolean actions such as --foo and --no-foo.
 *      @details (e.g. --no-foo' will be stored as a KV pair {"foo", false})
 *
 */
enum cmn_argparser_action {
	CMN_ARGPARSER_ACTION_STORE,
	CMN_ARGPARSER_ACTION_STORE_CONST,
	CMN_ARGPARSER_ACTION_STORE_TRUE,
	CMN_ARGPARSER_ACTION_STORE_FALSE,
	CMN_ARGPARSER_ACTION_APPEND,
	CMN_ARGPARSER_ACTION_APPEND_CONST,
	CMN_ARGPARSER_ACTION_COUNT,
	CMN_ARGPARSER_ACTION_VERSION,
	CMN_ARGPARSER_ACTION_HELP,
	CMN_ARGPARSER_ACTION_EXTEND,
	CMN_ARGPARSER_BOOLEAN_OPTIONAL
};

/**
 * @enum cmn_argparser_action_nargs
 *
 * @brief Methods of associating command line arguments with a single action.
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_NARGS_SINGLE
 *      @brief One argument will be consumed from the command line and produced
 *       as a single item.
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_NARGS_OPTIONAL
 *      @brief One argument will be consumed from the command line if possible,
 *       and produced as a single item.
 *      @details If no command-line argument is present, the value from @ref
 *       default_value will be produced. Note that for optional arguments, there
 *       is an additional case - the option string is present but not followed
 *       by a command-line argument. In this case the value from @ref
 *       const_value will be produced.
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_NARGS_LIST_OF_N
 *      @brief N arguments from the command line will be gathered together into
 *       a NULL terminated list.
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_NARGS_LIST
 *      @brief special cases of @ref CMN_ARGPARSER_ACTION_STORE_CONST
 *
 * @var cmn_argparser_action::CMN_ARGPARSER_ACTION_NARGS_LIST_OPTIONAL
 *      @brief special cases of @ref CMN_ARGPARSER_ACTION_STORE_CONST
 *      @details the parsing won't fail if no argument is provided.
 *
 */
enum cmn_argparser_action_nargs {
	CMN_ARGPARSER_ACTION_NARGS_SINGLE,
	CMN_ARGPARSER_ACTION_NARGS_OPTIONAL,
	CMN_ARGPARSER_ACTION_NARGS_LIST_OF_N,
	CMN_ARGPARSER_ACTION_NARGS_LIST,
	CMN_ARGPARSER_ACTION_NARGS_LIST_OPTIONAL,
};

enum cmn_argparser_type {
	CMN_ARGPARSER_CSTR
};

/**
 * @struct cmn_argparser_argument
 *
 * @brief Argument item.
 *
 * @var cmn_argparser_argument::name
 *      @brief Specify the name of a positional argument (like a value or a list
 *       of filenames).
 *
 * @var cmn_argparser_argument::flag
 *      @brief Specify a character flag identifying an option which will be
 *       preceded by a hyphen.
 *      @details If name is not NULL this field will be ignored during parsing.
 *
 * @var cmn_argparser_argument::long_flag
 *      @brief Specify a name flag identifying an option which will be preceded
 *       by two hyphens.
 *      @details If name is not NULL this field will be ignored during parsing.
 *
 * @var cmn_argparser_argument::is_required
 *      @brief Specify if an option is required, @ref cmn_argparser_parse will
 *       report an error if that option is not present at the command line.
 *      @details If name is not NULL this field will be ignored during parsing.
 *       The default value of this field is false.
 *
 * @var cmn_argparser_argument::action
 *      @brief Specify how the argument should be handled.
 *      @details Argparser objects associate command-line arguments with
 *       actions. These actions can do just about anything with the command-line
 *       arguments associated with them, though most actions simply add a value
 *       into the map returned by \ref cmn_argparser_parse().
 *       The default action is @ref CMN_ARGPARSER_ACTION_STORE.
 *
 * @var cmn_argparser_argument::action_nargs
 *      @brief Specify how to associate different number of command-line
 *       arguments with a single action.
 *      @details If @ref CMN_ARGPARSER_ACTION_NARGS_SINGLE or
 *       @ref CMN_ARGPARSER_ACTION_NARGS_OPTIONAL are specified then the
 *       parser will produce a single item. If @ref
 *       CMN_ARGPARSER_ACTION_NARGS_LIST_OF_N or @ref
 *       CMN_ARGPARSER_ACTION_NARGS_LIST are specified the parser will gather
 *       together the arguments from the command line into a NULL terminated
 *       string array.
 *
 * @var cmn_argparser_argument::nargs_list_size
 *      @brief Specify the number of elements that will be gathered together
 *       form the command line if @ref CMN_ARGPARSER_ACTION_NARGS_SINGLE is
 *       selected as the value of the @ref action_nargs field.
 *      @details This field is ignored if the @ref action_nargs field constains
 *       a value different from @ref CMN_ARGPARSER_ACTION_STORE.
 *
 * @var cmn_argparser_argument::const_value
 *      @brief Specify the value used when the action is set to
 *       @ref CMN_ARGPARSER_ACTION_STORE_CONST. The default value is NULL.
 *
 * @var cmn_argparser_argument::default_value
 *      @brief Specify what value should be used if the command-line argument
 *       is not present. an error message will be generated if there wasn’t at
 *       least one command-line argument present if the argument was positional
 *       or if it was an option with the required field set to true.
 *
 * @var cmn_argparser_argument::choices
 *      @brief Specify a NULL terminated array of acceptable values, @ref
 *       cmn_argparser_parse will report an error if the argument was not one
 *       of the acceptable values.
 *
 * @var cmn_argparser_argument::help
 *      @brief A string containing a brief description of the argument showed
 *       when a user requests help.
 *
 * @var cmn_argparser_argument::destination
 *      @brief Specify the identifier that will be used to retrive the argument
 *       supplied.
 *      @details The destination attribute allows to retrive the argument
 *       supplied. For positional argument, the default value is equal to name.
 *       For optional argument, the default value is inferred from the flags
 *       strings taking the first long option string and stripping away the
 *       initial -- string. If no long option strings were supplied, dest will
 *       be derived from the first short option string by stripping the initial
 *       - character. Any internal - characters will be converted to _
 *       characters to make sure the string is a valid attribute name.
 */
struct cmn_argparser_argument {
	bool active;
	void** result;
	enum cmn_argparser_action action;
	const char* name;
	const char* flag;
	const char* long_flag;
	bool is_required;
	enum cmn_argparser_action_nargs action_nargs;
	size_t nargs_list_size;
	void* const_value;
	void* default_value;
	char** choices;
	const char* help;
	const char* destination;
	enum cmn_argparser_type type;
};

#define CMN_ARGPARSER_ARGUMENT(...) (struct cmn_argparser_argument)__VA_ARGS__

/**
 * @brief Initialize an argument parser object.
 *
 * @return An initialized cmn_argparser object
 */
extern cmn_argparser_t cmn_argparser_init();

/**
 * @brief Free memory associated to an argument parser object.
 *
 * @param argparser
 * @return int
 */
extern int cmn_argparser_destroy(cmn_argparser_t argparser);

/**
 * @brief Set the argument parser object program name.
 *
 * @details By default cmn_argparser objects use argv[0] to determine
 * how to display the name of the program in help messages.
 * This default is almost always desirable because it will make the
 * help messages match how the program was invoked on the command line.
 * It is otherwise possible to specify an hardcoded string as the
 * program name using this function.
 *
 * @param argparser the argument parser object.
 * @param program_name The name of the program (default: basename(argv[0])).
 */
extern int cmn_argparser_set_program_name(cmn_argparser_t argparser, const char* program_name);

/**
 * @brief Set the argument parser object usage message.
 *
 * @details By default, cmn_argparser objects calculate the usage
 * message from the arguments they contain.
 * It is otherwise possible to specify an hardcoded string as the
 * usage message using this function.
 *
 * @param argparser the argument parser object.
 * @param usage The string describing the program usage.
 */
extern int cmn_argparser_set_usage(cmn_argparser_t argparser, const char* usage);

/**
 * @brief Set the Text to display before the argument help.
 *
 * @details Via this function it is possible to specify a brief description
 * of what the program does and how it works.
 * In help messages, the description is displayed between the command-line
 * usage string and the help messages for the various arguments.
 *
 * @param argparser the argument parser object.
 * @param description The string to display before the argument help.
 */
extern int cmn_argparser_set_description(cmn_argparser_t argparser, const char* description);

extern int cmn_argparser_add_argument_action_store_cstr(cmn_argparser_t argparser, char** result, struct cmn_argparser_argument argument);
#define cmn_argparser_add_argument_action_store(argparser, result, argument) _Generic((result), \
				    char**: cmn_argparser_add_argument_action_store_cstr)((argparser), (result), (argument))
#define cmn_argparser_add_argument cmn_argparser_add_argument_action_store

extern int cmn_argparser_add_arguments_with_size(cmn_argparser_t argparser, const struct cmn_argparser_argument* arguments, size_t arguments_number);

extern int cmn_argparser_parse(cmn_argparser_t argparser, int argc, const char** argv);

/**
 * TODO:
 *  * @var cmn_argparser::epilog
 *		@brief Text to display after the argument help
 *		@details By default, the epilog will be line-wrapped so that it fits
 *		within the given space. To change this behavior, see the
 *		@ref cmn_argparser::formatter argument.
 *		(default: none)
 *
 * @var cmn_argparser::parents
 *		@brief A NULL terminated list of cmn_argparser object references
 *		whose arguments should also be included
 *		@details Sometimes, several parsers share a common set of arguments.
 *		Rather than repeating the definitions of these arguments, a single
 *		parser with all the shared arguments passed via the
 *		@ref cmn_argparser::parents argument to the cmn_argparser objects can
 *		be used.
 *		It takes a list of cmn_argparser object references, collects all the
 *		positional and optional actions from them, and adds these actions to
 *		the cmn_argparser object being constructed.
 *		Note that most parent parsers will specify cmn_argparser::add_help as
 *		false. Otherwise, the ArgumentParser will see two -h/--help options
 *		(one in the parent and one in the child) and raise an error.
 *		Note You must fully initialize the parsers before passing them via
 *		@ref cmn_argparser::parents.
 *		If you change a parent parsers after the child parser initialization,
 *		those changes will not be reflected in the child.
 *
 * @var cmn_argparser::formatter
 *		@brief A class for customizing the help output
 *		@details Currently undocumented
 *
 * @var cmn_argparser::prefix_chars
 *		@brief The set of characters that prefix optional arguments
 *		@details Most command-line options will use - as the prefix, e.g. -f/--foo.
 *		Parsers that need to support different or additional prefix characters,
 *		e.g. for options like +f or /foo, may specify them using this argument.
 *		The prefix_chars argument defaults to '-'.
 *		Supplying a set of characters that does not include - will cause -f/--foo
 *		options to be disallowed.
 *
 * @var cmn_argparser::fromfile_prefix_chars
 *		@brief The set of characters that prefix files from which
 *		additional arguments should be read
 *		@details Currently undocumented
 *
 * @var cmn_argparser::argument_default
 *		@brief The global default value for arguments
 *		@details Currently undocumented
 *
 * @var cmn_argparser::conflict_handler
 *		@brief The strategy for resolving conflicting optionals (usually unnecessary)
 *		@details Currently undocumented
 *
 * @var cmn_argparser::add_help
 *		@brief Add a -h/--help option to the parser
 *		@details By default, cmn_argparser objects add an option which simply displays
 *		the parser’s help message.
 *		Occasionally, it may be useful to disable the addition of this help option.
 *		The help option is typically -h/--help. The exception to this is if the
 *		@ref cmn_argparser::prefix_chars is specified and does not include -, in which
 *		case -h and --help are not valid options.
 *		(default: true)
 *
 * @var cmn_argparser::allow_abbrev
 *		@brief Allows long options to be abbreviated if the abbreviation is unambiguous.
 *		@details Currently undocumented
 *
 * @var exit_on_error
 *		@brief Determines whether or not the program should exits
 *		with error info when an error occurs.
 *		@details Normally, when you invoke cmn_argparser_parse_args() with a
 *		cmn_argparser object containing an invalid argument list, the program
 *		will exit with error info.
 *		If the user would like to catch errors manually, the feature can be
 *		enabled by setting @ref cmn_argparser::exit_on_error to false
 *		(default: true)
 */
#endif // BURACCHI_COMMON_ARGPARSER_H_INCLUDED
