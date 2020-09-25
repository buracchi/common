#pragma once

/*
* Dictionary data structure
*/

typedef void* ds_dictionary_t;

struct kv_pair {
	void* key;
	void* value;
};

/*
* Return an initialized dictionary object.
* 
* @return the initialized object or NULL on error.
*/
ds_dictionary_t dictionary_init();

/*
* Destroy a dictionary object.
*
* @param dictionary - the dictionary object to destroy.
*/
void dictionary_destroy(const ds_dictionary_t dictionary);

/*
* Add a new (key,value) pair to the collection,
* mapping the new key to its new value.
* 
* @param dictionary
* @param key
* @param value
* @return a non negative value on succcess, 0 on error.
*/
int dictionary_insert(const ds_dictionary_t dictionary, void* key, void* value);

/*
* Remove a (key,value) pair from the collection,
* unmapping a given key from its value.
* 
* @param key
* @return a non negative value on succcess, 0 on error.
*/
int dictionary_delete(const ds_dictionary_t dictionary, void* key);

/*
* Find the value (if any) that is bound to a given key.
*
* @param key
* @param value - the destination where insert the value.
* @return a non negative value on succcess, 0 on error.
*/
int dictionary_search(const ds_dictionary_t dictionary, void*, key void** value);
