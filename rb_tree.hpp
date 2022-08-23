
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

struct visualizer_sets {
	unsigned long long data_size;
	unsigned long long space_block_size;
	unsigned long long total_spaces;
	unsigned long long space_block;
	std::string line;
	std::string red;
	std::string black;
	std::string reset;
	char space;
	char hline;
	char vline;
};

template <typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<rb_node<T> > >
class rb_tree {

private:

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

	typedef rbt_iterator<value_type>			iterator;
	typedef rbt_iterator<const value_type>		const_iterator;
	typedef reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef reverse_iterator<iterator>			reverse_iterator;

	typedef typename iterator::node_type		node_type;
	typedef typename iterator::node_pointer		node_pointer;

private:
	allocator_type _alloc;
	value_compare _cmp;

public:
	rb_tree(void);
	~rb_tree(void);

	void insert(const_reference data);
	void remove(const_reference data);
	node_type *search(T data);
	
	std::size_t height(void) const;
	void pre_order(void (*)(node_type *) = print);
	void in_order(void (*)(node_type *) = print);
	void post_order(void (*)(node_type *) = print);
	void breadth_order(void (*)(node_type *) = print);

	iterator begin(void);
	iterator end(void);
	const_iterator begin(void) const;
	const_iterator end(void) const;
	reverse_iterator rbegin(void);
	reverse_iterator rend(void);
	const_reverse_iterator rbegin(void) const;
	const_reverse_iterator rend(void) const;

	node_pointer increment(node_type *);
	node_pointer decrement(node_type *);

	void visualize(void) const;
	void visualize_lvl(node_type *node, int lvl, visualizer_sets &sets, bool lchild = false) const;

private:
	bool is_black(node_type *node) const;
	bool is_red(node_type *node) const;
    bool is_left_child(node_type *node) const;
    bool is_right_child(node_type *node) const;

	std::size_t height(node_type *node) const;

	void pre_order(node_type *node, void (*)(node_type *)) const;
	void in_order(node_type *node, void (*)(node_type *)) const;
	void post_order(node_type *node, void (*)(node_type *)) const;
	void breadth_order(node_type *node, int lvl, void (*)(node_type *)) const;

	void rotate_right(node_type *node);
	void rotate_left(node_type *node);

	void insert(node_type *node);
	void insert_balance_fix(node_type *node);

	node_type *search(node_type *node, T key) const;

	// Undone
	void destroy_node(node_type *node);
	void destroy_tree(node_type *node);
	void remove(node_type *node);
	void remove_balance_fix(node_type *node, node_type *parent);

	void swap_nodes(node_type *, node_type *);

private:
	node_type *_root;

};

template <typename T, typename Compare, typename Alloc >
rb_tree<T, Compare, Alloc>::rb_tree(void) : _root(NULL) {}

