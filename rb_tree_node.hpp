#pragma once

namespace ft {

	enum rb_tree_color {
		red = false,
		black = true
	};

	template <typename T>
	struct rb_tree_node {

		typedef rb_tree_node<T>*		pointer;
		typedef rb_tree_node<T>&		reference;
		typedef const rb_tree_node<T>*	const_pointer;
		typedef const rb_tree_node<T>&	const_reference;

		typedef rb_tree_color		color_type;
		typedef T					value_type;

		pointer		_parent;
		pointer		_left;
		pointer		_right;
		color_type	_color;
		value_type	_value;

		static pointer min(pointer node)
		{
			while (node->_left != 0)
				node = node->_left;
			return node;
		}

		static pointer max(pointer node)
		{
			while (node->_right != 0)
				node = node->_right;
			return node;
		}
	};

};