#pragma once

typedef void* dictionary_t;

/*
* Return an initialized dictionary object.
*/
dictionary_t dictionary_init();

/*
* Destroy a dictionary object.
*/
void dictionary_destroy(const dictionary_t dictionary);

int dictionary_insert(const dictionary_t dictionary, void* key, void* value);

int dictionary_delete(const dictionary_t dictionary, void* key);

void* dictionary_search(const dictionary_t dictionary, void* key);
