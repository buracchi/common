#pragma once

typedef void* binary_tree_node_t;

extern binary_tree_node_t binary_tree_node_init(void* info);

extern int binary_tree_node_destroy(binary_tree_node_t handle);

extern long binary_tree_node_degree(binary_tree_node_t handle);

extern int binary_tree_node_swap(binary_tree_node_t handle1, binary_tree_node_t handle2);

extern void* binary_tree_node_get_info(binary_tree_node_t handle);

extern binary_tree_node_t binary_tree_node_get_father(binary_tree_node_t handle);

extern int binary_tree_node_set_father(binary_tree_node_t handle, binary_tree_node_t father);

extern binary_tree_node_t binary_tree_node_get_left_son(binary_tree_node_t handle);

extern int binary_tree_node_set_left_son(binary_tree_node_t handle, binary_tree_node_t left_son);

extern binary_tree_node_t binary_tree_node_get_right_son(binary_tree_node_t handle);

extern int binary_tree_node_set_right_son(binary_tree_node_t handle, binary_tree_node_t right_son);

extern int binary_tree_node_is_left_son(binary_tree_node_t handle);

extern int binary_tree_node_is_right_son(binary_tree_node_t handle);
