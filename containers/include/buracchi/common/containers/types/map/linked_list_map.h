#pragma once

#include <buracchi/common/containers/map/linked_list_map.h>

#include <buracchi/common/containers/types/map.h>
#include <buracchi/common/containers/types/list/linked_list.h>

struct cmn_linked_list_map {
    struct cmn_map super;
    cmn_linked_list_t list;
};

extern int cmn_linked_list_map_ctor(cmn_linked_list_map_t map);
