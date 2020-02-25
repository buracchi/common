#pragma once

typedef void* avl_tree_node_t;

extern avl_tree_node_t avl_tree_node_init(void* key, void* value);

extern int avl_tree_node_destroy(avl_tree_node_t handle);

extern long avl_tree_node_degree(avl_tree_node_t handle);

extern int avl_tree_node_swap(avl_tree_node_t handle1, avl_tree_node_t handle2);

extern void* avl_tree_node_get_info(avl_tree_node_t handle);

extern void* avl_tree_node_get_key(avl_tree_node_t handle);

extern void* avl_tree_node_get_value(avl_tree_node_t handle);

extern int avl_tree_node_get_height(avl_tree_node_t handle);

extern int avl_tree_node_set_height(avl_tree_node_t handle, int height);

extern void avl_tree_node_update_height(avl_tree_node_t handle);

extern long avl_tree_node_get_balance_factor(avl_tree_node_t handle);

extern avl_tree_node_t avl_tree_node_get_father(avl_tree_node_t handle);

extern int avl_tree_node_set_father(avl_tree_node_t handle, avl_tree_node_t father);

extern avl_tree_node_t avl_tree_node_get_left_son(avl_tree_node_t handle);

extern int avl_tree_node_set_left_son(avl_tree_node_t handle, avl_tree_node_t left_son);

extern avl_tree_node_t avl_tree_node_get_right_son(avl_tree_node_t handle);

extern int avl_tree_node_set_right_son(avl_tree_node_t handle, avl_tree_node_t right_son);

extern int avl_tree_node_is_left_son(avl_tree_node_t handle);

extern int avl_tree_node_is_right_son(avl_tree_node_t handle);

extern avl_tree_node_t avl_tree_node_get_max(avl_tree_node_t node);

extern avl_tree_node_t avl_tree_node_get_pred(avl_tree_node_t node);
