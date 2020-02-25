#pragma once

#include "./trees/binary_tree_node.h"

typedef void* binary_tree_t;

extern binary_tree_t binary_tree_init(binary_tree_node_t root);

extern int binary_tree_destroy(binary_tree_t handle);

extern long binary_tree_nodes_number(binary_tree_t handle);

extern binary_tree_node_t binary_tree_get_root(binary_tree_t handle);

extern void binary_tree_set_root(binary_tree_t handle, binary_tree_node_t node);

extern void binary_tree_insert_as_left_subtree(binary_tree_t handle, binary_tree_node_t node, binary_tree_t subtree);

extern void binary_tree_insert_as_right_subtree(binary_tree_t handle, binary_tree_node_t node, binary_tree_t subtree);

extern binary_tree_t binary_tree_cut(binary_tree_t handle, binary_tree_node_t node);

extern binary_tree_t binary_tree_cut_left(binary_tree_t handle, binary_tree_node_t node);

extern binary_tree_t binary_tree_cut_right(binary_tree_t handle, binary_tree_node_t node);
