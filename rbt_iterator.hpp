#pragma once

#include "rb_node.hpp"
#include "iterator_traits.hpp"
#include "rb_tree.hpp"

namespace ft {

  	template <typename T>
    struct rbt_iterator {

        public:
			typedef rb_node<T>								node_type;
			typedef node_type *								node_pointer;
			typedef iterator_traits<node_pointer>			_traits_type;

            typedef typename _traits_type::pointer         	pointer;
            typedef typename _traits_type::reference       	reference;
            typedef typename _traits_type::value_type      	value_type;
            typedef typename _traits_type::difference_type 	difference_type;
            typedef bidirectional_iterator_tag 				iterator_category;

		protected:
            node_pointer _current;

		public:
		rbt_iterator(void) : _current(NULL) { }

		explicit
		rbt_iterator(node_pointer ptr) : _current(ptr) { }

		node_pointer base(void) const {
			return _current;
		}

        reference operator*(void) const {
			return *_current;
        }

        node_pointer operator->(void) const {
			return &(*_current);
        }

        rbt_iterator& operator++(void) {
			_current = rb_tree<value_type>::increment(_current);
            return *this;
        }

        rbt_iterator& operator--(void) {
			_current = rb_tree<value_type>::decrement(_current);
            return *this;
        }

        rbt_iterator operator++(int) {
			rbt_iterator tmp = *this;
			_current = rb_tree<value_type>::increment(_current);

            return tmp;
        }

        rbt_iterator operator--(int) {
            rbt_iterator tmp = *this;
			_current = rb_tree<value_type>::decrement(_current);

            return tmp;
        }
    };

	template <typename T>
	inline bool
	operator==(const rbt_iterator<T> &lhs, const rbt_iterator<T> &rhs)
	{ return lhs.base() == rhs.base(); }

	template <typename T>
	inline bool
	operator!=(const rbt_iterator<T> &lhs, const rbt_iterator<T> &rhs)
	{ return lhs.base() != rhs.base(); }

};