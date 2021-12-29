#pragma once

#include <memory>

#include "iterator_traits.hpp"

namespace ft {

	enum rb_tree_color {
		red = false,
		black = true
	};

	template <typename T>
	struct rb_tree_node {

		typedef rb_tree_node*		node_ptr;
		typedef rb_tree_color		node_color;
		typedef T					node_value;

		node_ptr	_parent;
		node_ptr	_left;
		node_ptr	_right;
		node_color	_color;
		node_value	_value;

		static node_ptr min(node_ptr node)
		{
			while (node->_left != 0)
				node = node->_left;
			return node;
		}

		static node_ptr max(node_ptr node)
		{
			while (node->_right != 0)
				node = node->_right;
			return node;
		}
	};


  	template <typename T>
    struct rb_tree_iterator
    {
		typedef T  	value_type;
		typedef T& 	reference;
		typedef T* 	pointer;

		typedef ptrdiff_t								difference_type;
		typedef bidirectional_iterator_tag				iterator_category;

		typedef typename rb_tree_node::node_ptr			node_ptr;
		typedef typename rb_tree_node::const_node_ptr	const_node_ptr;
		
		typedef rb_tree_iterator iterator;
		
		node_ptr _current;
		
		rb_tree_iterator() : _current() { }

		explicit
		rb_tree_iterator(node_ptr ptr) : _current(ptr) { }


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

		node_ptr increment() {

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

		node_ptr decrement() {

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
	
	
	template <typename Key, typename T, typename KeyOfValue, 
	typename Compare, typename Alloc = std::allocator<T> >
	class rb_tree {

		protected:
			typedef rb_tree_node<T>			node;
			typedef const rb_tree_node<T>	const_node;
			typedef rb_tree_node<T>* 		link_type;
			typedef const rb_tree_node<T>*	const_link_type;
		
		public:
			typedef Key 					key_type;
			typedef T 						value_type;
			typedef value_type* 			pointer;
			typedef const value_type* 		const_pointer;
			typedef value_type& 			reference;
			typedef const value_type& 		const_reference;
			typedef size_t 					size_type;
			typedef ptrdiff_t 				difference_type;
			typedef Alloc 					allocator_type;

			allocator_type get_allocator() const {
				return allocator_type()
			}

		protected:
			node *_root;

		 	iterator end() {
	            return ++rb_tree_node::max(_root->right);
	        }
	        
	        iterator begin() {
				return rb_tree_node::min(_root->left);
	        }
	        
	        reverse_iterator rend() {
	            return _tree.rend();
	        }
	        
	        reverse_iterator rbegin() {
	            return _tree.rbegin();
	        }
	        
	        const_iterator end() const {
	            return _tree.end();
	        }
	        
	        const_iterator begin() const {
	            return _tree.begin();
	        }
	        
	        const_reverse_iterator rend() const {
	            return _tree.rend();
	        }
	        
        const_reverse_iterator rbegin() const {
			//end, begin, rbegin, rend x2
			//iterator find(Key key)
			// 
			link_type get_node()
			{ 
				return _Alloc_traits::allocate(_M_get_Node_allocator(), 1);
			}

			void put_node(link_type p)
			{
				_Alloc_traits::deallocate(_M_get_Node_allocator(), p, 1);
			}

			void construct_node(link_type node, const value_type& x)
			{
				get_allocator().construct(node->_M_valptr(), x);
				put_node(node);
			}

			link_type create_node(const value_type& x)
			{
				link_type __tmp = get_node();
				construct_node(__tmp, x);
				return __tmp;
			}

			void destroy_node(link_type p)
			{
				get_allocator().destroy(p->_M_valptr());
			}

			void drop_node(link_type p)
			{
				destroy_node(p);
				put_node(p);
			}

			template<typename NodeGen>
			link_type clone_node(_Const_Link_type x, NodeGen& node_gen)
			{
				link_type tmp = node_gen(*x->_M_valptr());
				tmp->_color = x->_color;
				tmp->_left = 0;
				tmp->_right = 0;

				return tmp;
			}

	};

};
