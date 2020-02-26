#pragma once

typedef void* bst_node_t;

extern bst_node_t bst_node_init(void* key, void* value);

extern int bst_node_destroy(bst_node_t handle);

extern long bst_node_degree(bst_node_t handle);

extern int bst_node_swap(bst_node_t handle1, bst_node_t handle2);

extern void* bst_node_get_key(bst_node_t handle);

extern void* bst_node_get_value(bst_node_t handle);

extern bst_node_t bst_node_get_father(bst_node_t handle);

extern int bst_node_set_father(bst_node_t handle, bst_node_t father);

extern bst_node_t bst_node_get_left_son(bst_node_t handle);

extern int bst_node_set_left_son(bst_node_t handle, bst_node_t left_son);

extern bst_node_t bst_node_get_right_son(bst_node_t handle);

extern int bst_node_set_right_son(bst_node_t handle, bst_node_t right_son);

extern int bst_node_is_left_son(bst_node_t handle);

extern int bst_node_is_right_son(bst_node_t handle);

extern bst_node_t bst_node_get_max(bst_node_t handle);

extern bst_node_t bst_node_get_pred(bst_node_t handle);
