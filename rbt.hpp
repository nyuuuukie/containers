#pragma once

#include <sstream>  
#include <iomanip>
#include <memory>
#include <iostream>

#include "reverse_iterator.hpp"
#include "rbt_iterator.hpp"
#include "rbt_node.hpp"
#include "pair.hpp"

namespace ft {

template < typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T> >
class rbt {

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

	typedef rbt_node<value_type>	node_type;
	typedef node_type *				node_pointer;

	typedef rbt_iterator<value_type>	   		iterator;
	typedef rbt_const_iterator<value_type>		const_iterator;
	typedef reverse_iterator<const_iterator> 	const_reverse_iterator;
	typedef reverse_iterator<iterator>		 	reverse_iterator;

	typedef typename Alloc::template rebind<rbt_node<value_type> >::other	node_allocator_type;

private:
	node_allocator_type	_alloc;
	value_compare		_cmp;
	node_type *			_root;
	node_type *			_leaf;
	size_type			_size;

public:
	rbt(void);
	rbt(const rbt &other);

	template <class InputIt>
	rbt(InputIt first, InputIt last, 
		const value_compare &comp = value_compare(), 
		const node_allocator_type &alloc = node_allocator_type());

	rbt &operator=(const rbt &other);
	~rbt(void);

	iterator begin(void);
	iterator end(void);
	reverse_iterator rbegin(void);
	reverse_iterator rend(void);

	const_iterator root(void) const;
	const_iterator begin(void) const;
	const_iterator end(void) const;
	const_reverse_iterator rbegin(void) const;
	const_reverse_iterator rend(void) const;
	
	bool empty(void) const;
	size_type size(void) const;
	size_type max_size(void) const;

	template<class InputIt>
	void insert(InputIt first, InputIt last);
	pair<iterator, bool> insert(const_reference data);

	size_type erase(const_reference data);
	void erase(iterator pos);
	void erase(iterator first, iterator last);

	void clear(void);
	void swap(rbt &other);
	
	pair<iterator, iterator> equal_range(const_reference key);
	pair<const_iterator, const_iterator> equal_range( const_reference key) const;
	iterator lower_bound(const_reference key);
	const_iterator lower_bound(const_reference key) const;
	iterator upper_bound(const_reference key);
	const_iterator upper_bound(const_reference key) const;
	size_type height(void) const;
	iterator find(const_reference key);
	size_type count(const_reference key) const;
	const_iterator find(const_reference key) const;

	void pre_order(void (*)(iterator));
	void in_order(void (*)(iterator));
	void post_order(void (*)(iterator));
	void breadth_order(void (*)(iterator));

private:
	void rotate_right(node_type *node);
	void rotate_left(node_type *node);

	void insert(node_type *node);
	void insert_balance(node_type *node);

	void erase(node_type *node);
	void erase_balance(node_type *node, node_type *parent);

	size_type height(node_type *node) const;
	node_type *find(node_type *node, const_reference data) const;

	node_type *create_node(const_reference data);
	void destroy_node(node_type *node);
	void destroy_tree(node_type *node);
	void swap_nodes(node_type *, node_type *);
	void create_leaf(void);
	void destroy_leaf(void);

