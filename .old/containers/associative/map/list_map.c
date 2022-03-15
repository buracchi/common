#define IMPLEMENT_COMMON_LIST_MAP
#define IMPLEMENT_COMMON_ITERATOR
#include "list_map.h"
#undef IMPLEMENT_COMMON_LIST_MAP
#undef IMPLEMENT_COMMON_ITERATOR

#include <stdlib.h>

#include "double_linked_list.h"
#include "pair.h"

/*******************************************************************************
*                              List Map iterator                               *
*******************************************************************************/

struct _iterator {
	struct _common_iterator;
	struct _common_double_linked_list* list;
	struct _element* element;
};

/*
* @complexity	O(1).
*/
static struct _iterator* iterator_init(
	const struct _common_double_linked_list* list, const struct _element* element) {
	struct _iterator* iterator;
	iterator = malloc(sizeof * iterator);
	if (iterator) {
		iterator->ops = list->it_ops;
		iterator->element = element;
	}
	return iterator;
}

/*
* @complexity	O(1).
*/
static inline void iterator_destroy(const common_iterator_t this) {
	struct _iterator* _this = this;
	free(_this);
}

/*
* @complexity	O(1).
*/
static inline void** iterator_data(const common_iterator_t this) {
	struct _iterator* _this = this;
	return &(_this->element->data);
}

/*
* @complexity	O(1).
*/
static inline common_iterator_t iterator_next(common_iterator_t this) {
	struct _iterator* _this = this;
	_this->element = _this->element->next;
	return _this;
}

/*
* @complexity	O(1).
*/
static inline common_iterator_t iterator_prev(common_iterator_t this) {
	struct _iterator* _this = this;
	_this->element = _this->element->prev;
	return _this;
}

/*
* @complexity	O(1).
*/
static inline bool iterator_begin(const common_iterator_t this) {
	struct _iterator* _this = this;
	return _this->element == _this->list->head;
}

/*
* @complexity	O(1).
*/
static inline bool iterator_end(const common_iterator_t this) {
	struct _iterator* _this = this;
	return _this->element == NULL;
}

static inline void iterator_ops_init(
	struct _common_double_linked_list* list) {
	struct _common_iterator_ops* it_ops;
	it_ops = malloc(sizeof * it_ops);
	if (it_ops) {
		it_ops->_destroy = iterator_destroy;
		it_ops->_data = iterator_data;
		it_ops->_next = iterator_next;
		it_ops->_prev = iterator_prev;
		it_ops->_begin = iterator_begin;
		it_ops->_end = iterator_end;
	}
	list->it_ops = it_ops;
}

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

static inline void map_ops_init(struct _common_list_map* map);

extern common_list_map_t common_list_map_init(void) {
	struct _common_list_map* map;
	map = malloc(sizeof * map);
	if (map) {
		list_ops_init(map);
		iterator_ops_init(map);
		if (!map->it_ops) {
			goto cleanup;
		}
		map->list = common_double_linked_list_init();
		if (!map->list) {
			goto cleanup;
		}
	}
	return list;
cleanup:
	free(map);
	return NULL;
}

extern void common_list_map_destroy(const common_list_map_t this) {
	struct _common_list_map* _this = this;
	common_list_destroy(_this->list);
	free(_this->it_ops);
	free(_this);
}

static inline void map_ops_init(struct _common_list_map* map) {
	// Member functions
	map->_destroy = common_double_linked_list_destroy;
	// Element access
	map->_front = common_double_linked_list_front;
	map->_back = common_double_linked_list_back;
	// Iterators
	map->_begin = common_double_linked_list_begin;
	map->_end = common_double_linked_list_end;
	// Capacity
	map->_empty = common_double_linked_list_empty;
	map->_size = common_double_linked_list_size;
	// Modifiers
	map->_clear = common_double_linked_list_clear;
	map->_insert = common_double_linked_list_insert;
	map->_erase = common_double_linked_list_erase;
	map->_push_front = common_double_linked_list_push_front;
	map->_pop_front = common_double_linked_list_pop_front;
	map->_push_back = common_double_linked_list_push_back;
	map->_pop_back = common_double_linked_list_pop_back;
	map->_resize = common_double_linked_list_resize;
	map->_swap = common_double_linked_list_swap;
	// Operations
	map->_merge = common_double_linked_list_merge;
	map->_splice = common_double_linked_list_splice;
	map->_remove = common_double_linked_list_remove;
	map->_remove_if = common_double_linked_list_remove_if;
	map->_reverse = common_double_linked_list_reverse;
	map->_unique = common_double_linked_list_unique;
	map->_sort = common_double_linked_list_sort;
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

extern errno_t common_list_map_at(const common_list_map_t this, const void* key,
	void** value) {
	struct _common_list_map* _this = this;
	//
	return 0;
}

/*******************************************************************************
*                                   Iterators                                  *
*******************************************************************************/

extern common_iterator_t common_list_map_begin(const common_list_map_t this);

extern common_iterator_t common_list_map_end(const common_list_map_t this);

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

extern bool common_list_map_empty(const common_list_map_t this);

extern size_t common_list_map_size(const common_list_map_t this);

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

extern void common_list_map_clear(const common_list_map_t this);

extern common_iterator_t common_list_map_insert(const common_list_map_t this,
	const void* key, const void* value);

extern common_iterator_t common_list_map_insert_or_assign(const common_list_map_t this,
	const void* key, const void* value);

extern common_iterator_t common_list_map_erase(const common_list_map_t this,
	const common_iterator_t position);

extern void common_list_map_swap(const common_list_map_t this, const common_list_map_t other);

extern errno_t common_list_map_merge(const common_list_map_t this,
	const common_list_map_t source,
	errno_t(*comp)(const void* a, const void* b, bool* result));

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

extern errno_t common_list_map_remove(const common_list_map_t this, const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	size_t* removed);

extern errno_t common_list_map_remove_if(const common_list_map_t this,
	errno_t(*pred)(const void* a, bool* result), size_t* removed);

/*******************************************************************************
*                                   Lookup                                     *
*******************************************************************************/

extern errno_t common_list_map_count(const common_list_map_t this, const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	size_t* count);

extern errno_t common_list_map_find(const common_list_map_t this, const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	common_iterator_t* iterator);

extern errno_t common_list_map_contains(const common_list_map_t this, const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	bool* exists);
