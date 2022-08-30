#pragma once

#include <memory>

#include "pair.hpp"
#include "rbt.hpp"
#include "reverse_iterator.hpp"
#include "map_iterator.hpp"
#include "map_value_compare.hpp"

namespace ft {

template <typename Key, typename T, typename Comp = ft::less<Key>, 
		  typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map {

public:
	typedef Key 									key_type;
	typedef T 										mapped_type;
	typedef ft::pair<const Key, T>					value_type;
	typedef size_t                                  size_type;
	typedef Comp									key_compare;
	typedef Alloc                               	allocator_type;

	typedef typename Alloc::pointer        			pointer;
	typedef typename Alloc::const_pointer  			const_pointer;
	typedef typename Alloc::reference      			reference;
	typedef typename Alloc::const_reference			const_reference;

	// Member classes
	class value_compare : ft::binary_function<value_type, value_type, bool> {
		
		friend class map;

		public:
			bool operator()(const value_type &lhs, const value_type &rhs) const {
				return _comp(lhs.first, rhs.first);
			}

		protected:
			key_compare _comp;

			value_compare(key_compare comp) : _comp(comp) {}			
	};

	typedef rbt<value_type, map_value_compare<key_type, value_type, key_compare>, allocator_type> tree_type;

	typedef map_iterator<typename tree_type::iterator>			    iterator;
	typedef map_const_iterator<typename tree_type::const_iterator>	const_iterator;
	typedef reverse_iterator<const_iterator>						const_reverse_iterator;
	typedef reverse_iterator<iterator>								reverse_iterator;

	typedef typename iterator::difference_type     	difference_type;

private:
	tree_type _tree;

public:
	map(void);

	explicit map(const key_compare &comp, const allocator_type &alloc = allocator_type());

	template <class InputIt>
	map(InputIt first, InputIt last, const key_compare &comp = key_compare(), const Alloc &alloc = allocator_type());

	map(const map &other);

	map& operator=(const map &other);
	
	~map(void) {}


	// Allocator
	allocator_type get_allocator() const;


	// Element access
	T& at(const Key &key);
	const T& at(const Key &key) const;
	T& operator[](const Key &key);

	// Iterators
	iterator end(void);
	iterator begin(void);
	reverse_iterator rend(void);
	reverse_iterator rbegin(void);
	const_iterator end(void) const;
	const_iterator begin(void) const;
	const_reverse_iterator rend(void) const;
	const_reverse_iterator rbegin(void) const;

	// Capacity
	size_type size(void) const;
	size_type max_size(void) const;
	bool empty(void) const;
        
	// Lookup 
	size_type count(const Key &key) const;
	iterator find(const Key &key);
	const_iterator find(const Key &key) const;
	pair<iterator, iterator> equal_range(const Key &key);
	pair<const_iterator, const_iterator> equal_range(const Key &key) const;
	iterator lower_bound(const Key &key);
	const_iterator lower_bound(const Key &key) const;
	iterator upper_bound(const Key &key);
	const_iterator upper_bound(const Key &key) const;
		
	// Observers
	key_compare key_comp() const;
	value_compare value_comp() const;
        

	// Modifiers
	template <class InputIt>
	void insert(InputIt first, InputIt last);
	
	iterator insert(iterator hint, const value_type &val);
	pair<iterator, bool> insert(const value_type &value);
	
	void erase(iterator position);
	void erase(iterator first, iterator last);
	size_type erase(const Key &key);

	void swap(map &other);
	void clear(void);

	template <typename K, typename M, typename C, typename A>
	friend bool operator==(const map<K, M, C, A> &lhs, const map<K, M, C, A> &rhs);

	template <typename K, typename M, typename C, typename A> 
	friend bool	operator<(const map<K, M, C, A> &lhs, const map<K, M, C, A> &rhs);

};

template <typename Key, typename T, typename Comp, typename Alloc>
map<Key, T, Comp, Alloc>::map(void) {}

template <typename Key, typename T, typename Comp, typename Alloc>
map<Key, T, Comp, Alloc>::map(const key_compare &comp, const allocator_type &alloc) {}


template <typename Key, typename T, typename Comp, typename Alloc>
template <class InputIt>
map<Key, T, Comp, Alloc>::map(InputIt first, InputIt last, const key_compare &comp, const Alloc &alloc) {
	// Change comparator and allocator ?
	_tree.insert(first, last);
}

template <typename Key, typename T, typename Comp, typename Alloc>
map<Key, T, Comp, Alloc>::map(const map& other) : _tree(other._tree) {}
 
template <typename Key, typename T, typename Comp, typename Alloc>
map<Key, T, Comp, Alloc>& map<Key, T, Comp, Alloc>::operator=(const map &other) {
	if (this != &other) {
		_tree = other._tree;
	}
	return *this;
}

template <typename Key, typename T, typename Comp, typename Alloc>	
map<Key, T, Comp, Alloc>::~map(void) {}


// Allocator
template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::allocator_type
map<Key, T, Comp, Alloc>::get_allocator(void) const {
	return allocator_type(_tree.get_allocator());
}


// Element access	
template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::mapped_type & 
map<Key, T, Comp, Alloc>::at(const Key &key) {
	iterator it = find(key);
	
	if (it == end()) {
		throw std::out_of_range("map::at() - value not found");
	}
	return it->second;
}

template <typename Key, typename T, typename Comp, typename Alloc>	
const typename map<Key, T, Comp, Alloc>::mapped_type & 
map<Key, T, Comp, Alloc>::at(const Key &key) const {
	const_iterator it = find(key);
	
	if (it == end()) {
		throw std::out_of_range("map::at() - value not found");
	}
	return it->second;
}


template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::mapped_type & 
map<Key, T, Comp, Alloc>::operator[](const Key &key) {
	
	iterator it = find(key);
	if (it != end()) {
		return it->second;
	}

	pair<iterator, bool> ins = insert(ft::make_pair(key, mapped_type()));
	return ins.first->second;
}


// Iterators
template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::iterator
map<Key, T, Comp, Alloc>::end(void) {
	return _tree.end();
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::iterator
map<Key, T, Comp, Alloc>::begin(void) {
	return _tree.begin();
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::reverse_iterator
map<Key, T, Comp, Alloc>::rend(void) {
	return _tree.rend();
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::reverse_iterator
map<Key, T, Comp, Alloc>::rbegin(void) {
	return _tree.rbegin();
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::const_iterator
map<Key, T, Comp, Alloc>::end(void) const {
	return _tree.end();
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::const_iterator
map<Key, T, Comp, Alloc>::begin(void) const {
	return _tree.begin();
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::const_reverse_iterator
map<Key, T, Comp, Alloc>::rend(void) const {
	return _tree.rend();
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::const_reverse_iterator
map<Key, T, Comp, Alloc>::rbegin(void) const {
	return _tree.rbegin();
}


// Capacity
template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::size_type
map<Key, T, Comp, Alloc>::size(void) const {
	return _tree.size();
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::size_type
map<Key, T, Comp, Alloc>::max_size(void) const { 
	return _tree.max_size(); 
}

template <typename Key, typename T, typename Comp, typename Alloc>
bool
map<Key, T, Comp, Alloc>::empty(void) const {
	return _tree.empty();
}

        
// Lookup 
template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::size_type
map<Key, T, Comp, Alloc>::count(const Key &key) const {
	return _tree.count(ft::make_pair(key, mapped_type()));
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::iterator
map<Key, T, Comp, Alloc>::find(const Key &key) {
	return _tree.find(ft::make_pair(key, mapped_type()));
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::const_iterator
map<Key, T, Comp, Alloc>::find(const Key &key) const {
	return _tree.find(ft::make_pair(key, mapped_type()));
}

template <typename Key, typename T, typename Comp, typename Alloc>	
pair<typename map<Key, T, Comp, Alloc>::iterator, typename map<Key, T, Comp, Alloc>::iterator>
map<Key, T, Comp, Alloc>::equal_range(const Key &key) {
	return _tree.equal_range(ft::make_pair(key, mapped_type()));
}

template <typename Key, typename T, typename Comp, typename Alloc>	
pair<typename map<Key, T, Comp, Alloc>::const_iterator, typename map<Key, T, Comp, Alloc>::const_iterator>
map<Key, T, Comp, Alloc>::equal_range(const Key &key) const {
	return _tree.equal_range(ft::make_pair(key, mapped_type()));
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::iterator
map<Key, T, Comp, Alloc>::lower_bound(const Key &key) {
	return _tree.lower_bound(ft::make_pair(key, mapped_type()));
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::const_iterator
map<Key, T, Comp, Alloc>::lower_bound(const Key &key) const {
	return _tree.lower_bound(ft::make_pair(key, mapped_type()));
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::iterator
map<Key, T, Comp, Alloc>::upper_bound(const Key &key) {
	return _tree.upper_bound(ft::make_pair(key, mapped_type()));
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::const_iterator
map<Key, T, Comp, Alloc>::upper_bound(const Key &key) const {
	return _tree.upper_bound(ft::make_pair(key, mapped_type()));
}

		
// Observers
template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::key_compare 
map<Key, T, Comp, Alloc>::key_comp() const {
	return key_compare();
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::value_compare 
map<Key, T, Comp, Alloc>::value_comp() const {
	return value_compare(key_comp());
}
        

// Modifiers
template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::iterator
map<Key, T, Comp, Alloc>::insert(iterator hint, const value_type &val) {	
	return _tree.insert(hint.base(), val);
}

template <typename Key, typename T, typename Comp, typename Alloc>	
pair<typename map<Key, T, Comp, Alloc>::iterator, bool>
map<Key, T, Comp, Alloc>::insert(const value_type &value) {
	return _tree.insert(value);
}

template <typename Key, typename T, typename Comp, typename Alloc>	
template <class InputIt>
void
map<Key, T, Comp, Alloc>::insert(InputIt first, InputIt last) {
	_tree.insert(first, last);
}

template <typename Key, typename T, typename Comp, typename Alloc>	
void
map<Key, T, Comp, Alloc>::erase(iterator position) {
	_tree.erase(position.base());
}

template <typename Key, typename T, typename Comp, typename Alloc>	
void
map<Key, T, Comp, Alloc>::erase(iterator first, iterator last) {
	_tree.erase(first.base(), last.base());
}

template <typename Key, typename T, typename Comp, typename Alloc>	
typename map<Key, T, Comp, Alloc>::size_type
erase(const Key &key) {
	return _tree.erase(ft::make_pair(key, mapped_type()));
}

template <typename Key, typename T, typename Comp, typename Alloc>	
void
map<Key, T, Comp, Alloc>::swap(map &other) {
	if (this != &other) {
		_tree.swap(other._tree);
	}
}

template <typename Key, typename T, typename Comp, typename Alloc>	
void
map<Key, T, Comp, Alloc>::clear(void) {
	_tree.clear();
}


// Non-member function overloads
template<typename Key, typename T, typename Comp, typename Alloc>
inline bool
operator==(const map<Key, T, Comp, Alloc> &lhs, const map<Key, T, Comp, Alloc> &rhs) {
	return lhs._tree == rhs._tree;
}

template<typename Key, typename T, typename Comp, typename Alloc>
inline bool
operator<(const map<Key, T, Comp, Alloc> &lhs, const map<Key, T, Comp, Alloc> &rhs) {
	return lhs._tree < rhs._tree;
}

template<typename Key, typename T, typename Comp, typename Alloc>
inline bool
operator!=(const map<Key, T, Comp, Alloc> &lhs, const map<Key, T, Comp, Alloc> &rhs) {
	return !(lhs == rhs);
}

template<typename Key, typename T, typename Comp, typename Alloc>
inline bool
operator>(const map<Key, T, Comp, Alloc> &lhs, const map<Key, T, Comp, Alloc> &rhs) { 
	return rhs < lhs;
}

template<typename Key, typename T, typename Comp, typename Alloc>
inline bool
operator<=(const map<Key, T, Comp, Alloc> &lhs, const map<Key, T, Comp, Alloc> &rhs) {
	return !(rhs < lhs);
}

template<typename Key, typename T, typename Comp, typename Alloc>
inline bool
operator>=(const map<Key, T, Comp, Alloc> &lhs,  const map<Key, T, Comp, Alloc> &rhs) {
	return !(lhs < rhs);
}

template<typename Key, typename T, typename Comp, typename Alloc>
inline void
swap(map<Key, T, Comp, Alloc> &lhs, map<Key, T, Comp, Alloc> &rhs) {
	lhs.swap(rhs);
}


}