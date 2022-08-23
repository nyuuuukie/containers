#pragma once

#include "rb_node.hpp"
#include "iterator_traits.hpp"
#include "rb_tree.hpp"

namespace ft {

template <typename T>
struct rbt_iterator {

public:
	typedef iterator_traits<T>			_traits_type;

	// typedef T  										value_type;
	// typedef typename _traits_type::pointer         	pointer;
	// typedef typename _traits_type::reference       	reference;
	// typedef typename _traits_type::difference_type 	difference_type;
	// typedef ft::bidirectional_iterator_tag 			iterator_category;

	typedef typename _traits_type::pointer         	pointer;
	typedef typename _traits_type::value_type      	value_type;
	typedef typename _traits_type::reference      	reference;
	typedef typename _traits_type::difference_type 	difference_type;
	typedef bidirectional_iterator_tag 				iterator_category;
 
private:
	pointer _current;

public:
	rbt_iterator(void) : _current(NULL) { }

	explicit
	rbt_iterator(pointer node) : _current(node) { }

	rbt_iterator(const rbt_iterator<T> &it) : _current(it.base()) {}

	pointer
	base(void) const {
		return _current;
	}

	reference 
	operator*(void) const {
		return *_current;
	}

	pointer
	operator->(void) const {
		return &(*_current);
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

	pointer
	find_first(pointer node) {
		while (node != NULL && node->parent != NULL) {
			node = node->parent;
		}
		return leftmost_node(upmost_node(node));
	}

	pointer 
	increment(pointer node) {

		if (node == NULL) {
			// should never happen
			return NULL;
		}

		if (is_leaf_node(node)) {
			if (node->parent) {
				node = leftmost_node(upmost_node(node));
			}
		} else if (!is_leaf_node(node->right)) {
			node = leftmost_node(node->right);
		} else if (node->right->parent == node) {
			node = node->right;
		} else {
			node = upmost_right_node(node);
		}

		return node;
	}

	pointer
	decrement(pointer node) {

		if (node == NULL) {
			// should never happen
			return NULL;
		}
		
		if (is_leaf_node(node)) {
			if (node->parent) {
				node = node->parent;
			}
		} else if (!is_leaf_node(node->left)) {
			node = rightmost_node(node->left);
		} else if (node == leftmost_node(upmost_node(node))) {
			node = node->left;
		} else {
			node = upmost_left_node(node);
		}
		return node;
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

private:
	typedef rbt_iterator<T>		non_const_iterator;

public:
	typedef iterator_traits<T>						_traits_type;

	typedef typename _traits_type::pointer         	pointer;
	typedef typename _traits_type::value_type      	value_type;
	typedef typename _traits_type::reference      	reference;
	typedef typename _traits_type::difference_type 	difference_type;
	typedef bidirectional_iterator_tag 				iterator_category;

private:
	pointer _current;

public:
	rbt_const_iterator(void) : _current(NULL) { }

	explicit
	rbt_const_iterator(pointer node) : _current(node) { }

	rbt_const_iterator(const non_const_iterator &it) : _current(it.base()) { }

	rbt_const_iterator(const rbt_const_iterator &it) : _current(it.base()) {}

	pointer
	base(void) const {
		return _current;
	}

	reference 
	operator*(void) const {
		return *_current;
	}

	pointer
	operator->(void) const {
		return &(*_current);
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

	pointer 
	increment(pointer node) {

		if (node == NULL) {
			return NULL;
		}

		if (!is_leaf_node(node)) {
			if (!is_leaf_node(node->right)) {
				node = leftmost_node(node->right);
			} else if (node->right->parent == node) {
				node = node->right;
			} else {
				node = upmost_right_node(node);
			}
		}
		return node;
	}

	pointer
	decrement(pointer node) {

		if (node == NULL) {
			return NULL;
		}
		
		if (is_leaf_node(node)) {
			if (node->parent) {
				node = node->parent;
			}
		} else if (!is_leaf_node(node->left)) {
			node = rightmost_node(node->left);
		} else {
			pointer root = node;
			while (root != NULL && root->parent != NULL) {
				root = root->parent;
			}
			if (node != leftmost_node(root)) {
				node = upmost_left_node(node);
			} else {
				node = node->left;
			}
		}
		return node;
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