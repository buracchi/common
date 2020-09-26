#pragma once

/*
* Implement dictionary
*/

typedef void* ds_list_t;

/*
* Return an initialized list object.
*
* @return the initialized list on success; NULL otherwise.
*/
ds_list_t ds_list_init();

/*
* Destroy a list object.
*
* @param list - the list to destroy.
* @return 0 on success; non-zero otherwise.
*/
void ds_list_destroy(const ds_list_t list);

/*
* Add a new (key, value) pair to the collection,
* mapping the new key to its new value.
*
* @param list - the list to insert the (key, element) pair into.
* @param key - the key to insert into the list.
* @param value - the value to insert into the list.
* @return 0 on success; non-zero otherwise.
*/
int ds_list_insert(const ds_list_t list, void* value, void* key);

/*
* Remove a (key,value) pair from the collection, unmapping a given key from
* its value.
*
* @param key - the key that identify the (key, value) pair in the list.
* @return 0 on success; non-zero otherwise.
*/
int ds_list_delete(const ds_list_t list, void* key);

/*
* Return the value (if any) that is bound to a given key.
*
* @param key - the key that identify the (key, value) pair in the list.
* @param value - the pointer that will reference the value.
* @return 0 on success; non-zero otherwise.
*/
int ds_list_search(const ds_list_t list, void* key, void** value);
