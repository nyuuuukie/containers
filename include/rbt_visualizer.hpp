#pragma once

// It is NOT a part of containers, 
// just a useful tool that helps understand red-black trees.

#include <iostream>

#include "rbt.hpp"
#include "rbt_node.hpp"

namespace ft {

struct rbt_visualizer {

private:
	unsigned long long _data_size;
	unsigned long long _space_block_size;
	unsigned long long _total_spaces;
	unsigned long long _space_block;
	std::string	_line;
	std::string	_red;
	std::string	_black;
	std::string	_reset;
	std::string	_full_reset;
	char _space;
	char _hline;
	char _vline;
	char _continue;

	void init(void);

	template <typename T>
	void visualize_lvl(rbt_node<T> *node, int lvl, bool lchild = false);

	std::string center(std::string title, bool lchild = false);

public:
	template <typename T, typename C, typename A>
	explicit rbt_visualizer(ft::rbt<T, C, A> &tree);
	
	rbt_visualizer(void);
	~rbt_visualizer(void);

	template <typename T, typename C, typename A>
	void visualize(ft::rbt<T, C, A> &tree);
};

std::string 
rbt_visualizer::center(std::string title, bool lchild) {

	int spaces = _data_size - title.length();
	spaces = spaces < 0 ? 0 : spaces;

	std::string right(spaces / 2 + (lchild * (spaces % 2)), _space);
	std::string left(spaces / 2 + (!lchild * (spaces % 2)), _space);

	return (left + title + right);
}

void
rbt_visualizer::init(void) {
	_data_size = 4;
	_space_block_size = 1;
	_red = "\033[48;5;196;38;5;232m";
	_black = "\033[48;5;232;38;5;231m";
	_reset = "\033[38;5;220;49m";
	_full_reset = "\033[39;49m";
	_space = ' ';
	_hline = '-';
	_vline = '|';
	_continue = '~';
}

template <typename T, typename C, typename A>
rbt_visualizer::rbt_visualizer(ft::rbt<T, C, A> &tree) {
	init();
	visualize(tree);
}

rbt_visualizer::rbt_visualizer(void) {
	init();
}

rbt_visualizer::~rbt_visualizer(void) {}

template <typename T, typename C, typename A>
void
rbt_visualizer::visualize(ft::rbt<T, C, A> &tree) {

	std::size_t h = tree.height();

	_total_spaces = (1 << h) * _data_size + (1 << (h + 1)) * _space_block_size;

	std::cout << _reset;
    for (std::size_t lvl = 0; lvl <= h; ++lvl) {
		_space_block = (_total_spaces - (1 << lvl) * _data_size) / (1 << (lvl + 1));

		visualize_lvl(tree.root().base(), lvl);

		std::cout << std::endl << _line << std::endl;
		_line.clear();
    }
	std::cout << _full_reset;
}


template <typename T>
void
rbt_visualizer::visualize_lvl(rbt_node<T> *node, int lvl, bool lchild) {

	if (lvl == 0) {
		if (is_leaf_node(node)) {

			std::string data = (_data_size < 4 ? "N" : "NULL");
			data = center(data, lchild);
			
			std::cout << std::string(_space_block, _space);
			std::cout << _black;
			std::cout << std::setw(_data_size) << data << _reset;
			std::cout << std::string(_space_block, _space);
			
			_line.append(_space_block, _space);
			_line.append(_data_size, _space);
			_line.append(_space_block, _space);

		} else {
			const int space_count = _space_block / 2;
			const int lines_count = _space_block - space_count;
			
			std::stringstream ss;
			ss << node->data;
			std::string data = ss.str();
			if (data.length() > _data_size) {
				data.erase(_data_size - 1);
				data.append(1, _continue);
			}
			data = center(data, lchild);

			std::cout << std::string(space_count, _space);
			std::cout << std::string(lines_count, _hline);
			std::cout << (node->color == black ? _black : _red);
			std::cout << std::setw(_data_size) << data << _reset;
			std::cout << std::string(lines_count, _hline);
			std::cout << std::string(space_count, _space);
			
			_line.append(space_count, _space);
			_line.append(1, _vline);
			_line.append(lines_count - 1, _space);
			_line.append(_data_size, _space); 
			_line.append(lines_count - 1, _space);
			_line.append(1, _vline);
			_line.append(space_count, _space);
		}

	} else if (lvl > 0) {
		if (is_leaf_node(node)) {
			for (size_t i = 0; i < (1 << lvl); i++) {
				std::cout << std::string(_space_block, _space);
				std::cout << std::string(_data_size, _space);
				std::cout << std::string(_space_block, _space);
				
				_line.append(_space_block, _space);
				_line.append(_data_size, _space);
				_line.append(_space_block, _space);
			}
		} else {
			visualize_lvl(node->left, lvl - 1, true);
			visualize_lvl(node->right, lvl - 1, false);
		}
	}
}

};