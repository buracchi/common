#define IMPLEMENT_COMMON_LIST
#include "list.h"
#undef IMPLEMENT_COMMON_LIST

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

extern inline void common_list_destroy(const common_list_t this) {
	struct _common_list* _this = this;
	_this->_destroy(_this);
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

extern inline void* common_list_front(const common_list_t this) {
	struct _common_list* _this = this;
	return _this->_front(_this);
}
extern inline void* common_list_back(const common_list_t this) {
	struct _common_list* _this = this;
	return _this->_back(_this);
}

/*******************************************************************************
*                                   Iterators                                  *
*******************************************************************************/

extern common_iterator_t common_list_begin(const common_list_t this) {
	struct _common_list* _this = this;
	return _this->_begin(_this);
}

extern common_iterator_t common_list_end(const common_list_t this) {
	struct _common_list* _this = this;
	return _this->_end(_this);
}

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

extern inline bool common_list_empty(const common_list_t this) {
	struct _common_list* _this = this;
	return _this->_empty(_this);
}

extern inline size_t common_list_size(const common_list_t this) {
	struct _common_list* _this = this;
	return _this->_size(_this);
}

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

extern inline void common_list_clear(const common_list_t this) {
	struct _common_list* _this = this;
	_this->_clear(_this);
}

extern inline common_iterator_t common_list_insert(const common_list_t this,
	const common_iterator_t position, const void* value) {
	struct _common_list* _this = this;
	return _this->_insert(_this, position, value);
}

extern inline common_iterator_t common_list_erase(const common_list_t this,
	const common_iterator_t position) {
	struct _common_list* _this = this;
	return _this->_erase(_this, position);
}

extern inline int common_list_push_front(const common_list_t this,
	const void* value) {
	struct _common_list* _this = this;
	return _this->_push_front(_this, value);
}

extern inline int common_list_push_back(const common_list_t this,
	const void* value) {
	struct _common_list* _this = this;
	return _this->_push_back(_this, value);
}

extern inline void common_list_pop_front(const common_list_t this) {
	struct _common_list* _this = this;
	_this->_pop_front(_this);
}

extern inline void common_list_pop_back(const common_list_t this) {
	struct _common_list* _this = this;
	_this->_pop_back(_this);
}

extern inline errno_t common_list_resize(const common_list_t this, const size_t s,
	const void* value) {
	struct _common_list* _this = this;
	return _this->_resize(_this, s, value);
}

extern inline void common_list_swap(const common_list_t this, const common_list_t other) {
	struct _common_list* _this = this;
	_this->_swap(_this, other);
}

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

extern inline errno_t common_list_merge(const common_list_t this, const common_list_t other,
	errno_t(*comp)(const void* a, const void* b, bool* result)) {
	struct _common_list* _this = this;
	return _this->_merge(_this, other, comp);
}

extern inline void common_list_splice(const common_list_t this, const common_list_t other,
	const common_iterator_t pos, const common_iterator_t first, const common_iterator_t last) {
	struct _common_list* _this = this;
	_this->_splice(_this, other, pos, first, last);
}

extern inline size_t common_list_remove(const common_list_t this, void* value) {
	struct _common_list* _this = this;
	return _this->_remove(_this, value);
}

extern inline errno_t common_list_remove_if(const common_list_t this,
	errno_t(*pred)(const void* a, bool* result), size_t* removed) {
	struct _common_list* _this = this;
	return _this->_remove_if(_this, pred, removed);
}

extern inline void common_list_reverse(const common_list_t this) {
	struct _common_list* _this = this;
	_this->_reverse(_this);
}

extern inline errno_t common_list_unique(const common_list_t this,
	errno_t(*comp)(const void* a, const void* b, bool* result), int* removed) {
	struct _common_list* _this = this;
	return _this->_unique(_this, comp, removed);
}

extern inline errno_t common_list_sort(const common_list_t this,
	errno_t(*comp)(const void* a, const void* b, bool* result)) {
	struct _common_list* _this = this;
	return _this->_sort(_this, comp);
}
