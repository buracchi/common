#pragma once

#include "./trees/bst/avl_tree/avl_tree_node.h"

typedef void* avl_tree_t;

typedef int avl_tree_comparison_function(const void* key1, const void* key2);

extern avl_tree_t avl_tree_init(avl_tree_node_t root, avl_tree_comparison_function* comparison_function);

extern int avl_tree_destroy(avl_tree_t handle);

extern long avl_tree_nodes_number(avl_tree_t handle);

extern avl_tree_node_t avl_tree_get_root(avl_tree_t handle);

extern void avl_tree_set_root(avl_tree_t handle, avl_tree_node_t node);

extern void avl_tree_insert_as_left_subtree(avl_tree_t handle, avl_tree_node_t node, avl_tree_t subtree);

extern void avl_tree_insert_as_right_subtree(avl_tree_t handle, avl_tree_node_t node, avl_tree_t subtree);

extern avl_tree_t avl_tree_cut(avl_tree_t handle, avl_tree_node_t node);

extern avl_tree_t avl_tree_cut_left(avl_tree_t handle, avl_tree_node_t node);

extern avl_tree_t avl_tree_cut_right(avl_tree_t handle, avl_tree_node_t node);

extern avl_tree_t avl_tree_cut_one_son_node(avl_tree_t handle, avl_tree_node_t node);

extern void avl_tree_insert_single_node_tree(avl_tree_t handle, void* key, avl_tree_t new_tree);

extern avl_tree_node_t avl_tree_search_node(avl_tree_t handle, void* key);

extern void* avl_tree_search(avl_tree_t handle, void* key);

extern int avl_tree_insert(avl_tree_t handle, void* key, void* value);

extern void avl_tree_delete(avl_tree_t handle, void* key);
