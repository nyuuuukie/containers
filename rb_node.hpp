#pragma once

namespace ft {

	enum rb_color { black, red };

	template<class T>
	struct rb_node {

		T           data;
		rb_color    color;
		rb_node<T> *left;
		rb_node<T> *right;
		rb_node<T> *parent;
		
		rb_node(T data)
			: data(data)
			, color(red)
			, parent(NULL)
			, left(NULL)
			, right(NULL) { };
	};

	template<class T>
	rb_node<T> *
	leftmost_node(rb_node<T> *node) {
		while (node->left != NULL) {
			node = node->left;
		}
		return node;
	}

	template<class T>
	rb_node<T> *
	rightmost_node(rb_node<T> *node) {
		while (node->right != NULL) {
			node = node->right;
		}
		return node;
	}

	template<class T>
	rb_node<T> *
	upmost_right_node(rb_node<T> *node) {
		while (node->parent && node->parent->right == node) {
			node = node->parent;
		}
		node = node->parent;
		return node;
	}

	template<class T>
	rb_node<T> *
	upmost_left_node(rb_node<T> *node) {
		while (node->parent && node->parent->left == node) {
			node = node->parent;
		}
		node = node->parent;
		return node;
	}

};