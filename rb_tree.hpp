#pragma once

#include <memory>

#include "reverse_iterator.hpp"
#include "rb_tree_iterator.hpp"

namespace ft {

	template <typename Key, typename T, typename KeyOfValue, 
	typename Compare, typename Alloc = std::allocator<T> >
	class rb_tree {

			typedef ft::rb_tree_node<T>			node;
			typedef const ft::rb_tree_node<T>	const_node;
		//	typedef rb_tree_node<T>* 		link_type;
		//	typedef const rb_tree_node<T>*	const_link_type;
		
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


			typedef rb_tree_iterator<value_type>					iterator;
			typedef rb_tree_const_iterator<value_type>				const_iterator;
			typedef reverse_iterator<rb_tree_iterator<T> >			reverse_iterator;
			typedef reverse_iterator<rb_tree_const_iterator<T> >	const_reverse_iterator;


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
				return _tree.rbegin();
			}

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
