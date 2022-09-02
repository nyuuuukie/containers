#pragma once

#include "rbt_node.hpp"
#include "iterator_traits.hpp"
#include "rbt.hpp"

namespace ft {

template <typename T>
struct rbt_iterator {

public:
	typedef rbt_node<T>	 node_type;
	typedef rbt_node<T> * node_pointer;
	
	typedef iterator_traits<T *>					_traits_type;
	typedef typename _traits_type::pointer 		    pointer;
	typedef typename _traits_type::value_type      	value_type;
	typedef typename _traits_type::reference      	reference;
	typedef typename _traits_type::difference_type 	difference_type;
	typedef bidirectional_iterator_tag 				iterator_category;
 
private:
	node_pointer _current;

public:
	rbt_iterator(void) : _current(NULL) { }

	explicit
	rbt_iterator(node_pointer node) : _current(node) { }

	rbt_iterator(const rbt_iterator<T> &it) : _current(it.base()) {}

	node_pointer
	base(void) const {
		return _current;
	}

	reference 
	operator*(void) const {
		return _current->data;
	}

	pointer
	operator->(void) const {
		return &(_current->data);
	}

	rbt_iterator
	operator++(void) {
		_current = increment(_current);
		return *this;
	}

	rbt_iterator
	operator--(void) {
		_current = decrement(_current);
		return *this;
	}

	rbt_iterator
	operator++(int) {
		rbt_iterator tmp = *this;
		_current = increment(_current);

		return tmp;
	}

	rbt_iterator
	operator--(int) {
		rbt_iterator tmp = *this;
		_current = decrement(_current);

		return tmp;
	}

	inline bool
	operator==(const rbt_iterator<T> &rhs) const
	{ return base() == rhs.base(); }

	inline bool
	operator!=(const rbt_iterator<T> &rhs) const
	{ return base() != rhs.base(); }
};

template <typename T>
struct rbt_const_iterator {

public:
	typedef rbt_iterator<T>		non_const_iterator;
	typedef rbt_node<T>			node_type;
	typedef rbt_node<T> * 		node_pointer;
	
	typedef iterator_traits<const T *>				_traits_type;
	typedef typename _traits_type::pointer 		    pointer;
	typedef typename _traits_type::value_type      	value_type;
	typedef typename _traits_type::reference      	reference;
	typedef typename _traits_type::difference_type 	difference_type;

	typedef bidirectional_iterator_tag 				iterator_category;

private:
	node_pointer _current;

public:
	rbt_const_iterator(void) : _current(NULL) { }

	explicit
	rbt_const_iterator(node_pointer node) : _current(node) { }

	rbt_const_iterator(const non_const_iterator &it) : _current(it.base()) { }

	rbt_const_iterator(const rbt_const_iterator &it) : _current(it.base()) {}

	node_pointer
	base(void) const {
		return _current;
	}

	reference 
	operator*(void) const {
		return _current->data;
	}

	pointer
	operator->(void) const {
		return &(_current->data);
	}

	rbt_const_iterator
	operator++(void) {
		_current = increment(_current);
		return *this;
	}

	rbt_const_iterator
	operator--(void) {
		_current = decrement(_current);
		return *this;
	}

	rbt_const_iterator
	operator++(int) {
		rbt_const_iterator tmp = *this;
		_current = increment(_current);

		return tmp;
	}

	rbt_const_iterator
	operator--(int) {
		rbt_const_iterator tmp = *this;
		_current = decrement(_current);

		return tmp;
	}

	inline bool
	operator==(const rbt_const_iterator<T> &rhs) const
	{ return base() == rhs.base(); }

	inline bool
	operator!=(const rbt_const_iterator<T> &rhs) const
	{ return base() != rhs.base(); }
};


template <typename T>
inline bool
operator==(const rbt_iterator<T> &lhs, const rbt_const_iterator<T> &rhs)
{ return lhs.base() == rhs.base(); }

template <typename T>
inline bool
operator!=(const rbt_iterator<T> &lhs, const rbt_const_iterator<T> &rhs)
{ return lhs.base() != rhs.base(); }

template <typename T>
inline bool
operator==(const rbt_const_iterator<T> &lhs, const rbt_iterator<T> &rhs)
{ return lhs.base() == rhs.base(); }

template <typename T>
inline bool
operator!=(const rbt_const_iterator<T> &lhs, const rbt_iterator<T> &rhs)
{ return lhs.base() != rhs.base(); }

};