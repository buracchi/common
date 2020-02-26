#include "./trees/binary_tree_node.h"

#include <stdlib.h>

struct binary_tree_node {
	void* data;
	binary_tree_node_t father;
	binary_tree_node_t left_son;
	binary_tree_node_t right_son;
};

extern binary_tree_node_t binary_tree_node_init(void* info) {
	struct binary_tree_node* node;
	if ((node = malloc(sizeof(struct binary_tree_node))) == NULL) {
		return NULL;
	}
	node->data = info;
	node->father = NULL;
	node->left_son = NULL;
	node->right_son = NULL;
	return node;
}

extern int binary_tree_node_destroy(binary_tree_node_t handle) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	free(node);
	return 0;
}

extern long binary_tree_node_degree(binary_tree_node_t handle) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
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

extern int binary_tree_node_swap(binary_tree_node_t handle1, binary_tree_node_t handle2) {
	struct binary_tree_node* node1 = (struct binary_tree_node*)handle1;
	struct binary_tree_node* node2 = (struct binary_tree_node*)handle2;
	if (node1 && node2) {
		void* tmp = node1->data;
		node1->data = node2->data;
		node2->data = tmp;
		return 0;
	}
	return 1;
}

extern void* binary_tree_node_get_info(binary_tree_node_t handle) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	if (node) {
		return node->data;
	}
}

extern binary_tree_node_t binary_tree_node_get_father(binary_tree_node_t handle) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	return node->father;
}

extern int binary_tree_node_set_father(binary_tree_node_t handle, binary_tree_node_t father) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	if (node) {
		node->father = father;
		return 0;
	}
	return 1;
}

extern binary_tree_node_t binary_tree_node_get_left_son(binary_tree_node_t handle) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	return node->left_son;
}

extern int binary_tree_node_set_left_son(binary_tree_node_t handle, binary_tree_node_t left_son) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	if (node) {
		node->left_son = left_son;
		return 0;
	}
	return 1;
}

extern inline binary_tree_node_t binary_tree_node_get_right_son(binary_tree_node_t handle) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	return node->right_son;
}

extern int binary_tree_node_set_right_son(binary_tree_node_t handle, binary_tree_node_t right_son) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	if (node) {
		node->right_son = right_son;
		return 0;
	}
	return 1;
}

extern int binary_tree_node_is_left_son(binary_tree_node_t handle) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	if (node) {
		struct binary_tree_node* father = node->father;
		if (father) {
			if (father->left_son == node) {
				return 1;
			}
		}
	}
	return 0;
}

extern int binary_tree_node_is_right_son(binary_tree_node_t handle) {
	struct binary_tree_node* node = (struct binary_tree_node*)handle;
	if (node) {
		struct binary_tree_node* father = node->father;
		if (father) {
			if (father->right_son == node) {
				return 1;
			}
		}
	}
	return 0;
}
