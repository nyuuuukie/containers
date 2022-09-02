#pragma once

#include "rbt_node.hpp"
#include "iterator_traits.hpp"
#include "rbt.hpp"

namespace ft {

template <typename TreeIterator>
struct set_iterator {

public:
	typedef typename TreeIterator::pointer         	pointer;
	typedef typename TreeIterator::value_type      	value_type;
	typedef typename TreeIterator::reference      	reference;
	typedef typename TreeIterator::difference_type 	difference_type;
	typedef bidirectional_iterator_tag 				iterator_category;
 
private:
	TreeIterator _current;

public:
	set_iterator(void) : _current() { }

	set_iterator(const TreeIterator &node) : _current(node) { }

	set_iterator(const set_iterator<TreeIterator> &it) : _current(it._current) {}

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

	set_iterator
	operator++(void) {
		_current++;
		return *this;
	}

	set_iterator
	operator--(void) {
		_current--;
		return *this;
	}

	set_iterator
	operator++(int) {
		set_iterator tmp = *this;
		_current++;

		return tmp;
	}

	set_iterator
	operator--(int) {
		set_iterator tmp = *this;
		_current--;

		return tmp;
	}

	inline bool
	operator==(const set_iterator<TreeIterator> &rhs) const
	{ return _current == rhs._current; }

	inline bool
	operator!=(const set_iterator<TreeIterator> &rhs) const
	{ return _current != rhs._current; }
};

template <typename TreeIterator>
struct set_const_iterator {

public:
	typedef typename TreeIterator::pointer         	pointer;
	typedef typename TreeIterator::value_type      	value_type;
	typedef typename TreeIterator::reference      	reference;
	typedef typename TreeIterator::difference_type 	difference_type;
	typedef bidirectional_iterator_tag 				iterator_category;

private:
	TreeIterator _current;

public:
	set_const_iterator(void) : _current(NULL) { }

	set_const_iterator(const TreeIterator &node) : _current(node) { }

	set_const_iterator(set_iterator<typename TreeIterator::non_const_iterator> it) : _current(it.base()) { }

	set_const_iterator(const set_const_iterator &it) : _current(it._current) {}

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

	set_const_iterator
	operator++(void) {
		_current++;
		return *this;
	}

	set_const_iterator
	operator--(void) {
		_current--;
		return *this;
	}

	set_const_iterator
	operator++(int) {
		set_const_iterator tmp = *this;
		_current++;

		return tmp;
	}

	set_const_iterator
	operator--(int) {
		set_const_iterator tmp = *this;
		_current--;

		return tmp;
	}

	inline bool
	operator==(const set_const_iterator<TreeIterator> &rhs) const
	{ return _current == rhs._current; }

	inline bool
	operator!=(const set_const_iterator<TreeIterator> &rhs) const
	{ return _current != rhs._current; }
};


template <typename T>
inline bool
operator==(const set_iterator<T> &lhs, const set_const_iterator<T> &rhs)
{ return lhs._current == rhs._current; }

template <typename T>
inline bool
operator!=(const set_iterator<T> &lhs, const set_const_iterator<T> &rhs)
{ return lhs._current != rhs._current; }

template <typename T>
inline bool
operator==(const set_const_iterator<T> &lhs, const set_iterator<T> &rhs)
{ return lhs._current == rhs._current; }

template <typename T>
inline bool
operator!=(const set_const_iterator<T> &lhs, const set_iterator<T> &rhs)
{ return lhs._current != rhs._current; }

};