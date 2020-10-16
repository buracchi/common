#define DS_IMPLEMENT_LIST
#include "list.h"
#undef DS_IMPLEMENT_LIST

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

extern inline void ds_list_destroy(const ds_list_t this) {
	struct _ds_list* _this = this;
	_this->_destroy(_this);
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

extern inline void* ds_list_front(const ds_list_t this) {
	struct _ds_list* _this = this;
	return _this->_front(_this);
}
extern inline void* ds_list_back(const ds_list_t this) {
	struct _ds_list* _this = this;
	return _this->_back(_this);
}

/*******************************************************************************
*                                   Iterators                                  *
*******************************************************************************/

extern iterator_t ds_list_begin(const ds_list_t this) {
	struct _ds_list* _this = this;
	return _this->_begin(_this);
}

extern iterator_t ds_list_end(const ds_list_t this) {
	struct _ds_list* _this = this;
	return _this->_end(_this);
}

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

extern inline bool ds_list_empty(const ds_list_t this) {
	struct _ds_list* _this = this;
	return _this->_empty(_this);
}

extern inline size_t ds_list_size(const ds_list_t this) {
	struct _ds_list* _this = this;
	return _this->_size(_this);
}

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

extern inline void ds_list_clear(const ds_list_t this) {
	struct _ds_list* _this = this;
	_this->_clear(_this);
}

extern inline iterator_t ds_list_insert(const ds_list_t this,
	const iterator_t position, const void* value) {
	struct _ds_list* _this = this;
	return _this->_insert(_this, position, value);
}

extern inline iterator_t ds_list_erase(const ds_list_t this,
	const iterator_t position) {
	struct _ds_list* _this = this;
	return _this->_erase(_this, position);
}

extern inline int ds_list_push_front(const ds_list_t this,
	const void* value) {
	struct _ds_list* _this = this;
	return _this->_push_front(_this, value);
}

extern inline int ds_list_push_back(const ds_list_t this,
	const void* value) {
	struct _ds_list* _this = this;
	return _this->_push_back(_this, value);
}

extern inline void ds_list_pop_front(const ds_list_t this) {
	struct _ds_list* _this = this;
	_this->_pop_front(_this);
}

extern inline void ds_list_pop_back(const ds_list_t this) {
	struct _ds_list* _this = this;
	_this->_pop_back(_this);
}

extern inline errno_t ds_list_resize(const ds_list_t this, const size_t s,
	const void* value) {
	struct _ds_list* _this = this;
	return _this->_resize(_this, s, value);
}

extern inline void ds_list_swap(const ds_list_t this, const ds_list_t other) {
	struct _ds_list* _this = this;
	_this->_swap(_this, other);
}

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

extern inline errno_t ds_list_merge(const ds_list_t this, const ds_list_t other,
	errno_t(*comp)(const void* a, const void* b, bool* result)) {
	struct _ds_list* _this = this;
	return _this->_merge(_this, other, comp);
}

extern inline void ds_list_splice(const ds_list_t this, const ds_list_t other,
	const iterator_t pos, const iterator_t first, const iterator_t last) {
	struct _ds_list* _this = this;
	_this->_splice(_this, other, pos, first, last);
}

extern inline size_t ds_list_remove(const ds_list_t this, void* value) {
	struct _ds_list* _this = this;
	return _this->_remove(_this, value);
}

extern inline errno_t ds_list_remove_if(const ds_list_t this,
	errno_t(*pred)(const void* a, bool* result), size_t* removed) {
	struct _ds_list* _this = this;
	return _this->_remove_if(_this, pred, removed);
}

extern inline void ds_list_reverse(const ds_list_t this) {
	struct _ds_list* _this = this;
	_this->_reverse(_this);
}

extern inline errno_t ds_list_unique(const ds_list_t this,
	errno_t(*comp)(const void* a, const void* b, bool* result), int* removed) {
	struct _ds_list* _this = this;
	return _this->_unique(_this, comp, removed);
}

extern inline errno_t ds_list_sort(const ds_list_t this,
	errno_t(*comp)(const void* a, const void* b, bool* result)) {
	struct _ds_list* _this = this;
	return _this->_sort(_this, comp);
}
