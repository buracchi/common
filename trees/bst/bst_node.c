#include "./trees/bst/bst_node.h"

#include <stdlib.h>

#include "./trees/binary_tree_node.h"

struct bst_node {
	binary_tree_node_t node;
	void* key;
};

extern bst_node_t bst_node_init(void* key, void* value) {
	struct bst_node* bst_node;
	if ((bst_node = malloc(sizeof(struct bst_node))) == NULL) {
		return NULL;
	}
	bst_node->key = key;
	if ((bst_node->node = binary_tree_node_init(value)) == NULL) {
		free(bst_node);
		return NULL;
	}
	return bst_node;
}

extern int bst_node_destroy(bst_node_t handle) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	if (binary_tree_node_destroy(bst_node->node)) {
		return 1;
	}
	free(bst_node);
	return 0;
}

extern inline long bst_node_degree(bst_node_t handle) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_degree(bst_node->node);
}

extern inline int bst_node_swap(bst_node_t handle1, bst_node_t handle2) {
	struct bst_node* bst_node1 = (struct bst_node*)handle1;
	struct bst_node* bst_node2 = (struct bst_node*)handle1;
	if (binary_tree_node_swap(bst_node1, bst_node2)) {
		return 1;
	}
	void* tmp_key;
	tmp_key = bst_node1->key;
	bst_node1->key = bst_node2->key;
	bst_node2->key = tmp_key;
	return 0;
}

extern void* bst_node_get_key(bst_node_t handle){
	struct bst_node* bst_node = (struct bst_node*)handle;
	return bst_node->key;
}

extern void* bst_node_get_value(bst_node_t handle) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_get_info(bst_node->node);
}

extern inline bst_node_t bst_node_get_father(bst_node_t handle) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_get_father(bst_node->node);
}

extern inline int bst_node_set_father(bst_node_t handle, bst_node_t father) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_set_father(bst_node->node, father);
}

extern inline bst_node_t bst_node_get_left_son(bst_node_t handle) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_get_left_son(bst_node->node);
}

extern inline int bst_node_set_left_son(bst_node_t handle, bst_node_t left_son) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_set_left_son(bst_node->node, left_son);
}

extern inline bst_node_t bst_node_get_right_son(bst_node_t handle) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_get_right_son(bst_node->node);
}

extern inline int bst_node_set_right_son(bst_node_t handle, bst_node_t right_son) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_set_right_son(bst_node->node, right_son);
}

extern inline int bst_node_is_left_son(bst_node_t handle) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_is_left_son(bst_node->node);
}

extern inline int bst_node_is_right_son(bst_node_t handle) {
	struct bst_node* bst_node = (struct bst_node*)handle;
	return binary_tree_node_is_right_son(bst_node->node);
}

extern bst_node_t bst_node_get_max(bst_node_t handle) {
	bst_node_t current = handle;
	while (binary_tree_node_get_right_son(current)) {
		current = binary_tree_node_get_right_son(current);
	}
	return current;
}

extern bst_node_t bst_node_get_pred(bst_node_t handle) {
	if (handle == NULL) {
		return NULL;
	}
	if (binary_tree_node_get_left_son(handle)) {
		return bst_node_get_max(binary_tree_node_get_left_son(handle));
	}
	bst_node_t current = handle;
	while (binary_tree_node_is_left_son(current)) {
		current = binary_tree_node_get_father(current);
	}
	return current;
}
