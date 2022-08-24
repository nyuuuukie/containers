#pragma once

#include "rbt_node.hpp"
#include "iterator_traits.hpp"
#include "rbt.hpp"

namespace ft {

template <typename TreeIterator>
struct map_iterator {

public:
	// typedef iterator_traits<TreeIterator>			_traits_type;

	typedef typename TreeIterator::pointer         	pointer;
	typedef typename TreeIterator::value_type      	value_type;
	typedef typename TreeIterator::reference      	reference;
	typedef typename TreeIterator::difference_type 	difference_type;
	typedef bidirectional_iterator_tag 				iterator_category;
 
private:
	TreeIterator _current;

public:
	map_iterator(void) : _current() { }

	map_iterator(const TreeIterator &node) : _current(node) { }

	map_iterator(const map_iterator<TreeIterator> &it) : _current(it._current) {}

	TreeIterator 
	base(void) const {
		return _current;
	}

	reference 
	operator*(void) const {
		return _current.operator*();
	}

	pointer
	operator->(void) const {
		return _current.operator->();
	}

	map_iterator
	operator++(void) {
		_current++;
		return *this;
	}

	map_iterator
	operator--(void) {
		_current--;
		return *this;
	}

	map_iterator
	operator++(int) {
		map_iterator tmp = *this;
		_current++;

		return tmp;
	}

	map_iterator
	operator--(int) {
		map_iterator tmp = *this;
		_current--;

		return tmp;
	}

	inline bool
	operator==(const map_iterator<TreeIterator> &rhs) const
	{ return _current == rhs._current; }

	inline bool
	operator!=(const map_iterator<TreeIterator> &rhs) const
	{ return _current != rhs._current; }
};

template <typename TreeIterator>
struct map_const_iterator {

private:
	// typedef map_iterator<TreeIterator>				non_const_iterator;

public:
	typedef typename TreeIterator::pointer         	pointer;
	typedef typename TreeIterator::value_type      	value_type;
	typedef typename TreeIterator::reference      	reference;
	typedef typename TreeIterator::difference_type 	difference_type;
	typedef bidirectional_iterator_tag 				iterator_category;

private:
	TreeIterator _current;

public:
	map_const_iterator(void) : _current(NULL) { }

	explicit
	map_const_iterator(const TreeIterator &node) : _current(node) { }

	map_const_iterator(map_iterator<typename TreeIterator::non_const_iterator> it) : _current(it.base()) { }

	map_const_iterator(const map_const_iterator &it) : _current(it._current) {}

	TreeIterator 
	base(void) const {
		return _current;
	}

	reference 
	operator*(void) const {
		return _current.operator*();
	}

	pointer
	operator->(void) const {
		return _current.operator->();
	}

	map_const_iterator
	operator++(void) {
		_current++;
		return *this;
	}

	map_const_iterator
	operator--(void) {
		_current--;
		return *this;
	}

	map_const_iterator
	operator++(int) {
		map_const_iterator tmp = *this;
		_current++;

		return tmp;
	}

	map_const_iterator
	operator--(int) {
		map_const_iterator tmp = *this;
		_current--;

		return tmp;
	}

	inline bool
	operator==(const map_const_iterator<TreeIterator> &rhs) const
	{ return _current == rhs._current; }

	inline bool
	operator!=(const map_const_iterator<TreeIterator> &rhs) const
	{ return _current != rhs._current; }
};


template <typename T>
inline bool
operator==(const map_iterator<T> &lhs, const map_const_iterator<T> &rhs)
{ return lhs._current == rhs._current; }

template <typename T>
inline bool
operator!=(const map_iterator<T> &lhs, const map_const_iterator<T> &rhs)
{ return lhs._current != rhs._current; }

template <typename T>
inline bool
operator==(const map_const_iterator<T> &lhs, const map_iterator<T> &rhs)
{ return lhs._current == rhs._current; }

template <typename T>
inline bool
operator!=(const map_const_iterator<T> &lhs, const map_iterator<T> &rhs)
{ return lhs._current != rhs._current; }

};