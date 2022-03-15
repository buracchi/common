#define IMPLEMENT_COMMON_MAP
#include "map.h"
#undef IMPLEMENT_COMMON_MAP

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

extern inline void common_map_destroy(const common_map_t this) {
	struct _common_map* _this = this;
	_this->_destroy(_this);
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

extern inline errno_t common_map_at(const common_map_t this, const void* key,
	void** value) {
	struct _common_map* _this = this;
	return _this->_at(_this, key, value);
}

/*******************************************************************************
*                                   Iterators                                  *
*******************************************************************************/

extern inline common_iterator_t common_map_begin(const common_map_t this) {
	struct _common_map* _this = this;
	return _this->_begin(_this);
}

extern inline common_iterator_t common_map_end(const common_map_t this) {
	struct _common_map* _this = this;
	return _this->_end(_this);
}

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

extern inline bool common_map_empty(const common_map_t this) {
	struct _common_map* _this = this;
	return _this->_empty(_this);
}

extern inline size_t common_map_size(const common_map_t this) {
	struct _common_map* _this = this;
	return _this->_size(_this);
}

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

extern inline void common_map_clear(const common_map_t this) {
	struct _common_map* _this = this;
	_this->_clear(_this);
}

extern inline common_iterator_t common_map_insert(const common_map_t this,
	const void* key, const void* value) {
	struct _common_map* _this = this;
	return _this->_insert(_this, key, value);
}

extern inline common_iterator_t common_map_insert_or_assign(
	const common_map_t this, const void* key, const void* value) {
	struct _common_map* _this = this;
	return _this->_insert_or_assign(_this, key, value);
}

extern inline common_iterator_t common_map_erase(const common_map_t this,
	const common_iterator_t position) {
	struct _common_map* _this = this;
	return _this->_erase(_this, position);
}

extern inline void common_map_swap(const common_map_t this,
	const common_map_t other) {
	struct _common_map* _this = this;
	_this->_swap(_this, other);
}

extern inline errno_t common_map_merge(const common_map_t this,
	const common_map_t source,
	errno_t(*comp)(const void* a, const void* b, bool* result)) {
	struct _common_map* _this = this;
	return _this->_merge(_this, source, comp);
}

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

extern inline errno_t common_map_remove(const common_map_t this,
	const void* key, errno_t(*comp)(const void* a, const void* b, bool* result),
	size_t* removed) {
	struct _common_map* _this = this;
	return _this->_remove(_this, key, comp, removed);
}

extern inline errno_t common_map_remove_if(const common_map_t this,
	errno_t(*pred)(const void* a, bool* result), size_t* removed) {
	struct _common_map* _this = this;
	return _this->_remove_if(_this, pred, removed);
}

/*******************************************************************************
*                                   Lookup                                     *
*******************************************************************************/

extern inline errno_t common_map_count(const common_map_t this, const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	size_t* count) {
	struct _common_map* _this = this;
	return _this->_count(_this, key, comp, count);
}

extern inline errno_t common_map_find(const common_map_t this, const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	common_iterator_t* iterator) {
	struct _common_map* _this = this;
	return _this->_find(_this, key, comp, iterator);
}

extern inline errno_t common_map_contains(const common_map_t this, 
	const void* key, errno_t(*comp)(const void* a, const void* b, bool* result),
	bool* exists) {
	struct _common_map* _this = this;
	return _this->_contains(_this, key, comp, exists);
}
