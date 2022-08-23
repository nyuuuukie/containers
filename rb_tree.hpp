#pragma once

#include <sstream>  
#include <iomanip>
#include <memory>

#include "reverse_iterator.hpp"
#include "rbt_iterator.hpp"
#include "rb_node.hpp"

namespace ft {

template <typename T>
void print(rb_node<T> *node);

template <typename T>
void print_detailed(rb_node<T> *node);

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<rb_node<T> > >
class rb_tree {

public:
	typedef Compare					value_compare;
	typedef T 						value_type;
	typedef size_t 					size_type;
	typedef ptrdiff_t 				difference_type;
	typedef Alloc 					allocator_type;

	typedef value_type* 			pointer;
	typedef const value_type* 		const_pointer;
	typedef value_type& 			reference;
	typedef const value_type& 		const_reference;

	typedef rb_node<value_type>		node_type;
	typedef node_type *				node_pointer;

	typedef rbt_iterator<node_pointer>	     iterator;
	typedef rbt_const_iterator<node_pointer> const_iterator;
	typedef reverse_iterator<const_iterator> const_reverse_iterator;
	typedef reverse_iterator<iterator>		 reverse_iterator;
 

private:
	allocator_type	_alloc;
	value_compare	_cmp;
	node_type *		_root;
	node_type *		_leaf;
	size_type		_size;

public:
	rb_tree(void);
	~rb_tree(void);

	void insert(const_reference data);
	void remove(const_reference data);
	node_type *search(const_reference data);

	size_type size(void) const;
	size_type height(void) const;

	iterator begin(void);
	iterator end(void);
	reverse_iterator rbegin(void);
	reverse_iterator rend(void);

	const_iterator begin(void) const;
	const_iterator end(void) const;
	const_reverse_iterator rbegin(void) const;
	const_reverse_iterator rend(void) const;

	node_type *get_root(void) const;

	void pre_order(void (*)(node_type *) = print);
	void in_order(void (*)(node_type *) = print);
	void post_order(void (*)(node_type *) = print);
	void breadth_order(void (*)(node_type *) = print);

private:
	void rotate_right(node_type *node);
	void rotate_left(node_type *node);

	size_type height(node_type *node) const;

	node_type *create_node(const_reference data);
	node_type *search(node_type *node, const_reference data) const;

	void insert(node_type *node);
	void insert_balance_fix(node_type *node);

	void remove(node_type *node);
	void remove_balance_fix(node_type *node, node_type *parent);

	void destroy_node(node_type *node);
	void destroy_tree(node_type *node);

	void swap_nodes(node_type *, node_type *);

