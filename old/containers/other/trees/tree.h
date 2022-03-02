#pragma once

typedef void* ds_tree_t;
typedef void* ds_node_t;

/*
* Return an initialized tree object.
*
* @return the initialized tree on success; NULL otherwise.
*/
extern ds_tree_t ds_tree_init();

/*
* Destroy a tree object.
*
* @param tree - the tree to destroy.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_tree_destroy(const ds_tree_t tree);

/*
* Set the value referenced by number as a tree's node number.
*
* @param tree - the tree to check.
* @param number - the pointer that will reference the tree's node number.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_tree_nodes_number(const ds_tree_t tree, int* number);

extern ds_node_t ds_tree_get_root(const ds_tree_t tree);

extern void ds_tree_set_root(const ds_tree_t tree, const ds_node_t tree);

extern void ds_tree_insert_as_left_subtree(const ds_tree_t tree, const ds_node_t tree, const ds_tree_t subtree);

extern void ds_tree_insert_as_right_subtree(const ds_tree_t tree, const ds_node_t tree, const ds_tree_t subtree);

extern ds_tree_t ds_tree_cut(const ds_tree_t tree, const ds_node_t tree);

extern ds_tree_t ds_tree_cut_left(const ds_tree_t tree, const ds_node_t tree);

extern ds_tree_t ds_tree_cut_right(const ds_tree_t tree, const ds_node_t tree);





/*
* Set the value referenced by is_empty as true if the tree is empty or as flase
* otherwise.
*
* @param tree - the tree to check.
* @param is_empty - the pointer that will reference the state of the tree.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_tree_is_empty(const ds_tree_t tree, bool* is_empty);

/*
* Push an item onto a tree.
*
* @param tree - the tree to push the item onto.
* @param item - the item to push onto the tree.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_tree_push(const ds_tree_t tree, const void* item);

/*
* Pop the first item off a tree.
*
* @param tree - the tree to remove the top item from.
* @param item - the pointer that will reference the item, if the parameter
* is NULL the item is ignored.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_tree_pop(const ds_tree_t tree, void** item);

/*
* Return the item onto a tree.
*
* @param tree - the tree to return the top item from.
* @param item - the pointer that will reference the item.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_tree_top(const ds_tree_t tree, void** item);