template <typename T, typename Compare, typename Alloc >
rb_tree<T, Compare, Alloc>::~rb_tree(void) {
	destroy_tree(_root);
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::node_pointer 
rb_tree<T, Compare, Alloc>::increment(node_type *node) {

	if (node == NULL) {
		node = leftmost_node(_root);
	} else if (node->right) {
		node = leftmost_node(node->right);
	} else {
		node = upmost_right_node(node);
	}
	return node;
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::node_pointer
rb_tree<T, Compare, Alloc>::decrement(node_type *node) {

	if (node == NULL) {
		node = rightmost_node(_root);
	} else if (node->left) {
		node = rightmost_node(node->left);
	} else {
		node = upmost_left_node(node);
	}
	return node;
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::iterator 
rb_tree<T, Compare, Alloc>::end(void) {
	return ++iterator(rightmost_node(_root->right));
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::iterator 
rb_tree<T, Compare, Alloc>::begin(void) {
	return iterator(leftmost_node(_root->left));
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::reverse_iterator 
rb_tree<T, Compare, Alloc>::rend(void) {
	return reverse_iterator(begin());
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::reverse_iterator 
rb_tree<T, Compare, Alloc>::rbegin(void) {
	return reverse_iterator(rightmost_node(_root->right));
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::const_iterator 
rb_tree<T, Compare, Alloc>::end(void) const {
	return ++const_iterator(rightmost_node(_root->right));
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::const_iterator 
rb_tree<T, Compare, Alloc>::begin(void) const {
	return const_iterator(leftmost_node(_root->left));
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::const_reverse_iterator 
rb_tree<T, Compare, Alloc>::rend(void) const {
	return const_reverse_iterator(end());
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::const_reverse_iterator 
rb_tree<T, Compare, Alloc>::rbegin(void) const {
	return const_reverse_iterator(begin());
}


template <typename T, typename Compare, typename Alloc >
bool
rb_tree<T, Compare, Alloc>::is_black(node_type *node) const {
    return (node == NULL || node->color == black);
}

template <typename T, typename Compare, typename Alloc >
bool 
rb_tree<T, Compare, Alloc>::is_red(node_type *node) const {
    return !is_black(node);
}

template <typename T, typename Compare, typename Alloc >
bool 
rb_tree<T, Compare, Alloc>::is_left_child(node_type *node) const {
    return (node->parent->left == node);
}

template <typename T, typename Compare, typename Alloc >
bool 
rb_tree<T, Compare, Alloc>::is_right_child(node_type *node) const {
    return !is_left_child(node);
}


template <typename T, typename Compare, typename Alloc >
void rb_tree<T, Compare, Alloc>::rotate_left(node_type *node) {

	node_type *rchild = node->right;
	node->right = rchild->left;

    if (rchild != NULL) {
        rchild->parent = node->parent;

        if (rchild->left != NULL) {
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

    if (lchild != NULL) {
        lchild->parent = node->parent;

        if (lchild->right != NULL) {
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


// Change, split into two different functions
template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::insert(const_reference data) {

	node_type *node = NULL;

	try {
		node = _alloc.allocate(1);
		_alloc.construct(node, data);
    } catch (std::bad_alloc &e) {
        // return end();
    }

	insert(node);
	// change return type to iterator
	// ++size;
	// return iterator(node);
};

template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::insert(node_type *node) {
	
    for (node_type *tmp = _root; tmp; ) {
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
        node_type *uncle = NULL;

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

	if (node != NULL) {
		destroy_tree(node->left);
		destroy_tree(node->right);
		destroy_node(node);
	}
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::destroy_node(node_type *node) {
	
	if (node == NULL) {
		return ;
    }

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	_alloc.deallocate(node, 1);
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::remove(const_reference data) {

	node_type *node = search(data);
	if (node != NULL) {
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

	if (node->left != NULL && node->right != NULL) {
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

	if (child != NULL) {
		child->parent = node->parent;
	}

	if (is_black(node)) {
		remove_balance_fix(child, node->parent);
	}
	destroy_node(node);
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
rb_tree<T, Compare, Alloc>::search(T key) {
	return search(_root, key);
}

template <typename T, typename Compare, typename Alloc >
typename rb_tree<T, Compare, Alloc>::node_type *
rb_tree<T, Compare, Alloc>::search(node_type *node, T data) const {
    
	if (node == NULL) {
		return NULL;
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
std::size_t
rb_tree<T, Compare, Alloc>::height(void) const {
	return height(_root);
}

template <typename T, typename Compare, typename Alloc >
std::size_t
rb_tree<T, Compare, Alloc>::height(node_type *node) const {
	if (node == NULL) {
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

    if (node != NULL) {
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
    if (node != NULL) {
		func(node);
        pre_order(node->left, func);
        pre_order(node->right, func);
    }
}

template <typename T, typename Compare, typename Alloc >		 
void
rb_tree<T, Compare, Alloc>::in_order(node_type *node, void (*func)(node_type *)) const {
	if (node != NULL) {
		in_order(node->left, func);
		func(node);
		in_order(node->right, func);
	}
}

template <typename T, typename Compare, typename Alloc >		
void
rb_tree<T, Compare, Alloc>::post_order(node_type *node, void (*func)(node_type *)) const {
	if (node != NULL) {
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

// Visualizer

std::string 
center(std::string title, int width, bool lchild = false) {
	
	char c = ' ';

	int spaces = width - title.length();
	spaces = spaces < 0 ? 0 : spaces;

	std::string right(spaces / 2 + (lchild * (spaces % 2)), c);
	std::string left(spaces / 2 + (!lchild * (spaces % 2)), c);

	return (left + title + right);
}

template <typename T, typename Compare, typename Alloc >
void
rb_tree<T, Compare, Alloc>::visualize(void) const {

	std::size_t h = height();

	visualizer_sets sets;

	sets.data_size = 2;
	sets.space_block_size = 1;
	sets.total_spaces = (1 << h) * sets.data_size + (1 << (h + 1)) * sets.space_block_size;
	sets.red = "\033[48;5;196;38;5;232m";
	sets.black = "\033[48;5;232;38;5;231m";
	sets.reset = "\033[38;5;220;49m";
	sets.space = ' ';
	sets.hline = '-';
	sets.vline = '|';

	std::cout << sets.reset;
    for (std::size_t lvl = 0; lvl <= h; ++lvl) {
		sets.space_block = (sets.total_spaces - (1 << lvl) * sets.data_size) / (1 << (lvl + 1));

		visualize_lvl(_root, lvl, sets);

		std::cout << std::endl << sets.line << std::endl;
		sets.line.clear();
    }
	std::cout << "\033[39;49m";
}

template <typename T, typename Compare, typename Alloc >
void 
rb_tree<T, Compare, Alloc>::visualize_lvl(node_type *node, int lvl, visualizer_sets &sets, bool lchild) const {

	if (lvl == 0) {
		if (node == NULL) {

			std::string data = (sets.data_size < 4 ? "N" : "NULL");
			data = center(data, sets.data_size, lchild);
			
			std::cout << std::string(sets.space_block, sets.space);
			std::cout << (is_black(node) ? sets.black : sets.red);
			std::cout << std::setw(sets.data_size) << data << sets.reset;
			std::cout << std::string(sets.space_block, sets.space);
			
			sets.line.append(sets.space_block, sets.space);
			sets.line.append(sets.data_size, sets.space);
			sets.line.append(sets.space_block, sets.space);

		} else {

			const int space_count = sets.space_block / 2;
			const int lines_count = sets.space_block - space_count;
			
			std::stringstream ss;
			ss << node->data;
			std::string data = ss.str();
			if (data.length() > sets.data_size) {
				data.erase(sets.data_size - 1);
				data.append(1, '~');
			}
			data = center(data, sets.data_size, lchild);

			std::cout << std::string(space_count, sets.space);
			std::cout << std::string(lines_count, sets.hline);
			std::cout << (is_black(node) ? sets.black : sets.red);
			std::cout << std::setw(sets.data_size) << data << sets.reset;
			std::cout << std::string(lines_count, sets.hline);
			std::cout << std::string(space_count, sets.space);
			
			sets.line.append(space_count, sets.space);
			sets.line.append(1, sets.vline);
			sets.line.append(lines_count - 1, sets.space);
			sets.line.append(sets.data_size, sets.space); 
			sets.line.append(lines_count - 1, sets.space);
			sets.line.append(1, sets.vline);
			sets.line.append(space_count, sets.space);
		}

	} else if (lvl > 0) {
		if (node == NULL) {
			for (size_t i = 0; i < (1 << lvl); i++) {
				std::cout << std::string(sets.space_block, sets.space);
				std::cout << std::string(sets.data_size, sets.space);
				std::cout << std::string(sets.space_block, sets.space);
				
				sets.line.append(sets.space_block, sets.space);
				sets.line.append(sets.data_size, sets.space);
				sets.line.append(sets.space_block, sets.space);
			}
		} else {
			visualize_lvl(node->left, lvl - 1, sets, true);
			visualize_lvl(node->right, lvl - 1, sets, false);
		}
	}                             
}

}
