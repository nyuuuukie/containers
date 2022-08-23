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
	bool
	is_leaf_node(rb_node<T> *node) {
		return (node && node->left == NULL);
	}

	template <typename T>
	bool 
	is_left_child(rb_node<T> *node) {
		return (node->parent->left == node);
	}

	template <typename T>
	bool 
	is_right_child(rb_node<T> *node) {
		return !is_left_child(node);
	}

	template <typename T>
	bool
	is_black(rb_node<T> *node) {
		return (node == NULL || node->color == black);
	}

	template <typename T>
	bool
	is_red(rb_node<T> *node) {
		return !is_black(node);
	}

	template<class T>
	rb_node<T> *
	leftmost_node(rb_node<T> *node) {
		
		if (node == NULL) {
			return NULL;
		}

		while (!is_leaf_node(node->left)) {
			node = node->left;
		}
		return node;
	}

	template<class T>
	rb_node<T> *
	rightmost_node(rb_node<T> *node) {

		if (node == NULL) {
			return NULL;
		}

		while (!is_leaf_node(node->right)) {
			node = node->right;
		}
		return node;
	}

	template<class T>
	rb_node<T> *
	upmost_node(rb_node<T> *node) {

		while (node != NULL && node->parent != NULL) {
			node = node->parent;
		}
		return node;
	}

	template<class T>
	rb_node<T> *
	upmost_right_node(rb_node<T> *node) {

		if (node == NULL) {
			return NULL;
		}

		while (node->parent != NULL && node->parent->right == node) {
			node = node->parent;
		}
		node = node->parent;
		return node;
	}

	template<class T>
	rb_node<T> *
	upmost_left_node(rb_node<T> *node) {

		if (node == NULL) {
			return NULL;
		}
	
		while (node->parent != NULL && node->parent->left == node) {
			node = node->parent;
		}
		node = node->parent;
		return node;
	}

};