	void pre_order(node_type *node, void (*)(node_type *)) const;
	void in_order(node_type *node, void (*)(node_type *)) const;
	void post_order(node_type *node, void (*)(node_type *)) const;
	void breadth_order(node_type *node, int lvl, void (*)(node_type *)) const;
};

// Public interface

template <typename T, typename Compare, typename Alloc >
rb_tree<T, Compare, Alloc>::rb_tree(void) 
: _root(NULL), _size(0) {
	_leaf = _alloc.allocate(1);
	_leaf->color = black;
	_leaf->left = NULL;
	_leaf->right = NULL;
	_leaf->parent = NULL;
}

template <typename T, typename Compare, typename Alloc >
rb_tree<T, Compare, Alloc>::~rb_tree(void) {
	destroy_tree(_root);
	destroy_node(_leaf);
}


template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::iterator 
rb_tree<T, Compare, Alloc>::end(void) {
	return iterator(_leaf);
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::const_iterator 
rb_tree<T, Compare, Alloc>::end(void) const {
	return const_iterator(_leaf);
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::iterator 
rb_tree<T, Compare, Alloc>::begin(void) {
	return (_root ? iterator(leftmost_node(_root)) : end());
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::const_iterator 
rb_tree<T, Compare, Alloc>::begin(void) const {
	return (_root ? const_iterator(leftmost_node(_root)) : end());
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::reverse_iterator 
rb_tree<T, Compare, Alloc>::rend(void) {
	return reverse_iterator(end());
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::const_reverse_iterator 
rb_tree<T, Compare, Alloc>::rend(void) const {
	return const_reverse_iterator(end());
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::reverse_iterator 
rb_tree<T, Compare, Alloc>::rbegin(void) {
	return reverse_iterator(--end());
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::const_reverse_iterator 
rb_tree<T, Compare, Alloc>::rbegin(void) const {
	return const_reverse_iterator(--end());
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::node_type * 
rb_tree<T, Compare, Alloc>::create_node(const_reference data) {

	node_type *node = _alloc.allocate(1);
	_alloc.construct(node, data);

	node->right = _leaf;
	node->left = _leaf;

	return node;
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::node_type * 
rb_tree<T, Compare, Alloc>::get_root(void) const {
	return _root;
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::size_type 
rb_tree<T, Compare, Alloc>::size(void) const {
	return _size;
}

template <typename T, typename Compare, typename Alloc >
void rb_tree<T, Compare, Alloc>::rotate_left(node_type *node) {

	node_type *rchild = node->right;
	node->right = rchild->left;

    if (rchild != _leaf) {
        rchild->parent = node->parent;

        if (rchild->left != _leaf) {
            rchild->left->parent = node;
        }
        rchild->left = node;
    }

	if (node->parent == NULL) {
		_root = rchild;
    } else if (node == node->parent->left) {
        node->parent->left = rchild;
    } else {
        node->parent->right = rchild;
    }

	node->parent = rchild;
};

template <typename T, typename Compare, typename Alloc >
void rb_tree<T, Compare, Alloc>::rotate_right(node_type *node) {

	node_type *lchild = node->left;
	node->left = lchild->right;

    if (lchild != _leaf) {
        lchild->parent = node->parent;

        if (lchild->right != _leaf) {
            lchild->right->parent = node;
        }

        lchild->right = node;
    }

	if (node->parent == NULL) {
		_root = lchild;
    } else if (node == node->parent->right) {
        node->parent->right = lchild;
    } else {
        node->parent->left = lchild;
	}

	node->parent = lchild;
};

template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::insert(const_reference data) {

	node_type *node = create_node(data);

	insert(node);
	// change return type to iterator
	// return iterator(node);
};

template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::insert(node_type *node) {
	
    for (node_type *tmp = _root; tmp && tmp != _leaf; ) {
		node->parent = tmp;
        tmp = !_cmp(node->data, tmp->data) ? tmp->right : tmp->left;
    }

	if (node->parent == NULL) {
		_root = node;
	} else if (!_cmp(node->data, node->parent->data)) {
        node->parent->right = node;
    } else {
        node->parent->left = node;
    }

	insert_balance_fix(node);
	_size++;
	_leaf->parent = rightmost_node(_root);
};

template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::insert_balance_fix(node_type *node) {

	while (node != _root) {

        if (is_black(node->parent)) {
            break ;
        }

        node_type *parent = node->parent;
        node_type *grandpa = parent->parent;
        node_type *uncle = _leaf;

		if (is_left_child(parent)) {
            uncle = grandpa->right;
			if (is_black(uncle)) {
				if (is_right_child(node)) {
					rotate_left(parent);
				}
				rotate_right(grandpa);
			} else {
                node = grandpa;
                uncle->color = black;
            }
		} else {
			uncle = grandpa->left;
			if (is_black(uncle)) {
				if (is_left_child(node)) {
					rotate_right(parent);
				}
				rotate_left(grandpa);
			} else {
                node = grandpa;
                uncle->color = black;
            }
		}

        parent->color = black;
        grandpa->color = red;
	}
	_root->color = black;
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::destroy_tree(node_type *node) {

	if (node && node != _leaf) {
		destroy_tree(node->left);
		destroy_tree(node->right);
		destroy_node(node);
	}
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::destroy_node(node_type *node) {
	
	if (node == _leaf) {
		return ;
    }

	node->parent = _leaf;
	node->left = _leaf;
	node->right = _leaf;

	_alloc.deallocate(node, 1);
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::remove(const_reference data) {

	node_type *node = search(data);
	if (node != _leaf) {
		remove(node);
    }
}

template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::swap_nodes(node_type *first, node_type *second) {

		node_type *tmpparent = first->parent;
		node_type *tmpleft = first->left;
		node_type *tmpright = first->right;
		rb_color tmpcolor = first->color;

		// Change first node
		if (first->parent == NULL) {
			_root = second;
		} else if (is_left_child(first)) {
			first->parent->left = second;
		} else {
			first->parent->right = second;
		}

		first->parent = second->parent;
		first->left = second->left;
		if (first->left) {
			first->left->parent = first;
		}
		first->right = second->right;
		if (first->right) {
			first->right->parent = first;
		}
		first->color = second->color;

		// Change second node
		if (second->parent == NULL) {
			_root = first;
		} else if (is_left_child(second)) {
			second->parent->left = first;
		} else {
			second->parent->right = first;
		}

		second->parent = tmpparent;		
		second->left = tmpleft;
		if (second->left) {
			second->left->parent = second;
		}
		second->right = tmpright;
		if (second->right) {
			second->right->parent = second;
		}
		second->color = tmpcolor;
}

template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::remove(node_type *node) {

	if (node->left != _leaf && node->right != _leaf) {
		// 2 childs
		node_type *successor = leftmost_node(node->right);
		swap_nodes(node, successor);
	}

	// 0 or 1 child
	node_type *child = node->left ? node->left : node->right;
	if (node->parent == NULL) {
		_root = child;
	} else if (is_left_child(node)) {
		node->parent->left = child;
	} else {
		node->parent->right = child;
	}

	if (child != _leaf) {
		child->parent = node->parent;
	}

	if (is_black(node)) {
		remove_balance_fix(child, node->parent);
	}

	if (_leaf->parent == node) {
		_leaf->parent = rightmost_node(_root);
	}
	
	destroy_node(node);
	_size--;
}

template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::remove_balance_fix(node_type *node, node_type *parent) {

	while (is_black(node) && node != _root) {

		if (parent->left == node) {
			node_type *uncle = parent->right;
			if (is_red(uncle)) {
				uncle->color = black;
				parent->color = red;
				rotate_left(parent);
			}

			if (is_black(uncle->left) && is_black(uncle->right)) {
				uncle->color = red;
			} else {
				if (is_black(uncle->right)) {
					uncle->left->color = black;
					uncle->color = red;
					rotate_right(uncle);
				}
				uncle->color = parent->color;
				parent->color = black;
				uncle->right->color = black;
				rotate_left(parent);
				node = _root;
			}
		} else {
			node_type *uncle = parent->left;
			if (is_red(uncle)) {
				uncle->color = black;
				parent->color = red;
				rotate_right(parent);
			}
           
			if (is_black(uncle->left) && is_black(uncle->right)) {
				uncle->color = red;
			} else {
				if (is_black(uncle->left)) {
					uncle->right->color = black;
					uncle->color = red;
					rotate_left(uncle);
				}
				uncle->color = parent->color;
				parent->color = black;
				uncle->left->color = black;
				rotate_right(parent);
				node = _root;
			}
		}
	}
	node->color = black;
	_root->color = black;
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::node_type *
rb_tree<T, Compare, Alloc>::search(const_reference data) {
	return search(_root, data);
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::node_type *
rb_tree<T, Compare, Alloc>::search(node_type *node, const_reference data) const {
    
	if (node == _leaf) {
		return _leaf;
	}
	
	if (!_cmp(data, node->data) && !_cmp(node->data, data)) {
		return node;
    } else if (!_cmp(data, node->data)) {
		return search(node->right, data);
	} else {
		return search(node->left, data);
	}
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::size_type
rb_tree<T, Compare, Alloc>::height(void) const {
	return height(_root);
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::size_type
rb_tree<T, Compare, Alloc>::height(node_type *node) const {
	if (node == _leaf) {
		return 0;
	}
	size_t lmax = height(node->left);
	size_t rmax = height(node->right);
    return lmax > rmax ? lmax + 1 : rmax + 1;	
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::breadth_order(void (*func)(node_type *)) {

    const std::size_t h = height();
    for (std::size_t i = 1; i <= h; ++i) {
        breadth_order(_root, i, func);
    }
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::in_order(void (*func)(node_type *)) {
    in_order(_root, func);
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::pre_order(void (*func)(node_type *)) {
    pre_order(_root, func);
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::post_order(void (*func)(node_type *)) {
    post_order(_root, func);
}

template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::breadth_order(node_type *node, int lvl, void (*func)(node_type *)) const {

    if (node != _leaf) {
		if (lvl == 1) {
			func(node);
		} else if (lvl > 1) {
			breadth_order(node->left, lvl - 1, func);
			breadth_order(node->right, lvl - 1, func);
		}
    }
}

template <typename T, typename Compare, typename Alloc >		 
void
rb_tree<T, Compare, Alloc>::pre_order(node_type *node, void (*func)(node_type *)) const {
    if (node != _leaf) {
		func(node);
        pre_order(node->left, func);
        pre_order(node->right, func);
    }
}

template <typename T, typename Compare, typename Alloc >		 
void
rb_tree<T, Compare, Alloc>::in_order(node_type *node, void (*func)(node_type *)) const {
	if (node != _leaf) {
		in_order(node->left, func);
		func(node);
		in_order(node->right, func);
	}
}

template <typename T, typename Compare, typename Alloc >		
void
rb_tree<T, Compare, Alloc>::post_order(node_type *node, void (*func)(node_type *)) const {
	if (node != _leaf) {
		post_order(node->left, func);
		post_order(node->right, func);
		func(node);
	}
};

template <typename T>
void
print(rb_node<T> *node) {
	std::cout << node->data << " ";
}

template <typename T>
void
print_detailed(rb_node<T> *node) {

	if (node == NULL) {
		return ;
 	}

	struct u {
		static std::string print_node(rb_node<T> *node) {
			std::stringstream ss;
			ss << std::setw(10) << node->data << (node->color ? "(R)" : "(B)");
			return ss.str();
		}
 	};

	std::cout << u::print_node(node);
	if (node->parent == NULL) {
		std::cout << std::setw(20) << " tree's root" << std::endl; 
	} else if (node->parent->left == node) {
		std::cout << u::print_node(node->parent) << " -> left" << std::endl;
	} else {
		std::cout << u::print_node(node->parent) << " -> right" << std::endl;
	}
}

}
