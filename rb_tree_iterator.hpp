#pragma once

#include "rb_tree_node.hpp"
#include "iterator_traits.hpp"

namespace ft {

  	template <typename T>
    struct rb_tree_iterator
    {
		typedef T  	value_type;
		typedef T& 	reference;
		typedef T* 	pointer;

		typedef ptrdiff_t								difference_type;
		typedef bidirectional_iterator_tag				iterator_category;

		typedef typename rb_tree_node::pointer			pointer;
		typedef typename rb_tree_node::const_pointer	const_pointer;
		
		typedef rb_tree_iterator iterator;
		
		pointer _current;
		
		rb_tree_iterator() : _current() { }

		explicit
		rb_tree_iterator(pointer ptr) : _current(ptr) { }


        reference operator*() const {
			return _current->_value;
        }

        pointer operator->() const {
			return &(_current->_value);
        }

        iterator& operator++() {
			_current = increment(_current);
            return *this;
        }

        iterator& operator--() {
			_current = decrement(_current);
            return *this;
        }

        iterator operator++(int) {
			iterator tmp = *this;
			_current = increment(_current);

            return tmp;
        }

        iterator operator--(int) {
            iterator tmp = *this;
			_current = decrement(_current);

            return tmp;
        }

		pointer increment() {

			if (_current->right) {
				_current = rb_tree_node::min(_current->right);
			}
			else {
				while (_current->parent->right == _current)
					_current = _current->parent;
				_current = _current->parent;
			}
			return _current;
		}

		pointer decrement() {

			if (_current->left) {
				_current = rb_tree_node::max(_current->left);
			}
			else {
				while (_current->parent->left == _current)
					_current = _current->parent;
				_current = _current->parent;
			}
			return _current;
		}

    };


	template<typename T>
    struct rb_tree_const_iterator
    {
		typedef T	 value_type;
		typedef const T& reference;
		typedef const T* pointer;


		typedef ft::bidirectional_iterator_tag	iterator_category;
		typedef ptrdiff_t			 				difference_type;

		typedef rb_tree_iterator<T> 				iterator;
		typedef rb_tree_const_iterator<T>			const_iterator;
		typedef rb_tree_node::const_pointer		node_pointer;
		typedef const rb_tree_node<T>*			link_type;

		node_pointer _current;


		rb_tree_const_iterator() : _current() { }

		explicit
		rb_tree_const_iterator(pointer ptr) : _current(ptr) { }

		rb_tree_const_iterator(const iterator& __it)
		: _M_node(__it._M_node) { }

		iterator
		const_cast() const { 
			return iterator(const_cast<typename iterator::pointer>(_current));
		}

		reference operator*() const {
			return _current->_value;
		}

		pointer operator->() const {
			return &(_current->_value);
		}

		iterator& operator++() {
			increment();
		    return *this;
		}

		iterator& operator--() {
			decrement();
		    return *this;
		}

		iterator operator++(int) {
			iterator tmp = *this;
			increment();

		    return tmp;
		}

		iterator operator--(int) {
		    iterator tmp = *this;
			decrement();

		    return tmp;
		}

		pointer increment() {

			if (_current->right) {
				_current = rb_tree_node::min(_current->right);
			}
			else {
				while (_current->parent->right == _current)
					_current = _current->parent;
				_current = _current->parent;
			}
			return _current;
		}

		pointer decrement() {

			if (_current->left) {
				_current = rb_tree_node::max(_current->left);
			}
			else {
				while (_current->parent->left == _current)
					_current = _current->parent;
				_current = _current->parent;
			}
			return _current;
		}


   
    };

	template <typename T>
	inline bool
	operator==(const rb_tree_iterator<T>& lhs, const rb_tree_iterator<T>& rhs)
	{ return lhs._node == rhs._node; }

	template <typename T>
	inline bool
	operator!=(const rb_tree_iterator<T>& lhs, const rb_tree_iterator<T>& rhs)
	{ return lhs._node != rhs._node; }
	
	template <typename T>
	inline bool
	operator==(const rb_tree_const_iterator<T>& lhs, const rb_tree_const_iterator<T>& rhs)
	{ return lhs._node == rhs._node; }

	template <typename T>
	inline bool
	operator!=(const rb_tree_const_iterator<T>& lhs, const rb_tree_const_iterator<T>& rhs)
	{ return lhs._node != rhs._node; }

};