#define IMPLEMENT_COMMON_ITERATOR
#include "iterator.h"
#undef IMPLEMENT_COMMON_ITERATOR

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

extern inline void common_iterator_destroy(const common_iterator_t this) {
	struct _common_iterator* _this = this;
	_this->ops->_destroy(_this);
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

extern inline void** common_iterator_data(const common_iterator_t this) {
	struct _common_iterator* _this = this;
	return _this->ops->_data(_this);
}

extern inline common_iterator_t common_iterator_next(const common_iterator_t this) {
	struct _common_iterator* _this = this;
	return _this->ops->_next(_this);
}

extern inline common_iterator_t common_iterator_prev(const common_iterator_t this) {
	struct _common_iterator* _this = this;
	return _this->ops->_prev(_this);
}

extern inline bool common_iterator_begin(const common_iterator_t this) {
	struct _common_iterator* _this = this;
	return _this->ops->_begin(_this);
}

extern inline bool common_iterator_end(const common_iterator_t this) {
	struct _common_iterator* _this = this;
	return _this->ops->_end(_this);
}

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

extern common_iterator_t common_iterator_advance(const common_iterator_t this,
	int n) {
	struct _common_iterator* _this = this;

	for (int i = n; i != 0; n ? i++ : i--) {
		n ? _this->ops->_next(_this) : _this->ops->_prev(_this);
	}
	return _this;
}

extern size_t common_iterator_distance(const common_iterator_t first,
	const common_iterator_t last) {
	struct _common_iterator* _first = first;
	struct _common_iterator* _last = last;

	size_t dist = 0;
	while (_first != _last) {
		_first->ops->_next(_first);
		dist++;
	}
	for (size_t i = 0; i < dist; i++) {
		_first->ops->_prev(_first);		//Not very smart duh
	}
	return dist;
}
