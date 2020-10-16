#define IMPLEMENT_ITERATOR
#include "iterator.h"
#undef IMPLEMENT_ITERATOR

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

extern inline void iterator_destroy(const iterator_t this) {
	struct _iterator* _this = this;
	_this->ops->_destroy(_this);
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

extern inline void* iterator_data(const iterator_t this) {
	struct _iterator* _this = this;
	return _this->ops->_data(_this);
}

extern inline iterator_t iterator_next(const iterator_t this) {
	struct _iterator* _this = this;
	return _this->ops->_next(_this);
}

extern inline iterator_t iterator_prev(const iterator_t this) {
	struct _iterator* _this = this;
	return _this->ops->_prev(_this);
}

extern inline bool iterator_begin(const iterator_t this) {
	struct _iterator* _this = this;
	return _this->ops->_begin(_this);
}

extern inline bool iterator_end(const iterator_t this) {
	struct _iterator* _this = this;
	return _this->ops->_end(_this);
}

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

extern iterator_t iterator_advance(const iterator_t this, int n) {
	struct _iterator* _this = this;

	for (int i = n; i != 0; n ? i++ : i--) {
		n ? _this->ops->_next(_this) : _this->ops->_prev(_this);
	}
	return _this;
}

extern size_t iterator_distance(const iterator_t first, const iterator_t last) {
	struct _iterator* _first = first;
	struct _iterator* _last = last;

	size_t dist = 0;
	while (_first != _last) {
		_first->ops->_next(_first);
		dist++;
	}
	for (int i = 0; i < dist; i++) {
		_first->ops->_prev(_first);		//Not very smart duh
	}
	return dist;
}
