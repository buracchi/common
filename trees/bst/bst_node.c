#include "./trees/bst/bst_node.h"

#include <stdlib.h>

struct bst_node {
	void* key;
	void* value;
	bst_node_t father;
	bst_node_t left_son;
	bst_node_t right_son;
};

extern bst_node_t bst_node_init(void* key, void* value) {
	struct bst_node* node;
	if ((node = malloc(sizeof(struct bst_node))) == NULL) {
		return NULL;
	}
	node->key = key;
	node->value = value;
	node->father = NULL;
	node->left_son = NULL;
	node->right_son = NULL;
	return node;
}

extern int bst_node_destroy(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	free(node);
	return 0;
}

extern long bst_node_degree(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	long degree = 0;

	if (node) {
		if (node->left_son) {
			degree++;
		}
		if (node->right_son) {
			degree++;
		}
	}
	return degree;
}

extern int bst_node_swap(bst_node_t handle1, bst_node_t handle2) {
	struct bst_node* node1 = (struct bst_node*)handle1;
	struct bst_node* node2 = (struct bst_node*)handle1;
	void* tmp;
	tmp = node1->key;
	node1->key = node2->key;
	node2->key = tmp;
	tmp = node1->value;
	node1->value = node2->value;
	node2->value = tmp;
	return 0;
}

extern inline void* bst_node_get_key(bst_node_t handle){
	struct bst_node* node = (struct bst_node*)handle;
	return node->key;
}

extern inline void* bst_node_get_value(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	return node->value;
}

extern inline bst_node_t bst_node_get_father(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	return node->father;
}

extern int bst_node_set_father(bst_node_t handle, bst_node_t father) {
	struct bst_node* node = (struct bst_node*)handle;
	if (node) {
		node->father = father;
		return 0;
	}
	return 1;
}

extern inline bst_node_t bst_node_get_left_son(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	return node->left_son;
}

extern int bst_node_set_left_son(bst_node_t handle, bst_node_t left_son) {
	struct bst_node* node = (struct bst_node*)handle;
	if (node) {
		node->left_son = left_son;
		return 0;
	}
	return 1;
}

extern inline bst_node_t bst_node_get_right_son(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	return node->right_son;
}

extern inline int bst_node_set_right_son(bst_node_t handle, bst_node_t right_son) {
	struct bst_node* node = (struct bst_node*)handle;
	if (node) {
		node->right_son = right_son;
		return 0;
	}
	return 1;
}

extern inline int bst_node_is_left_son(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	if (node) {
		struct bst_node* father = node->father;
		if (father) {
			if (father->left_son == node) {
				return 1;
			}
		}
	}
	return 0;
}

extern inline int bst_node_is_right_son(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	if (node) {
		struct bst_node* father = node->father;
		if (father) {
			if (father->right_son == node) {
				return 1;
			}
		}
	}
	return 0;
}

extern bst_node_t bst_node_get_max(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	while (bst_node_get_right_son(node)) {
		node = bst_node_get_right_son(node);
	}
	return node;
}

extern bst_node_t bst_node_get_pred(bst_node_t handle) {
	struct bst_node* node = (struct bst_node*)handle;
	if (node == NULL) {
		return NULL;
	}
	if (bst_node_get_left_son(node)) {
		return bst_node_get_max(bst_node_get_left_son(node));
	}
	while (bst_node_is_left_son(node)) {
		node = bst_node_get_father(node);
	}
	return node;
}
