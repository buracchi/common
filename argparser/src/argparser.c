#include <buracchi/common/argparser/argparser.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <buracchi/common/containers/map/linked_list_map.h>
#include <buracchi/common/utilities/try.h>

#include "struct_argparser.h"

extern int format_usage(cmn_argparser_t this);

static struct cmn_argparser_argument help_arg = {
        .flag = "h",
        .long_flag = "help",
        .action = CMN_ARGPARSER_ACTION_HELP,
        .help = "show this help message and exit"
};

static int lexicographical_comparison(void* arg1, void* arg2, bool* result) {
    const char* _s1 = (const char*)arg1;
    const char* _s2 = (const char*)arg2;
    while (*_s1 && *_s2 && *(_s1++) == *(_s2++));
    *result = *_s1 == *_s2;
    return 0;
}

extern cmn_argparser_t _cmn_argparser_init(const char* pname, const char* pdesc, struct cmn_argparser_argument *arguments, size_t arguments_number) {
    cmn_argparser_t this;
    try(this = malloc(sizeof *this), NULL, fail);
    try(this->program_name = malloc(strlen(pname) + 1), NULL, fail2);
    try(this->program_description = malloc(strlen(pdesc) + 1), NULL, fail3);
    try(this->map = (cmn_map_t) cmn_linked_list_map_init(), NULL, fail4);
    cmn_map_set_key_comparer(this->map, &lexicographical_comparison);
    strcpy(this->program_name, pname);
    strcpy(this->program_description, pdesc);
    this->args_number = arguments_number + 1;
    try(this->args = malloc(sizeof * this->args * this->args_number), NULL, fail4);
    memcpy(&(this->args[0]), &help_arg, sizeof * this->args);
    for (size_t i = 1; i < this->args_number; i++) {
        memcpy(&(this->args[i]), arguments++, sizeof * this->args);
    }
    // TODO: Check and throw error if: There are conflicts, ...
    format_usage(this);
    return this;
fail4:
    free(this->program_description);
fail3:
    free(this->program_name);
fail2:
    free(this);
fail:
    return NULL;
}

extern int cmn_argparser_destroy(cmn_argparser_t this) {
    try(cmn_map_destroy(this->map), 1, fail);
    free(this->args);
    free(this->program_name);
    free(this->program_description);
    free(this->usage);
    free(this->usage_details);
    free(this);
    return 0;
fail:
    return 1;
}
