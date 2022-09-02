#pragma once

namespace ft {

	enum rb_color { black, red };

	template<class T>
	struct rbt_node {

		T           data;
		rb_color    color;
		rbt_node<T> *left;
		rbt_node<T> *right;
		rbt_node<T> *parent;
		
		rbt_node(T data)
			: data(data)
			, color(red)
			, parent(NULL)
			, left(NULL)
			, right(NULL) { };
	};

	template<class T>
	bool
	is_leaf_node(rbt_node<T> *node) {
		return (node && node->left == NULL);
	}

	template <typename T>
	bool 
	is_left_child(rbt_node<T> *node) {
		return (node->parent->left == node);
	}

	template <typename T>
	bool 
	is_right_child(rbt_node<T> *node) {
		return !is_left_child(node);
	}

	template <typename T>
	bool
	is_black(rbt_node<T> *node) {
		return (node == NULL || node->color == black);
	}

	template <typename T>
	bool
	is_red(rbt_node<T> *node) {
		return !is_black(node);
	}

	template<class T>
	rbt_node<T> *
	leftmost_node(rbt_node<T> *node) {
		
		if (node == NULL) {
			return NULL;
		}

		while (!is_leaf_node(node->left)) {
			node = node->left;
		}
		return node;
	}

	template<class T>
	rbt_node<T> *
	rightmost_node(rbt_node<T> *node) {

		if (node == NULL) {
			return NULL;
		}

		while (!is_leaf_node(node->right)) {
			node = node->right;
		}
		return node;
	}

	template<class T>
	rbt_node<T> *
	upmost_node(rbt_node<T> *node) {

		while (node != NULL && node->parent != NULL) {
			node = node->parent;
		}
		return node;
	}

	template<class T>
	rbt_node<T> *
	upmost_right_node(rbt_node<T> *node) {

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
	rbt_node<T> *
	upmost_left_node(rbt_node<T> *node) {

		if (node == NULL) {
			return NULL;
		}
	
		while (node->parent != NULL && node->parent->left == node) {
			node = node->parent;
		}
		node = node->parent;
		return node;
	}

	template<class T>
	rbt_node<T> *
	increment(rbt_node<T> * node) {

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

	template <typename T>
	rbt_node<T> *
	decrement(rbt_node<T> *node) {

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

};