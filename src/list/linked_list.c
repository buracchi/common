#include "sequence/list.h"

#include <stdlib.h>

/*
* Casts defined as macros for shortness.
*/
#define THIS ((struct linked_list*)this)
#define OTHER ((struct linked_list*)other)
#define ELEMENT ((struct element*)element)
#define FIRST ((struct element*)first)
#define LAST ((struct element*)last)

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

* @param	data	-	the element data.
* @param	next	-	the next element.
*
* @complexity	O(1).
*
* @return	the initialized element on success; NULL otherwise.
*/
static inline struct element* element_init(void* data, struct element* next) {
	struct element* element;
	element = malloc(sizeof(struct linked_list));
	if (element) {
		element->data = data;
		element->next = next;
	}
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
static inline struct element* element_destroy(struct element* element) {
	free(element);
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

static inline struct element* get_previous_element(
	const struct linked_list* this, const struct element* element) {
	struct element* walk;
	struct element* previous;
	walk = this->head;
	while (walk->next != element) {
		walk = walk->next;
	}
	previous = walk;
	return previous;
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
	return 0;
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
	if (THIS->head == element) {
		return ds_list_push_front(this, value);
	}
	struct element* new_element;
	new_element = element_init(value, element);
	if (new_element) {
		struct element** indirect;
		indirect = &(THIS->head);
		while ((*indirect)->next != element) {
			indirect = &((*indirect)->next);
		}
		(*indirect)->next = new_element;
		THIS->size++;
		return 0;
	}
	return 1;
}

/*
* @complexity	O(n).
*/
extern int ds_list_erase(const ds_list_t this,
	const ds_list_element_t element) {
	if (THIS->head == element) {
		return ds_list_pop_front(this);
	}
	struct element** pprev;
	pprev = &(THIS->head);
	while ((*pprev)->next != element) {
		pprev = &((*pprev)->next);
	}
	(*pprev)->next = ELEMENT->next;
	if (THIS->tail == element) {
		THIS->tail = *pprev;
	}
	element_destroy(element);
	THIS->size--;
	return 0;
}

/*
* @complexity	O(1).
*/
extern int ds_list_push_front(const ds_list_t this, const void* value) {
	struct element* new_element;
	new_element = element_init(value, THIS->head);
	if (new_element) {
		THIS->head = new_element;
		if (THIS->tail == NULL) {
			THIS->tail = new_element;
		}
		THIS->size++;
		return 0;
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
	if (THIS->head == NULL) {
		THIS->tail = NULL;
	}
	THIS->size--;
	return 0;
}

/*
* @complexity	O(1).
*/
extern int ds_list_push_back(const ds_list_t this, const void* value) {
	struct element* new_element;
	new_element = element_init(value, NULL);
	if (new_element) {
		if (THIS->head == NULL) {
			THIS->head = new_element;
			THIS->tail = new_element;
		}
		else {
			THIS->tail->next = new_element;
			THIS->tail = new_element;
		}
		THIS->size++;
		return 0;
	}
	return 1;
}

/*
* @complexity	O(n).
*/
extern inline int ds_list_pop_back(const ds_list_t this) {
	return ds_list_erase(this, THIS->tail);
}

/*
* @complexity	O(n + size).
*/
extern int ds_list_resize(const ds_list_t this, const int count,
	const void* value) {
	if (THIS->size < count) {
		for (int i = 0; i < count - THIS->size; i++) {
			ds_list_push_back(this, value);
		}
		return 0;
	}
	if (THIS->size > count) {
		for (int i = 0; i < THIS->size - count; i++) {
			ds_list_pop_back(this);
		}
		return 0;
	}
	return 0;
}

/*
* @complexity	O(1).
*/
extern int ds_list_swap(const ds_list_t this, const ds_list_t other) {
	struct linked_list tmp = { THIS->size, THIS->head, THIS->tail };
	THIS->head = OTHER->head;
	THIS->size = OTHER->size;
	THIS->tail = OTHER->tail;
	OTHER->head = tmp.head;
	OTHER->size = tmp.size;
	OTHER->tail = tmp.tail;
	return 0;
}


/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

/*
* @complexity	O(log(n)).
*/
extern int ds_list_merge(const ds_list_t this, const ds_list_t other,
	int (*comp)(const void* a, const void* b, bool* result)) {
	THIS->tail->next = OTHER->head;
	THIS->size += OTHER->size;
	OTHER->head = NULL;
	OTHER->tail = NULL;
	OTHER->size = 0;
	return ds_list_sort(this, comp);
}

/*
* @complexity	O(n + m).
*/
extern int ds_list_splice(const ds_list_t this, const ds_list_t other,
	const ds_list_element_t element, const ds_list_element_t first,
	const ds_list_element_t last) {
	if (element == THIS->head) {
		THIS->head = first;
	}
	else {
		get_previous_element(this, element)->next = first;
	}
	if (first == OTHER->head) {
		OTHER->head = last;
	}
	else {
		get_previous_element(other, first)->next = last;
	}
	get_previous_element(other, last)->next = element;
	return 0;
}

/*
*@complexity	O(n).
*/
extern int ds_list_remove_if(const ds_list_t this,
	int (*p)(const void* a, bool* result)) {
	struct element* walk;
	struct element* tmp;
	bool result;

	walk = THIS->head;
	for (int i = 0; i < THIS->size; i++) {
		tmp = walk;
		walk = walk->next;
		if (p(tmp->data, &result)) {
			return 1;
		}
		if (result && ds_list_erase(this, tmp)) {
			return 1;
		}
	}
	return 0;
}

/*
*@complexity	O(n).
*/
extern int ds_list_reverse(const ds_list_t this) {
	struct element* walk;
	struct element* new_head;

	walk = THIS->head;
	for (int i = 0; i < THIS->size - 1; i++) {
		new_head = walk->next;
		walk->next = new_head->next;
		new_head->next = THIS->head;
		THIS->head = new_head;
	}
	THIS->tail = walk;
	return 0;
}

static inline int default_compeq(const void* a, const void* b, bool* result) {
	*result = (a == b);
	return 0;
}

/*
*@complexity	O(n^2).
*/
extern int ds_list_unique(const ds_list_t this,
	int (*comp)(const void* a, const void* b, bool* result)) {
	struct element* iterator1;
	struct element* iterator2;
	bool res;
	if (!comp) {
		comp = default_compeq;
	}
	iterator1 = THIS->head;
	while (iterator1) {
		iterator2 = iterator1->next;
		while (iterator2) {
			struct element* tmp;
			tmp = iterator2->next;
			if (comp(iterator1->data, iterator2->data, &res)) {
				return 1;
			}
			if (res && ds_list_erase(this, iterator2)) {
				return 1;
			}
			iterator2 = tmp;
		}
		iterator1 = iterator1->next;
	}
	return 0;
}

static inline int default_complt(const void* a, const void* b, bool* result) {
	*result = (a < b);
	return 0;
}

/*
*
* TODO: it needs an algorithm library
*@complexity	O(n * log(n)).
*/
extern int ds_list_sort(const ds_list_t this,
	int (*comp)(const void* a, const void* b, bool* result)) {
	return 1;
}
