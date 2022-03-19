#pragma once

#include <buracchi/common/containers/list/linked_list.h>

#include <buracchi/common/containers/types/list.h>
#include <buracchi/common/iterators/types/iterator.h>

struct cmn_linked_list {
    struct cmn_list super;
    size_t size;
    struct list_element *head;
    struct list_element *tail;
};

struct list_element {
    void *data;
    struct list_element *next;
};

struct linked_list_iterator {
    struct cmn_iterator super;
    struct cmn_linked_list *list;
    struct list_element *element;
};

extern int cmn_linked_list_ctor(cmn_linked_list_t list);
