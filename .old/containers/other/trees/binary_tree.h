#pragma once

#include "./trees/binary_tree_node.h"

typedef void* binary_tree_t;

binary_tree_t binary_tree_init();

int binary_tree_destroy(binary_tree_t handle);

long binary_tree_nodes_number(binary_tree_t handle);

binary_tree_node_t binary_tree_get_root(binary_tree_t handle);

void binary_tree_set_root(binary_tree_t handle, binary_tree_node_t node);

void binary_tree_insert_as_left_subtree(binary_tree_t handle, binary_tree_node_t node, binary_tree_t subtree);

void binary_tree_insert_as_right_subtree(binary_tree_t handle, binary_tree_node_t node, binary_tree_t subtree);

binary_tree_t binary_tree_cut(binary_tree_t handle, binary_tree_node_t node);

binary_tree_t binary_tree_cut_left(binary_tree_t handle, binary_tree_node_t node);

binary_tree_t binary_tree_cut_right(binary_tree_t handle, binary_tree_node_t node);
