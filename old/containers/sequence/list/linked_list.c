#define IMPLEMENT_COMMON_LINKED_LIST
#define IMPLEMENT_COMMON_ITERATOR
#include "linked_list.h"
#undef IMPLEMENT_COMMON_LINKED_LIST
#undef IMPLEMENT_COMMON_ITERATOR

#include <stdlib.h>

/*******************************************************************************
*                                 Member types                                 *
*******************************************************************************/

struct _element {
	void* data;
	struct _element* next;
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
	const struct _element* next) {
	struct _element* element;
	element = malloc(sizeof * element);
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
static inline struct _element* element_destroy(struct _element* element) {
	free(element);
	return 0;
}

/*
* Get previous element in the list.
*
* @complexity	O(n).
*/
static inline struct _element* get_previous_element(
	const struct _common_linked_list* this, const struct _element* element) {
	struct _element* walk;
	struct _element* previous;
	walk = this->head;
	while (walk->next != element) {
		walk = walk->next;
	}
	previous = walk;
	return previous;
}

/*******************************************************************************
*                             Linked list iterator                             *
*******************************************************************************/

struct _iterator {
	struct _common_iterator;
	struct _common_linked_list* list;
	struct _element* element;
};

/*
* @complexity	O(1).
*/
static struct _iterator* iterator_init(
	const struct _common_linked_list* list, const struct _element* element) {
	struct _iterator* iterator;
	iterator = malloc(sizeof * iterator);
	if (iterator) {
		iterator->ops = list->it_ops;
		iterator->list = list;
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
* @complexity	O(n).
*/
static inline common_iterator_t iterator_prev(common_iterator_t this) {
	struct _iterator* _this = this;
	_this->element = get_previous_element(_this->list, _this->element);
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
	struct _common_linked_list* list) {
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

static inline void list_ops_init(struct _common_linked_list* list);

extern common_linked_list_t common_linked_list_init(void) {
	struct _common_linked_list* list;
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

extern void common_linked_list_destroy(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;
	while (_this->size > 0) {
		common_linked_list_pop_front(this);
	}
	free(_this->it_ops);
	free(_this);
}

static inline void list_ops_init(struct _common_linked_list* list) {
	// Member functions
	list->_destroy = common_linked_list_destroy;
	// Element access
	list->_front = common_linked_list_front;
	list->_back = common_linked_list_back;
	// Iterators
	list->_begin = common_linked_list_begin;
	list->_end = common_linked_list_end;
	// Capacity
	list->_empty = common_linked_list_empty;
	list->_size = common_linked_list_size;
	// Modifiers
	list->_clear = common_linked_list_clear;
	list->_insert = common_linked_list_insert;
	list->_erase = common_linked_list_erase;
	list->_push_front = common_linked_list_push_front;
	list->_pop_front = common_linked_list_pop_front;
	list->_push_back = common_linked_list_push_back;
	list->_pop_back = common_linked_list_pop_back;
	list->_resize = common_linked_list_resize;
	list->_swap = common_linked_list_swap;
	// Operations
	list->_merge = common_linked_list_merge;
	list->_splice = common_linked_list_splice;
	list->_remove = common_linked_list_remove;
	list->_remove_if = common_linked_list_remove_if;
	list->_reverse = common_linked_list_reverse;
	list->_unique = common_linked_list_unique;
	list->_sort = common_linked_list_sort;
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

extern inline void* common_linked_list_front(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;
	return ((struct _element*)_this->head)->data;
}

extern inline void* common_linked_list_back(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;
	return ((struct _element*)_this->tail)->data;
}

/*******************************************************************************
*                                   Iterators                                  *
*******************************************************************************/

extern inline common_iterator_t common_linked_list_begin(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;
	return iterator_init(_this, _this->head);
}

extern inline common_iterator_t common_linked_list_end(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;
	return iterator_init(_this, NULL);
}

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

extern inline bool common_linked_list_empty(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;
	return _this->size == 0;
}

extern inline size_t common_linked_list_size(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;
	return _this->size;
}

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

extern inline void common_linked_list_clear(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;
	while (_this->size > 0) {
		common_linked_list_pop_front(_this);
	}
}

extern common_iterator_t common_linked_list_insert(const common_linked_list_t this,
	const common_iterator_t position, const void* value) {
	struct _common_linked_list* _this = this;
	struct _iterator* _position = position;

	struct _element* new_element;
	new_element = element_init(value, _position->element);
	if (new_element) {
		if (_position->element == _this->head) {
			if (_this->size == 0) {
				_this->tail = new_element;
			}
			_this->head = new_element;
		}
		else {
			struct _element* prev;
			prev = get_previous_element(_this, _position->element);
			prev->next = new_element;
		}
		_this->size++;
		return iterator_init(_this, new_element);
	}
	return NULL;
}

extern common_iterator_t common_linked_list_erase(const common_linked_list_t this,
	const common_iterator_t position) {
	struct _common_linked_list* _this = this;
	struct _iterator* _position = position;

	struct _element* follower;
	follower = _position->element->next;

	if (_position->element == _this->head) {
		struct _element* old_head;
		old_head = _this->head;
		_this->head = follower;
		if (_this->head == NULL) {
			_this->tail = NULL;
		}
		element_destroy(old_head);
	}
	else {
		struct _element* prev;
		prev = get_previous_element(_this, _position->element);
		prev->next = follower;
		if (_position->element == _this->tail) {
			_this->tail = prev;
		}
		element_destroy(_position->element);
	}
	_this->size--;
	return iterator_init(_this, follower);
}

extern errno_t common_linked_list_push_front(const common_linked_list_t this,
	const void* value) {
	struct _common_linked_list* _this = this;

	struct _element* new_element;
	new_element = element_init(value, _this->head);
	if (new_element) {
		_this->head = new_element;
		if (_this->size == 0) {
			_this->tail = new_element;
		}
		_this->size++;
		return 0;
	}
	return ENOMEM;
}

extern errno_t common_linked_list_push_back(const common_linked_list_t this,
	const void* value) {
	struct _common_linked_list* _this = this;

	struct _element* new_element;
	new_element = element_init(value, NULL);
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

extern void common_linked_list_pop_front(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;

	if (_this->size == 1) {
		element_destroy(_this->head);
		_this->head = NULL;
		_this->tail = NULL;
	}
	else {
		struct _element* old_head;
		old_head = _this->head;
		_this->head = old_head->next;
		element_destroy(old_head);
	}
	_this->size--;
}

extern void common_linked_list_pop_back(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;

	if (_this->size == 1) {
		element_destroy(_this->head);
		_this->head = NULL;
		_this->tail = NULL;
	}
	else {
		struct _element* prev;
		prev = get_previous_element(_this, _this->tail);
		prev->next = NULL;
		element_destroy(_this->tail);
		_this->tail = prev;
	}
	_this->size--;
}

extern errno_t common_linked_list_resize(const common_linked_list_t this,
	const size_t s, const void* value) {
	struct _common_linked_list* _this = this;

	errno_t ret = 0;
	while (_this->size != s) {
		(_this->size > s) ?
			(common_linked_list_pop_back(_this)) :
			(ret = common_linked_list_push_back(_this, value));
		if (ret) {
			return ret;
		}
	}
	return 0;
}

extern void common_linked_list_swap(const common_linked_list_t this,
	const common_linked_list_t other) {
	struct _common_linked_list* _this = this;
	struct _common_linked_list* _other = other;

	struct _common_linked_list tmp;
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
* TODO: implement common_linked_list_sort()
*/
extern errno_t common_linked_list_merge(const common_linked_list_t this,
	const common_linked_list_t other,
	errno_t(*comp)(const void* a, const void* b, bool* result)) {
	struct _common_linked_list* _this = this;
	struct _common_linked_list* _other = other;

	((struct _element*)_this->tail)->next = _other->head;
	_this->size += _other->size;
	_other->head = NULL;
	_other->tail = NULL;
	_other->size = 0;
	return common_linked_list_sort(_this, comp);
}

extern void common_linked_list_splice(const common_linked_list_t this,
	const common_linked_list_t other, const common_iterator_t position,
	const common_iterator_t first, const common_iterator_t last) {
	struct _common_linked_list* _this = this;
	struct _common_linked_list* _other = other;
	struct _iterator* _position = position;
	struct _iterator* _first = first;
	struct _iterator* _last = last;

	if (_position->element == _this->head) {
		_this->head = _first->element;
	}
	else {
		get_previous_element(_this, _position->element)->next = _first->element;
	}
	if (_first->element == _other->head) {
		_other->head = _last->element;
	}
	else {
		get_previous_element(_other, _first->element)->next = _last->element;
	}
	get_previous_element(_other, _last->element)->next = _position->element;
}

extern size_t common_linked_list_remove(const common_linked_list_t this, void* value) {
	struct _common_linked_list* _this = this;

	struct _iterator* iterator;
	struct _iterator* tmp;
	int _removed = 0;

	iterator = common_linked_list_begin(_this);
	while (!iterator_end(iterator)) {
		if (iterator->element->data == value) {
			tmp = iterator;
			iterator = common_linked_list_erase(_this, iterator);
			iterator_destroy(tmp);
			_removed++;
		}
		else {
			iterator_next(iterator);
		}
	}
	iterator_destroy(iterator);
	return _removed;
}

extern errno_t common_linked_list_remove_if(const common_linked_list_t this,
	errno_t(*pred)(const void* a, bool* result), size_t* removed) {
	struct _common_linked_list* _this = this;

	struct _iterator* iterator;
	struct _iterator* tmp;
	bool result;
	size_t _removed = 0;

	iterator = common_linked_list_begin(_this);
	while (!iterator_end(iterator)) {
		if (pred(iterator->element->data, &result)) {
			return 1;
		}
		if (result) {
			tmp = iterator;
			iterator = common_linked_list_erase(_this, iterator);
			iterator_destroy(tmp);
			_removed++;
		}
		else {
			iterator_next(iterator);
		}
	}
	iterator_destroy(iterator);
	if (removed) {
		*removed = _removed;
	}
	return 0;
}

extern void common_linked_list_reverse(const common_linked_list_t this) {
	struct _common_linked_list* _this = this;

	if (_this->size == 0) {
		return;
	}

	struct _element* walk;
	struct _element* new_head;
	walk = _this->head;
	while (walk->next) {
		new_head = walk->next;
		walk->next = new_head->next;
		new_head->next = _this->head;
		_this->head = new_head;
	}
	_this->tail = walk;
}

static inline errno_t default_compeq(const void* a, const void* b,
	bool* result) {
	*result = (a == b);
	return 0;
}

extern errno_t common_linked_list_unique(const common_linked_list_t this,
	errno_t(*comp)(const void* a, const void* b, bool* result), size_t* removed) {
	struct _common_linked_list* _this = this;

	struct _iterator* iterator1;
	struct _iterator* iterator2;
	struct _iterator* tmp;
	bool result;
	size_t _removed = 0;

	if (!comp) {
		comp = default_compeq;
	}
	iterator1 = common_linked_list_begin(_this);
	iterator2 = iterator_init(_this, NULL);
	while (!iterator_end(iterator1)) {
		iterator2->element = iterator1->element->next;
		while (!iterator_end(iterator2)) {
			errno_t ret;
			void* e1 = *iterator_data(iterator1);
			void* e2 = *iterator_data(iterator2);
			ret = comp(e1, e2, &result);
			if (ret) {
				return ret;
			}
			if (result) {
				tmp = iterator2;
				iterator2 = common_linked_list_erase(_this, iterator2);
				iterator_destroy(tmp);
				_removed++;
			}
			else {
				iterator_next(iterator2);
			}
		}
		iterator_next(iterator1);
	}
	iterator_destroy(iterator1);
	iterator_destroy(iterator2);

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
extern int common_linked_list_sort(const common_linked_list_t this,
	int (*comp)(const void* a, const void* b, bool* result)) {
	struct _common_linked_list* _this = this;

	return 1;
}
