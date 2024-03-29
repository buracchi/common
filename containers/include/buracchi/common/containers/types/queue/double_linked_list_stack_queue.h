#pragma once

#include <buracchi/common/containers/queue/double_linked_list_stack_queue.h>

#include <buracchi/common/containers/stack/linked_list_stack.h>
#include <buracchi/common/containers/types/queue.h>

struct cmn_double_linked_list_stack_queue {
    struct cmn_queue super;
    cmn_linked_list_stack_t stack_in;
    cmn_linked_list_stack_t stack_out;
};

extern int cmn_double_linked_list_stack_queue_ctor(cmn_double_linked_list_stack_queue_t queue);