	void pre_order(node_type *node, void (*)(iterator)) const;
	void in_order(node_type *node, void (*)(iterator)) const;
	void post_order(node_type *node, void (*)(iterator)) const;
	void breadth_order(node_type *node, int lvl, void (*)(iterator)) const;
};

template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::create_leaf(void) {
	_leaf = _alloc.allocate(1);
	_leaf->color = black;
	_leaf->left = NULL;
	_leaf->right = NULL;
	_leaf->parent = NULL;
}

template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::destroy_leaf(void) {
	destroy_node(_leaf);
	_leaf = NULL;
}

// Public interface
template <typename T, typename Compare, typename Alloc >
rbt<T, Compare, Alloc>::rbt(void) 
: _root(NULL), _leaf(NULL), _size(0) {
	create_leaf();
}

template <typename T, typename Compare, typename Alloc >
rbt<T, Compare, Alloc>::~rbt(void) {
	clear();
	destroy_leaf();
}

template <typename T, typename Compare, typename Alloc >
template <class InputIt>
rbt<T, Compare, Alloc>::rbt(
		InputIt first, InputIt last, 
		const value_compare &comp, 
		const node_allocator_type &alloc) : _cmp(comp), _alloc(alloc) {
	create_leaf();
	while (first != last) {
		insert(*first);
		first++;
	}
}

template <typename T, typename Compare, typename Alloc >
rbt<T, Compare, Alloc>::rbt(const rbt &other) 
	: _root(NULL), _leaf(NULL), _size(0) {
	*this = other;
}

template <typename T, typename Compare, typename Alloc >
rbt<T, Compare, Alloc> &
rbt<T, Compare, Alloc>::operator=(const rbt &other) {
	
	if (this != &other) {
		clear();
		destroy_leaf();

		_alloc = other._alloc;
		_cmp = other._cmp;

		create_leaf();
		insert(other.begin(), other.end());
	}
	return *this;
}


// Iterators
template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::iterator 
rbt<T, Compare, Alloc>::end(void) {
	return iterator(_leaf);
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::const_iterator 
rbt<T, Compare, Alloc>::end(void) const {
	return const_iterator(_leaf);
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::iterator 
rbt<T, Compare, Alloc>::begin(void) {
	return (_root ? iterator(leftmost_node(_root)) : end());
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::const_iterator 
rbt<T, Compare, Alloc>::begin(void) const {
	return (_root ? const_iterator(leftmost_node(_root)) : end());
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::reverse_iterator 
rbt<T, Compare, Alloc>::rend(void) {
	return reverse_iterator(end());
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::const_reverse_iterator 
rbt<T, Compare, Alloc>::rend(void) const {
	return const_reverse_iterator(end());
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::reverse_iterator 
rbt<T, Compare, Alloc>::rbegin(void) {
	return reverse_iterator(--end());
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::const_reverse_iterator 
rbt<T, Compare, Alloc>::rbegin(void) const {
	return const_reverse_iterator(--end());
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::const_iterator
rbt<T, Compare, Alloc>::root(void) const {
	return const_iterator(_root);
}


// Capacity
template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::size_type 
rbt<T, Compare, Alloc>::size(void) const {
	return _size;
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::size_type 
rbt<T, Compare, Alloc>::max_size(void) const {
	return _alloc.max_size();
}

template <typename T, typename Compare, typename Alloc >
bool
rbt<T, Compare, Alloc>::empty(void) const {
	return (_size == 0);
}


// Modifiers
template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::clear(void) {
	destroy_tree(_root);
	_root = NULL;
	if (_leaf != NULL) {
		_leaf->parent = NULL;
	}
}

template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::swap(rbt &other) {

	node_allocator_type	tmp_alloc = _alloc;
	value_compare		tmp_cmp = _cmp;
	node_type *			tmp_root = _root;
	node_type *			tmp_leaf = _leaf;
	size_type			tmp_size = _size;

	_alloc = other._alloc;
	_cmp = other._cmp;
	_root = other._root;
	_leaf = other._leaf;
	_size = other._size;

	other._alloc = tmp_alloc;
	other._cmp = tmp_cmp;
	other._root = tmp_root;
	other._leaf = tmp_leaf;
	other._size = tmp_size;
}

template <typename T, typename Compare, typename Alloc >
template<class InputIt>
void
rbt<T, Compare, Alloc>::insert(InputIt first, InputIt last) {
	while (first != last) {
		insert(*first);
		first++;
	}
}

template <typename T, typename Compare, typename Alloc >
pair<typename rbt< T, Compare, Alloc>::iterator, bool>
rbt<T, Compare, Alloc>::insert(const_reference data) {

	node_type *node = NULL;
	try {
		node = create_node(data);
	} catch (std::bad_alloc &e) {
		return ft::make_pair(end(), false); // Not like that
	}

	insert(node);

	return ft::make_pair(iterator(node), true);
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::size_type
rbt<T, Compare, Alloc>::erase(const_reference data) {

	iterator it = find(data);
	if (it != end()) {
		erase(it.base());
		return 1;
    }
	return 0;
}

template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::erase(iterator pos) {
	erase(pos.base());
}

template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::erase(iterator first, iterator last) {
	while (first != last) {
		erase(first);
		first++;
	}
}


// Lookup
template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::iterator
rbt<T, Compare, Alloc>::find(const_reference data) {
	return iterator(find(_root, data));
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::size_type
rbt<T, Compare, Alloc>::height(void) const {
	return height(_root);
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::size_type
rbt<T, Compare, Alloc>::count(const_reference data) const {
	
	size_type count = 0;
	for (node_type *tmp = _root; tmp && tmp != _leaf; ) {
		if (!_cmp(data, tmp->data)) {
			if (!_cmp(tmp->data, data)) {
				count++;
			}
			tmp = tmp->right;
		} else {
			tmp = tmp->left;
		}
    }
	return count;
}

template <typename T, typename Compare, typename Alloc >
pair<typename rbt<T, Compare, Alloc>::iterator, typename rbt<T, Compare, Alloc>::iterator> 
rbt<T, Compare, Alloc>::equal_range(const_reference key) {
	return ft::make_pair(lower_bound(key), upper_bound(key));
}

template <typename T, typename Compare, typename Alloc >
pair<typename rbt<T, Compare, Alloc>::const_iterator, typename rbt<T, Compare, Alloc>::const_iterator> 
rbt<T, Compare, Alloc>::equal_range(const_reference key) const {
	return ft::make_pair(lower_bound(key), upper_bound(key));
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::iterator
rbt<T, Compare, Alloc>::lower_bound(const_reference key) {
	
	node_pointer tmp = _root;
	node_pointer closest = NULL;
	while (tmp && tmp != _leaf) {
		if (!_cmp(tmp->data, key)) {
			closest = tmp;
			tmp = tmp->left;
		} else {
			tmp = tmp->right;
		}
	}

	if (closest == NULL) {
		return end();
	}
	return iterator(closest);
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::const_iterator
rbt<T, Compare, Alloc>::lower_bound(const_reference key) const {
	
	node_pointer tmp = _root;
	node_pointer closest = NULL;
	while (tmp && tmp != _leaf) {
		if (!_cmp(tmp->data, key)) {
			closest = tmp;
			tmp = tmp->left;
		} else {
			tmp = tmp->right;
		}
	}

	if (closest == NULL) {
		return end();
	}
	return const_iterator(closest);
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::iterator
rbt<T, Compare, Alloc>::upper_bound(const_reference key) {
	
	node_pointer tmp = _root;
	node_pointer closest = NULL;
	while (tmp && tmp != _leaf) {
		if (_cmp(key, tmp->data)) {
			closest = tmp;
			tmp = tmp->left;
		} else {
			tmp = tmp->right;
		}
	}

	if (closest == NULL) {
		return end();
	}
	return iterator(closest);
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::const_iterator
rbt<T, Compare, Alloc>::upper_bound(const_reference key) const {
	
	node_pointer tmp = _root;
	node_pointer closest = NULL;
	while (tmp && tmp != _leaf) {
		if (_cmp(key, tmp->data)) {
			closest = tmp;
			tmp = tmp->left;
		} else {
			tmp = tmp->right;
		}
	}

	if (closest == NULL) {
		return end();
	}
	return const_iterator(closest);
}

// Functional Tree Traversal 
template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::breadth_order(void (*func)(iterator)) {

    const std::size_t h = height();
    for (std::size_t i = 1; i <= h; ++i) {
        breadth_order(_root, i, func);
    }
}

template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::in_order(void (*func)(iterator)) {
    in_order(_root, func);
}

template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::pre_order(void (*func)(iterator)) {
    pre_order(_root, func);
}

template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::post_order(void (*func)(iterator)) {
    post_order(_root, func);
}


// Internal implementation
template <typename T, typename Compare, typename Alloc >
void rbt<T, Compare, Alloc>::rotate_left(node_type *node) {

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
void rbt<T, Compare, Alloc>::rotate_right(node_type *node) {

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
rbt<T, Compare, Alloc>::insert(node_type *node) {
	
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

	insert_balance(node);
	_size++;
	_leaf->parent = rightmost_node(_root);
};

template <typename T, typename Compare, typename Alloc >
void 
rbt<T, Compare, Alloc>::insert_balance(node_type *node) {

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
rbt<T, Compare, Alloc>::erase(node_type *node) {

	if (node == _leaf) {
		return ;
	}

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
		erase_balance(child, node->parent);
	}

	if (_leaf->parent == node) {
		_leaf->parent = rightmost_node(_root);
	}
	
	destroy_node(node);
	_size--;
}

template <typename T, typename Compare, typename Alloc >
void 
rbt<T, Compare, Alloc>::erase_balance(node_type *node, node_type *parent) {

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
void 
rbt<T, Compare, Alloc>::swap_nodes(node_type *first, node_type *second) {

		node_type *tmpparent = first->parent;
		node_type *tmpleft = first->left;
		node_type *tmpright = first->right;
		rb_color tmpcolor = first->color;

		// Changing first node
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

		// Changing second node
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
rbt<T, Compare, Alloc>::destroy_tree(node_type *node) {

	if (node != NULL && node != _leaf) {
		destroy_tree(node->left);
		destroy_tree(node->right);
		destroy_node(node);
	}
}

template <typename T, typename Compare, typename Alloc >
void
rbt<T, Compare, Alloc>::destroy_node(node_type *node) {

	if (node == NULL) {
		return ;
	}

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	_alloc.deallocate(node, 1);
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::node_type * 
rbt<T, Compare, Alloc>::create_node(const_reference data) {

	node_type *node = _alloc.allocate(1);
	_alloc.construct(node, data);

	node->right = _leaf;
	node->left = _leaf;

	return node;
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::node_type *
rbt<T, Compare, Alloc>::find(node_type *node, const_reference data) const {
    
	if (node == _leaf) {
		return _leaf;
	}
	
	if (!_cmp(data, node->data) && !_cmp(node->data, data)) {
		return node;
    } else if (!_cmp(data, node->data)) {
		return find(node->right, data);
	} else {
		return find(node->left, data);
	}
}

template <typename T, typename Compare, typename Alloc >
typename rbt<T, Compare, Alloc>::size_type
rbt<T, Compare, Alloc>::height(node_type *node) const {
	if (node == _leaf) {
		return 0;
	}
	size_t lmax = height(node->left);
	size_t rmax = height(node->right);
    return lmax > rmax ? lmax + 1 : rmax + 1;	
}


// Functional Tree Traversal
template <typename T, typename Compare, typename Alloc >
void 
rbt<T, Compare, Alloc>::breadth_order(node_type *node, int lvl, void (*func)(iterator)) const {

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
rbt<T, Compare, Alloc>::pre_order(node_type *node, void (*func)(iterator)) const {
    if (node != _leaf) {
		func(node);
        pre_order(node->left, func);
        pre_order(node->right, func);
    }
}

template <typename T, typename Compare, typename Alloc >		 
void
rbt<T, Compare, Alloc>::in_order(node_type *node, void (*func)(iterator)) const {
	if (node != _leaf) {
		in_order(node->left, func);
		func(node);
		in_order(node->right, func);
	}
}

template <typename T, typename Compare, typename Alloc >		
void
rbt<T, Compare, Alloc>::post_order(node_type *node, void (*func)(iterator)) const {
	if (node != _leaf) {
		post_order(node->left, func);
		post_order(node->right, func);
		func(node);
	}
};

};
