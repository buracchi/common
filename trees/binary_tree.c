#include "./trees/binary_tree.h"

#include <stdlib.h>

#include "./abstract/stack/stack.h"

struct binary_tree {
	binary_tree_node_t root;
	long n;
};

static int subtree_nodes_number(binary_tree_node_t node) {
	int nodes_number = 0;
	_stack_t stack = stack_init();
	if (node) {
		stack_push(stack, node);
		while (!stack_is_empty(stack)) {
			struct binary_tree_node* current_node;
			current_node = stack_pop(stack);
			nodes_number++;
			if (binary_tree_node_get_left_son(current_node)) {
				stack_push(stack, binary_tree_node_get_left_son(current_node));
			}
			if (binary_tree_node_get_right_son(current_node)) {
				stack_push(stack, binary_tree_node_get_right_son(current_node));
			}
		}
	}
	stack_destroy(stack);
	return nodes_number;
}

extern binary_tree_t binary_tree_init() {
	struct binary_tree* tree;
	if ((tree = malloc(sizeof(struct binary_tree))) == NULL) {
		return NULL;
	}
	tree->root = NULL;
	tree->n = 0;
	return tree;
}

extern int binary_tree_destroy(binary_tree_t handle) {
	struct binary_tree* tree = (struct binary_tree*)handle;
	struct binary_tree* left_subtree;
	struct binary_tree* right_subtree;
	left_subtree = binary_tree_cut_left(tree, tree->root);
	if (!left_subtree) {
		return 1;
	}
	right_subtree = binary_tree_cut_right(tree, tree->root);
	if (!right_subtree) {
		return 1;
	}
	if (left_subtree->root) {
		if (binary_tree_destroy(left_subtree)) {
			return 1;
		}
	}
	free(left_subtree);
	if (right_subtree->root) {
		if (binary_tree_destroy(right_subtree)) {
			return 1;
		}
	}
	free(right_subtree);
	if (binary_tree_node_destroy(tree->root)) {
		return 1;
	}
	free(tree);
	return 0;
}

extern inline long binary_tree_nodes_number(binary_tree_t handle) {
	struct binary_tree* tree = (struct binary_tree*)handle;
	return tree->n;
}

extern inline binary_tree_node_t binary_tree_get_root(binary_tree_t handle) {
	struct binary_tree* tree = (struct binary_tree*)handle;
	return tree->root;
}

extern inline void binary_tree_set_root(binary_tree_t handle, binary_tree_node_t node) {
	struct binary_tree* tree = (struct binary_tree*)handle;
	tree->root = node;
	tree->n = subtree_nodes_number(node);
}

extern void binary_tree_insert_as_left_subtree(binary_tree_t handle, binary_tree_node_t node, binary_tree_t subtree) {
	struct binary_tree* tree = (struct binary_tree*)handle;
	struct binary_tree* binary_subtree = (struct binary_tree*)subtree;
	if (binary_subtree->root) {
		binary_tree_node_set_father(binary_subtree->root, node);
	}
	binary_tree_node_set_left_son(node, binary_subtree->root);
	tree->n += subtree_nodes_number(node);
}

extern void binary_tree_insert_as_right_subtree(binary_tree_t handle, binary_tree_node_t node, binary_tree_t subtree) {
	struct binary_tree* tree = (struct binary_tree*)handle;
	struct binary_tree* binary_subtree = (struct binary_tree*)subtree;
	if (binary_subtree->root) {
		binary_tree_node_set_father(binary_subtree->root, node);
	}
	binary_tree_node_set_right_son(node, binary_subtree->root);
	tree->n += subtree_nodes_number(node);
}

extern binary_tree_t binary_tree_cut(binary_tree_t handle, binary_tree_node_t node) {
	struct binary_tree* tree = (struct binary_tree*)handle;

	if (node) {
		binary_tree_node_t father = binary_tree_node_get_father(node);

		if (node == binary_tree_get_root(tree)) {
			tree->root = NULL;
			tree->n = 0;
		}
		else if (node == binary_tree_node_get_left_son(father)) {
			if (binary_tree_node_degree(node) == 0) {
				binary_tree_node_set_left_son(father, NULL);
				tree->n--;
			}
			else {
				return binary_tree_cut_left(tree, node);
			}
		}
		else if (node == binary_tree_node_get_right_son(father)) {
			if (binary_tree_node_degree(node) == 0) {
				binary_tree_node_set_right_son(father, NULL);
				tree->n--;
			}
			else {
				return binary_tree_cut_right(tree, node);
			}
		}
	}
	binary_tree_t cutted = binary_tree_init();
	if (cutted) {
		binary_tree_set_root(cutted, node);
	}
	return cutted;
}

extern binary_tree_t binary_tree_cut_left(binary_tree_t handle, binary_tree_node_t node) {
	struct binary_tree* tree = (struct binary_tree*)handle;
	struct binary_tree* new_tree;
	binary_tree_t left_son = binary_tree_node_get_left_son(node);
	if ((new_tree = binary_tree_init()) == NULL) {
		return NULL;
	}
	binary_tree_set_root(new_tree, left_son);
	tree->n -= subtree_nodes_number(left_son);
	binary_tree_node_set_left_son(node, NULL);
	return new_tree;
}

extern binary_tree_t binary_tree_cut_right(binary_tree_t handle, binary_tree_node_t node) {
	struct binary_tree* tree = (struct binary_tree*)handle;
	struct binary_tree* new_tree;
	binary_tree_node_t right_son = binary_tree_node_get_right_son(node);
	if ((new_tree = binary_tree_init()) == NULL) {
		return NULL;
	}
	binary_tree_set_root(new_tree, right_son);
	tree->n -= subtree_nodes_number(right_son);
	binary_tree_node_set_right_son(node, NULL);
	return new_tree;
}
