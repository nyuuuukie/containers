#pragma once

#include <memory>

namespace ft {
	
	template <typename Key, typename T, typename KeyOfValue, 
			typename Compare, typename Alloc = std::allocator<T> >
    class rb_tree {
	
		protected:
			typedef rb_tree_node_base* 			_Base_ptr;
			typedef const _Rb_tree_node_base* 	_Const_Base_ptr;
			typedef rb_tree_node<_Val>* 		_Link_type;
			typedef const _Rb_tree_node<_Val>*	_Const_Link_type;

	};

};