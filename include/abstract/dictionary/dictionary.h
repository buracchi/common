#pragma once

typedef void* ds_dictionary_t;

/*
* Return an initialized dictionary object.
*
* @return the initialized dictionary on success; NULL otherwise.
*/
ds_dictionary_t ds_dictionary_init();

/*
* Destroy a dictionary object.
*
* @param dictionary - the dictionary to destroy.
* @return 0 on success; non-zero otherwise.
*/
int ds_dictionary_destroy(const ds_dictionary_t dictionary);

/*
* Add a new (key, value) pair to the collection,
* mapping the new key to its new value.
* 
* @param dictionary - the dictionary to insert the (key, element) pair into.
* @param key - the key to insert into the dictionary.
* @param value - the value to insert into the dictionary.
* @return 0 on success; non-zero otherwise.
*/
int ds_dictionary_insert(const ds_dictionary_t dictionary, void* value, void* key);

/*
* Remove a (key,value) pair from the collection, unmapping a given key from
* its value.
* 
* @param key - the key that identify the (key, value) pair in the dictionary.
* @return 0 on success; non-zero otherwise.
*/
int ds_dictionary_delete(const ds_dictionary_t dictionary, void* key);

/*
* Return the value (if any) that is bound to a given key.
*
* @param key - the key that identify the (key, value) pair in the dictionary.
* @param value - the pointer that will reference the value.
* @return 0 on success; non-zero otherwise.
*/
int ds_dictionary_search(const ds_dictionary_t dictionary, void* key, void** value);
