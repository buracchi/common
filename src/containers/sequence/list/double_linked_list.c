#define DS_IMPLEMENT_DOUBLE_LINKED_LIST
#define IMPLEMENT_ITERATOR
#include "double_linked_list.h"
#undef DS_IMPLEMENT_DOUBLE_LINKED_LIST
#undef DS_IMPLEMENT_LINKED_LIST

#include <stdlib.h>

/*******************************************************************************
*                                 Member types                                 *
*******************************************************************************/

struct _element {
	void* data;
	struct _element* next;
	struct _element* prev;
};

/*
* Return an initialized element object.

* @param	data	-	the element data.
* @param	next	-	the next element.
*
* @complexity	O(1).
*
* @return	the initialized element on success; NULL otherwise.
*/
static inline struct _element* element_init(const void* data,
	const struct _element* next, const struct _element* prev) {
	struct _element* element;
	element = malloc(sizeof * element);
	if (element) {
		element->data = data;
		element->next = next;
		element->prev = prev;
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
static inline struct _element* element_destroy(struct _element* element) {
	free(element);
	return 0;
}

/*******************************************************************************
*                         Double linked list iterator                          *
*******************************************************************************/

struct __iterator {
	struct _iterator;
	struct _ds_double_linked_list* list;
	struct _element* element;
};

/*
* @complexity	O(1).
*/
static struct __iterator* _iterator_init(
	const struct _ds_double_linked_list* list, const struct _element* element) {
	struct __iterator* iterator;
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
static inline void _iterator_destroy(const iterator_t this) {
	struct __iterator* _this = this;
	free(_this);
}

/*
* @complexity	O(1).
*/
static inline void* _iterator_data(const iterator_t this) {
	struct __iterator* _this = this;
	return _this->element->data;
}

/*
* @complexity	O(1).
*/
static inline iterator_t _iterator_next(iterator_t this) {
	struct __iterator* _this = this;
	_this->element = _this->element->next;
	return _this;
}

/*
* @complexity	O(1).
*/
static inline iterator_t _iterator_prev(iterator_t this) {
	struct __iterator* _this = this;
	_this->element = _this->element->prev;
	return _this;
}

/*
* @complexity	O(1).
*/
static inline bool _iterator_begin(const iterator_t this) {
	struct __iterator* _this = this;
	return _this->element == _this->list->head;
}

/*
* @complexity	O(1).
*/
static inline bool _iterator_end(const iterator_t this) {
	struct __iterator* _this = this;
	return _this->element == NULL;
}

static inline void iterator_ops_init(
	struct _ds_double_linked_list* list) {
	struct _iterator_ops* it_ops;
	it_ops = malloc(sizeof * it_ops);
	if (it_ops) {
		it_ops->_destroy = _iterator_destroy;
		it_ops->_data = _iterator_data;
		it_ops->_next = _iterator_next;
		it_ops->_prev = _iterator_prev;
		it_ops->_begin = _iterator_begin;
		it_ops->_end = _iterator_end;
	}
	list->it_ops = it_ops;
}

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

static inline void list_ops_init(struct _ds_double_linked_list* list);

extern ds_double_linked_list_t ds_double_linked_list_init(void) {
	struct _ds_double_linked_list* list;
	list = malloc(sizeof * list);
	if (list) {
		list_ops_init(list);
		iterator_ops_init(list);
		if (!list->it_ops) {
			free(list);
			return NULL;
		}
		list->size = 0;
		list->head = NULL;
		list->tail = NULL;
	}
	return list;
}

extern void ds_double_linked_list_destroy(const ds_double_linked_list_t* this) {
	struct _ds_double_linked_list* _this = this;
	while (_this->size > 0) {
		ds_double_linked_list_pop_front(this);
	}
	free(_this->it_ops);
	free(_this);
}

static inline void list_ops_init(struct _ds_double_linked_list* list) {
	// Member functions
	list->_destroy = ds_double_linked_list_destroy;
	// Element access
	list->_front = ds_double_linked_list_front;
	list->_back = ds_double_linked_list_back;
	// Iterators
	list->_begin = ds_double_linked_list_begin;
	list->_end = ds_double_linked_list_end;
	// Capacity
	list->_empty = ds_double_linked_list_empty;
	list->_size = ds_double_linked_list_size;
	// Modifiers
	list->_clear = ds_double_linked_list_clear;
	list->_insert = ds_double_linked_list_insert;
	list->_erase = ds_double_linked_list_erase;
	list->_push_front = ds_double_linked_list_push_front;
	list->_pop_front = ds_double_linked_list_pop_front;
	list->_push_back = ds_double_linked_list_push_back;
	list->_pop_back = ds_double_linked_list_pop_back;
	list->_resize = ds_double_linked_list_resize;
	list->_swap = ds_double_linked_list_swap;
	// Operations
	list->_merge = ds_double_linked_list_merge;
	list->_splice = ds_double_linked_list_splice;
	list->_remove = ds_double_linked_list_remove;
	list->_remove_if = ds_double_linked_list_remove_if;
	list->_reverse = ds_double_linked_list_reverse;
	list->_unique = ds_double_linked_list_unique;
	list->_sort = ds_double_linked_list_sort;
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

extern inline void* ds_double_linked_list_front(
	const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;
	return ((struct _element*)_this->head)->data;
}

extern inline void* ds_double_linked_list_back(
	const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;
	return ((struct _element*)_this->tail)->data;
}

/*******************************************************************************
*                                   Iterators                                  *
*******************************************************************************/

extern inline iterator_t ds_double_linked_list_begin(
	const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;
	return _iterator_init(_this, _this->head);
}

extern inline iterator_t ds_double_linked_list_end(
	const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;
	return _iterator_init(_this, NULL);
}

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

extern inline bool ds_double_linked_list_empty(
	const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;
	return _this->size == 0;
}

extern inline size_t ds_double_linked_list_size(
	const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;
	return _this->size;
}

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

extern inline void ds_double_linked_list_clear(
	const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;
	while (_this->size > 0) {
		ds_double_linked_list_pop_front(_this);
	}
}

extern iterator_t ds_double_linked_list_insert(
	const ds_double_linked_list_t this, const iterator_t position,
	const void* value) {
	struct _ds_double_linked_list* _this = this;
	struct __iterator* _position = position;

	struct _element* new_element;
	new_element = element_init(
		value,
		_position->element,
		_position->element->prev
	);
	if (new_element) {
		if (_position->element == _this->head) {
			if (_this->size == 0) {
				_this->tail = new_element;
			}
			else {
				((struct _element*)_this->head)->prev = new_element;
			}
			_this->head = new_element;
		}
		else {
			_position->element->prev->next = new_element;
			_position->element->prev = new_element;
		}
		_this->size++;
		return _iterator_init(_this, new_element);
	}
	return NULL;
}

extern iterator_t ds_double_linked_list_erase(
	const ds_double_linked_list_t this, const iterator_t position) {
	struct _ds_double_linked_list* _this = this;
	struct __iterator* _position = position;

	struct _element* follower;
	follower = _position->element->next;

	if (_position->element == _this->head) {
		struct _element* old_head;
		old_head = _this->head;
		_this->head = follower;
		if (_this->head == NULL) {
			_this->tail = NULL;
		}
		else {
			((struct _element*)_this->head)->prev = NULL;
		}
		element_destroy(old_head);
	}
	else {
		_position->element->prev->next = follower;
		if (follower) {
			follower->prev = _position->element->prev;
		}
		if (_position->element == _this->tail) {
			_this->tail = _position->element->prev;
		}
		element_destroy(_position->element);
	}
	_this->size--;
	return _iterator_init(_this, follower);
}

extern errno_t ds_double_linked_list_push_front(
	const ds_double_linked_list_t this, const void* value) {
	struct _ds_double_linked_list* _this = this;

	struct _element* new_element;
	new_element = element_init(value, _this->head, NULL);
	if (new_element) {
		_this->head = new_element;
		if (_this->size == 0) {
			_this->tail = new_element;
		}
		else {
			new_element->next->prev = new_element;
		}
		_this->size++;
		return 0;
	}
	return ENOMEM;
}

extern errno_t ds_double_linked_list_push_back(
	const ds_double_linked_list_t this, const void* value) {
	struct _ds_double_linked_list* _this = this;

	struct _element* new_element;
	new_element = element_init(value, NULL, _this->tail);
	if (new_element) {
		if (_this->size == 0) {
			_this->head = new_element;
		}
		else {
			((struct _element*)_this->tail)->next = new_element;
		}
		_this->tail = new_element;
		_this->size++;
		return 0;
	}
	return ENOMEM;
}

extern void ds_double_linked_list_pop_front(
	const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;

	if (_this->size == 1) {
		element_destroy(_this->head);
		_this->head = NULL;
		_this->tail = NULL;
	}
	else {
		struct _element* old_head;
		old_head = _this->head;
		_this->head = old_head->next;
		((struct _element*)_this->head)->prev = NULL;
		element_destroy(old_head);
	}
	_this->size--;
}

extern void ds_double_linked_list_pop_back(const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;

	if (_this->size == 1) {
		element_destroy(_this->head);
		_this->head = NULL;
		_this->tail = NULL;
	}
	else {
		_this->tail = ((struct _element*)_this->tail)->prev;
		element_destroy(((struct _element*)_this->tail)->next);
		((struct _element*)_this->tail)->next = NULL;
	}
	_this->size--;
}

extern errno_t ds_double_linked_list_resize(const ds_double_linked_list_t this,
	const size_t s, const void* value) {
	struct _ds_double_linked_list* _this = this;

	errno_t ret = 0;
	while (_this->size != s) {
		(_this->size > s) ?
			(ds_double_linked_list_pop_back(_this)) :
			(ret = ds_double_linked_list_push_back(_this, value));
		if (ret) {
			return ret;
		}
	}
	return 0;
}

extern void ds_double_linked_list_swap(const ds_double_linked_list_t this,
	const ds_double_linked_list_t other) {
	struct _ds_double_linked_list* _this = this;
	struct _ds_double_linked_list* _other = other;

	struct _ds_double_linked_list tmp;
	tmp.size = _this->size;
	tmp.head = _this->head;
	tmp.tail = _this->tail;

	_this->head = _other->head;
	_this->size = _other->size;
	_this->tail = _other->tail;
	_other->head = tmp.head;
	_other->size = tmp.size;
	_other->tail = tmp.tail;
}

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

/*
* TODO: implement ds_double_linked_list_sort()
*/
extern errno_t ds_double_linked_list_merge(const ds_double_linked_list_t this,
	const ds_double_linked_list_t other,
	errno_t(*comp)(const void* a, const void* b, bool* result)) {
	struct _ds_double_linked_list* _this = this;
	struct _ds_double_linked_list* _other = other;

	((struct _element*)_this->tail)->next = _other->head;
	_this->size += _other->size;
	_other->head = NULL;
	_other->tail = NULL;
	_other->size = 0;
	return ds_double_linked_list_sort(_this, comp);
}

extern void ds_double_linked_list_splice(const ds_double_linked_list_t this,
	const ds_double_linked_list_t other, const iterator_t position,
	const iterator_t first, const iterator_t last) {
	struct _ds_double_linked_list* _this = this;
	struct _ds_double_linked_list* _other = other;
	struct __iterator* _position = position;
	struct __iterator* _first = first;
	struct __iterator* _last = last;

	struct _element* first_prev = _first->element->prev;
	struct _element* last_prev = _last->element->prev;

	if (_position->element == _this->head) {
		_this->head = _first->element;
		_first->element->prev = NULL;
	}
	else {
		_position->element->prev->next = _first->element;
	}
	if (_first->element == _other->head) {
		_other->head = _last->element;
		_last->element->prev = NULL;
	}
	else {
		first_prev->next = _last->element;
		_last->element->prev = first_prev->next;
	}
	last_prev->next = _position->element;
	_position->element->prev = last_prev;
}

extern size_t ds_double_linked_list_remove(const ds_double_linked_list_t this,
	void* value) {
	struct _ds_double_linked_list* _this = this;

	struct __iterator* iterator;
	struct __iterator* tmp;
	int _removed = 0;

	iterator = ds_double_linked_list_begin(_this);
	while (!_iterator_end(iterator)) {
		if (iterator->element->data == value) {
			tmp = iterator;
			iterator = ds_double_linked_list_erase(_this, iterator);
			_iterator_destroy(tmp);
			_removed++;
		}
		else {
			_iterator_next(iterator);
		}
	}
	_iterator_destroy(iterator);
	return _removed;
}

extern errno_t ds_double_linked_list_remove_if(
	const ds_double_linked_list_t this,
	errno_t(*pred)(const void* a, bool* result), size_t* removed) {
	struct _ds_double_linked_list* _this = this;

	struct __iterator* iterator;
	struct __iterator* tmp;
	bool result;
	int _removed = 0;

	iterator = ds_double_linked_list_begin(_this);
	while (!_iterator_end(iterator)) {
		if (pred(iterator->element->data, &result)) {
			return 1;
		}
		if (result) {
			tmp = iterator;
			iterator = ds_double_linked_list_erase(_this, iterator);
			_iterator_destroy(tmp);
			_removed++;
		}
		else {
			_iterator_next(iterator);
		}
	}
	_iterator_destroy(iterator);
	if (removed) {
		*removed = _removed;
	}
	return 0;
}

extern void ds_double_linked_list_reverse(const ds_double_linked_list_t this) {
	struct _ds_double_linked_list* _this = this;

	if (_this->size == 0) {
		return;
	}

	struct _element* walk;
	struct _element* tmp;
	struct _element* new_head;

	new_head = _this->tail;
	_this->tail = _this->head;
	_this->head = new_head;

	walk = _this->head;
	while (walk) {
		tmp = walk->next;
		walk->next = walk->prev;
		walk->prev = tmp;
		walk = walk->next;
	}
}

static inline errno_t default_compeq(const void* a, const void* b,
	bool* result) {
	*result = (a == b);
	return 0;
}

extern errno_t ds_double_linked_list_unique(const ds_double_linked_list_t this,
	errno_t(*comp)(const void* a, const void* b, bool* result), int* removed) {
	struct _ds_double_linked_list* _this = this;

	struct __iterator* iterator1;
	struct __iterator* iterator2;
	struct __iterator* tmp;
	bool result;
	int _removed = 0;

	if (!comp) {
		comp = default_compeq;
	}
	iterator1 = ds_double_linked_list_begin(_this);
	iterator2 = _iterator_init(_this, NULL);
	while (!_iterator_end(iterator1)) {
		iterator2->element = iterator1->element->next;
		while (!_iterator_end(iterator2)) {
			errno_t ret;
			void* e1 = _iterator_data(iterator1);
			void* e2 = _iterator_data(iterator2);
			ret = comp(e1, e2, &result);
			if (ret) {
				return ret;
			}
			if (result) {
				tmp = iterator2;
				iterator2 = ds_double_linked_list_erase(_this, iterator2);
				_iterator_destroy(tmp);
				_removed++;
			}
			else {
				_iterator_next(iterator2);
			}
		}
		_iterator_next(iterator1);
	}
	_iterator_destroy(iterator1);
	_iterator_destroy(iterator2);

	if (removed) {
		*removed = _removed;
	}
	return 0;
}

static inline errno_t default_complt(const void* a, const void* b,
	bool* result) {
	*result = (a < b);
	return 0;
}

/*
* TODO: it needs an algorithm library
*/
extern int ds_double_linked_list_sort(const ds_double_linked_list_t this,
	int (*comp)(const void* a, const void* b, bool* result)) {
	struct _ds_double_linked_list* _this = this;

	return 1;
}
