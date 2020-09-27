#include "sequence/list.h"

#include <stdlib.h>

#define THIS ((struct linked_list*)this)
#define ELEMENT ((struct element*)element)

/*******************************************************************************
*                                 Member types                                 *
*******************************************************************************/

struct element {
	void* data;
	struct element* next;
};

struct linked_list {
	int size;
	struct element* head;
	struct element* tail;
	void (*destroy)(void* data);
};

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern ds_list_t ds_list_init(void (*destroy)(void*)) {
	struct linked_list* list;
	list = malloc(sizeof(struct linked_list));
	if (list) {
		list->size = 0;
		list->head = NULL;
		list->tail = NULL;
		list->destroy = destroy;
	}
	return list;
}

/*
* @complexity	O(n).
*/
extern int ds_list_destroy(const ds_list_t this) {
	while (THIS->size > 0) {
		if (THIS->destroy) {
			struct element* element;
			if (ds_list_get_front(this, &element)) {
				return 1;
			}
			THIS->destroy(element->data);
		}
		if (ds_list_pop_front(this)) {
			return 1;
		}
	}
	free(THIS);
	return 0;
}

/*
* Return an initialized element object.

* @complexity	O(1).
* 
* @return	the initialized element on success; NULL otherwise.
*/
static inline struct element* element_init() {
	struct element* element;
	element = malloc(sizeof(struct linked_list));
	return element;
}

/*
* Destroy a list object.
*
* @param	this	-	the list object, NULL causes undefined behavior.
* 
* @complexity	O(1).
* 
* @return	0 on success; non-zero otherwise.
*/
static inline struct element* element_destroy(struct element* this) {
	free(THIS);
	return 0;
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern inline int ds_list_get_front(const ds_list_t this,
	ds_list_element_t* element) {
	*element = THIS->head;
	return 0;
}

/*
* @complexity	O(1).
*/
extern inline int ds_list_get_back(const ds_list_t this,
	ds_list_element_t* element) {
	*element = THIS->tail;
	return 0;
}

/*
* @complexity	O(1).
*/
extern inline int ds_list_get_element_next(const ds_list_element_t element,
	ds_list_element_t* next) {
	*next = ELEMENT->next;
	return 0;
}

/*
* @complexity	O(1).
*/
extern inline int ds_list_get_element_value(const ds_list_element_t element,
	void** value) {
	*value = ELEMENT->data;
	return 0;
}

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern int ds_list_is_empty(const ds_list_t this, bool* is_empty) {
	*is_empty = (THIS->size == 0);
	return 0;
}

/*
* @complexity	O(1).
*/
extern int ds_list_get_size(const ds_list_t this, int* size) {
	*size = THIS->size;
}

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

/*
* @complexity	O(n).
*/
extern int ds_list_clear(const ds_list_t this) {
	while (THIS->size > 0) {
		if (ds_list_pop_front(this)) {
			return 1;
		}
	}
	return 0;
}


/*
* @complexity	O(n).
*/
extern int ds_list_insert(const ds_list_t this, const ds_list_element_t element,
	const void* value) {
	struct element* new_element = element_init();
	if (new_element) {
		new_element->data = value;
		new_element->next = element;
		//TODO
	}
	return 1;
}

/*
* @complexity	O(n).
*/
extern int ds_list_erase(const ds_list_t this,
	const ds_list_element_t element) {
	struct element** indirect;
	indirect = &THIS->head;
	while ((*indirect) != element) {
		indirect = &(*indirect)->next;
	}
	*indirect = ELEMENT->next;
	element_destroy(element);
}

/*
* @complexity	O(1).
*/
extern int ds_list_push_front(const ds_list_t this, const void* value) {
	struct element* new_element = element_init();
	if (new_element) {
		new_element->data = value;
		new_element->next = THIS->head;
		THIS->head = new_element;
	}
	return 1;
}

/*
* @complexity	O(1).
*/
extern int ds_list_pop_front(const ds_list_t this) {
	struct element* new_head;
	new_head = THIS->head->next;
	element_destroy(THIS->head);
	THIS->head = new_head;
}

/*
* @complexity	O(1).
*/
extern int ds_list_push_back(const ds_list_t this, const void* value) {

}

/*
* @complexity	O(1).
*/
extern int ds_list_pop_back(const ds_list_t this) {

}

extern int ds_list_resize(const ds_list_t this, int size, void* value) {

}

extern int ds_list_swap(const ds_list_t this, const ds_list_t other) {

}


/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

extern int ds_list_merge(const ds_list_t this, const ds_list_t other,
	int (*comp)(const void* a, const void* b, bool* result));

extern int ds_list_splice(const ds_list_t this, const ds_list_t other,
	const ds_list_element_t element, const ds_list_element_t first,
	const ds_list_element_t last);

extern int ds_list_remove_if(const ds_list_t this,
	int (*p)(const void* a, bool* result));

extern int ds_list_reverse(const ds_list_t this);

extern int ds_list_unique(const ds_list_t this,
	int (*comp)(const void* a, const void* b, bool* result));

extern int ds_list_sort(const ds_list_t this,
	int (*comp)(const void* a, const void* b, bool* result));
