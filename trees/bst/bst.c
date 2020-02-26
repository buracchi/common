#include "./trees/bst/bst.h"

#include <stdlib.h>

#include "./abstract/stack/stack.h"

struct bst {
	bst_node_t root;
	int n;
	bst_comparison_function* compare;
};

static int subtree_nodes_number(bst_node_t node) {
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

static int defualt_comparison_function(const void* key1, const void* key2) {
	if (key1 < key2) {
		return -1;
	}
	else if (key1 > key2) {
		return 1;
	}
	return 0;
}

extern bst_t bst_init(bst_comparison_function* comparison_function) {
	struct bst* tree;
	if ((tree = malloc(sizeof(struct bst))) == NULL) {
		return NULL;
	}
	tree->root = NULL;
	tree->n = 0;
	tree->compare = comparison_function ? comparison_function : &defualt_comparison_function;
	return tree;
}

extern int bst_destroy(bst_t handle) {
	struct bst* tree = (struct bst*)handle;
	struct bst* left_subtree;
	struct bst* right_subtree;
	left_subtree = bst_cut_left(tree, tree->root);
	if (!left_subtree) {
		return 1;
	}
	right_subtree = bst_cut_right(tree, tree->root);
	if (!right_subtree) {
		return 1;
	}
	if (left_subtree->root) {
		if (bst_destroy(left_subtree)) {
			return 1;
		}
	}
	free(left_subtree);
	if (right_subtree->root) {
		if (bst_destroy(right_subtree)) {
			return 1;
		}
	}
	free(right_subtree);
	if (bst_node_destroy(tree->root)) {
		return 1;
	}
	free(tree);
	return 0;
}

extern inline long bst_nodes_number(bst_t handle) {
	struct bst* tree = (struct bst*)handle;
	return tree->n;
}

extern inline bst_node_t bst_get_root(bst_t handle) {
	struct bst* tree = (struct bst*)handle;
	return tree->root;
}

extern inline void bst_set_root(bst_t handle, bst_node_t node) {
	struct bst* tree = (struct bst*)handle;
	tree->root = node;
	tree->n = subtree_nodes_number(node);
}

extern void bst_insert_as_left_subtree(bst_t handle, bst_node_t node, bst_t subtree) {
	struct bst* tree = (struct bst*)handle;
	struct bst* bst_subtree = (struct bst*)subtree;
	if (bst_subtree->root) {
		bst_node_set_father(bst_subtree->root, node);
	}
	bst_node_set_left_son(node, bst_subtree->root);
	tree->n += subtree_nodes_number(node);
}

extern void bst_insert_as_right_subtree(bst_t handle, bst_node_t node, bst_t subtree) {
	struct bst* tree = (struct bst*)handle;
	struct bst* bst_subtree = (struct bst*)subtree;
	if (bst_subtree->root) {
		bst_node_set_father(bst_subtree->root, node);
	}
	bst_node_set_right_son(node, bst_subtree->root);
	tree->n += subtree_nodes_number(node);
}

extern bst_t bst_cut(bst_t handle, bst_node_t node) {
	struct bst* tree = (struct bst*)handle;
	if (node) {
		bst_t father = bst_node_get_father(node);

		if (node == bst_get_root(tree)) {
			tree->root = NULL;
			tree->n = 0;
		}
		else if (node == bst_node_get_left_son(father)) {
			if (bst_node_degree(node) == 0) {
				bst_node_set_left_son(father, NULL);
				tree->n--;
			}
			else {
				return bst_cut_left(tree, node);
			}
		}
		else if (node == bst_node_get_right_son(father)) {
			if (bst_node_degree(node) == 0) {
				bst_node_set_right_son(father, NULL);
				tree->n--;
			}
			else {
				return bst_cut_right(tree, node);
			}
		}
	}
	bst_t cutted = bst_init(tree->compare);
	if (cutted) {
		bst_set_root(cutted, node);
	}
	return cutted;
}

extern bst_t bst_cut_left(bst_t handle, bst_node_t node) {
	struct bst* tree = (struct bst*)handle;
	struct bst* new_tree;
	bst_t left_son = bst_node_get_left_son(node);
	if ((new_tree = bst_init(tree->compare)) == NULL) {
		return NULL;
	}
	bst_set_root(new_tree, left_son);
	tree->n -= subtree_nodes_number(left_son);
	bst_node_set_left_son(node, NULL);
	return new_tree;
}

extern bst_t bst_cut_right(bst_t handle, bst_node_t node) {
	struct bst* tree = (struct bst*)handle;
	struct bst* new_tree;
	bst_t right_son = bst_node_get_right_son(node);
	if ((new_tree = bst_init(tree->compare)) == NULL) {
		return NULL;
	}
	bst_set_root(new_tree, right_son);
	tree->n -= subtree_nodes_number(right_son);
	bst_node_set_right_son(node, NULL);
	return new_tree;
}

extern bst_t bst_cut_one_son_node(bst_t handle, bst_node_t node) {
	struct bst* tree = (struct bst*)handle;
	bst_t cutted_tree;
	bst_node_t son;
	if (!(son = bst_node_get_left_son(node))) {
		son = bst_node_get_right_son(node);
	}
	if (!son) {
		cutted_tree = bst_cut(tree, node);
	}
	else {
		bst_node_swap(node, son);
		cutted_tree = bst_cut(tree, son);
		bst_insert_as_left_subtree(tree, node, bst_cut(cutted_tree, bst_node_get_left_son(son)));
		bst_insert_as_right_subtree(tree, node, bst_cut(cutted_tree, bst_node_get_right_son(son)));
		//memory leack
	}
	return cutted_tree;
}

extern void bst_insert_single_node_tree(bst_t handle, void* key, bst_t new_tree) {
	struct bst* tree = (struct bst*)handle;
	int cmp;
	if (bst_get_root(tree) == NULL) {
		bst_set_root(tree, bst_get_root(new_tree));
		//memory leack
	}
	else {
		bst_node_t current = bst_get_root(tree);
		bst_node_t prev = NULL;
		while (current) {
			prev = current;
			cmp = tree->compare(key, bst_node_get_key(current));
			if (cmp < 1) {
				current = bst_node_get_left_son(current);
			}
			else {
				current = bst_node_get_right_son(current);
			}
		}
		cmp = tree->compare(key, bst_node_get_key(current));
		if (cmp < 1) {
			bst_insert_as_left_subtree(tree, prev, new_tree);
		}
		else {
			bst_insert_as_right_subtree(tree, prev, new_tree);
		}
	}
}

extern bst_node_t bst_search_node(bst_t handle, void* key) {
	struct bst* tree = (struct bst*)handle;
	bst_node_t current = bst_get_root(tree);
	int cmp;
	while (current) {
		cmp = tree->compare(key, bst_node_get_key(current));
		if (!cmp) {
			return current;
		}
		else if (cmp == -1) {
			current = bst_node_get_left_son(current);
		}
		else {
			current = bst_node_get_right_son(current);
		}
	}
	return NULL;
}

extern void* bst_search(bst_t handle, void* key) {
	struct bst* tree = (struct bst*)handle;
	return bst_node_get_value(bst_search_node(tree, key));
}

extern int bst_insert(bst_t handle, void* key, void* value) {
	struct bst* tree = (struct bst*)handle;
	bst_t new_tree = bst_init(tree->compare);
	bst_set_root(new_tree, bst_node_init(key, value));
	bst_insert_single_node_tree(tree, key, new_tree);
	return 0;
}

extern void bst_delete(bst_t handle, void* key) {
	struct bst* tree = (struct bst*)handle;
	bst_node_t node;
	if (node = bst_search_node(tree, key)) {
		if (bst_node_degree(node) < 2) {
			bst_cut_one_son_node(tree, node);
		}
		else {
			bst_node_t pred = bst_node_get_pred(node);
			bst_node_swap(node, pred);
			bst_cut_one_son_node(tree, pred);
		}
	}
}
