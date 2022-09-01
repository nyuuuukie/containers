#pragma once

#include <memory>

#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "set_iterator.hpp"
#include "rbt.hpp"

namespace ft {

template < typename Key, typename Comp = ft::less<Key>, 
		   typename Alloc = std::allocator<Key> >
class set {
	
	public:
		typedef Key 									key_type;
		typedef Key										value_type;
        typedef size_t                                  size_type;
		typedef Comp									key_compare;
		typedef Comp									value_compare;

        typedef Alloc                               	allocator_type;
        typedef typename Alloc::pointer        			pointer;
        typedef typename Alloc::const_pointer  			const_pointer;
        typedef typename Alloc::reference      			reference;
        typedef typename Alloc::const_reference			const_reference;

		typedef rbt<value_type, key_compare, allocator_type> tree_type;

		typedef set_iterator<typename tree_type::iterator>			    iterator;
		typedef set_const_iterator<typename tree_type::const_iterator>	const_iterator;
		typedef reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef reverse_iterator<iterator>								reverse_iterator;

        typedef typename iterator::difference_type     	difference_type;

	private:
        tree_type _tree;
		key_compare _comp;

    public:
		set(void);
		explicit set(const Comp &comp, const Alloc &alloc = Alloc());

		template <class InputIt>
		set(InputIt first, InputIt last, const Comp &comp = Comp(), const Alloc &alloc = Alloc());

		set(const set &other);
		set &operator=(const set &other);
        
		~set(void);
	
		// Allocator
        allocator_type get_allocator() const;

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
		key_compare key_comp(void) const;
		value_compare value_comp(void) const;

		// Modifiers
		template <class InputIt>
		void insert(InputIt first, InputIt last);
        iterator insert(iterator hint, const value_type &value);
		pair<iterator, bool> insert(const value_type &value);
        void erase(iterator pos);
        void erase(iterator first, iterator last);
		size_type erase(const Key &key);
        void swap(set &other);
        void clear(void);

		template <typename K, typename C, typename A>
		friend bool operator==(const set<K, C, A> &lhs, const set<K, C, A> &rhs);

		template <typename K, typename C, typename A> 
		friend bool	operator<(const set<K, C, A> &lhs, const set<K, C, A> &rhs);
    };

	template <typename Key, typename Comp, typename Alloc> 
	set<Key, Comp, Alloc>::set(void) {}
		
	template <typename Key, typename Comp, typename Alloc> 
	set<Key, Comp, Alloc>::set(const Comp &comp, const Alloc &alloc)
	: _comp(comp) {}

	template <typename Key, typename Comp, typename Alloc> 
	template <class InputIt>
	set<Key, Comp, Alloc>::set(InputIt first, InputIt last, const Comp &comp, const Alloc &alloc)
	: _comp(comp) {
		_tree.insert(first, last);
	}

	template <typename Key, typename Comp, typename Alloc> 
	set<Key, Comp, Alloc>::set(const set &other)
	: _tree(other._tree), _comp(other._comp) {}

	template <typename Key, typename Comp, typename Alloc> 
	set<Key, Comp, Alloc> &
	set<Key, Comp, Alloc>::operator=(const set &other) {
		if (this != &other) {
			_tree = other._tree;
			_comp = other._comp;
		}
		return *this;
	}
	
	template <typename Key, typename Comp, typename Alloc>
	set<Key, Comp, Alloc>::~set(void) {}


	// Allocator
	template <typename Key, typename Comp, typename Alloc>
    typename set<Key, Comp, Alloc>::allocator_type 
	set<Key, Comp, Alloc>::get_allocator(void) const {
		return allocator_type(_tree.get_allocator());
	}


	// Iterators
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::iterator
	set<Key, Comp, Alloc>::end(void) {
		return iterator(_tree.end());
	}
	
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::iterator
	set<Key, Comp, Alloc>::begin(void) {
		return iterator(_tree.begin());
	}
	
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::reverse_iterator
	set<Key, Comp, Alloc>::rend(void) {
		return reverse_iterator(iterator(_tree.end()));
	}
	
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::reverse_iterator
	set<Key, Comp, Alloc>::rbegin(void) {
		return reverse_iterator(--iterator(_tree.end()));
	}
	
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::const_iterator
	set<Key, Comp, Alloc>::end(void) const {
		return const_iterator(_tree.end());
	}
	
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::const_iterator
	set<Key, Comp, Alloc>::begin(void) const {
		return const_iterator(_tree.begin());
	}
	
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::const_reverse_iterator
	set<Key, Comp, Alloc>::rend(void) const {
		return const_reverse_iterator(const_iterator(_tree.end()));
	}
	
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::const_reverse_iterator
	set<Key, Comp, Alloc>::rbegin(void) const {
		return const_reverse_iterator(--const_iterator(_tree.end()));
	}


	// Capacity
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::size_type
	set<Key, Comp, Alloc>::size(void) const {
		return _tree.size();
	}

	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::size_type
	set<Key, Comp, Alloc>::max_size(void) const { 
		return _tree.max_size(); 
	}

	template <typename Key, typename Comp, typename Alloc>
	bool
	set<Key, Comp, Alloc>::empty(void) const {
		return _tree.empty();
	}

        
	// Lookup 
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::size_type
	set<Key, Comp, Alloc>::count(const Key &key) const {
		return _tree.find(key) != _tree.end();
	}

	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::iterator
	set<Key, Comp, Alloc>::find(const Key &key) {
		return _tree.find(key);
	}

	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::const_iterator
	set<Key, Comp, Alloc>::find(const Key &key) const {
		return _tree.find(key);
	}

	template <typename Key, typename Comp, typename Alloc>
	pair<typename set<Key, Comp, Alloc>::iterator, typename set<Key, Comp, Alloc>::iterator>
	set<Key, Comp, Alloc>::equal_range(const Key &key) {
		return _tree.equal_range(key);
	}

	template <typename Key, typename Comp, typename Alloc>
	pair<typename set<Key, Comp, Alloc>::const_iterator, typename set<Key, Comp, Alloc>::const_iterator> 
	set<Key, Comp, Alloc>::equal_range(const Key &key) const {
		return _tree.equal_range(key);
	}

	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::iterator
	set<Key, Comp, Alloc>::lower_bound(const Key &key) {
		return _tree.lower_bound(key);
	}

	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::const_iterator
	set<Key, Comp, Alloc>::lower_bound(const Key &key) const {
		return _tree.lower_bound(key);
	}

	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::iterator
	set<Key, Comp, Alloc>::upper_bound(const Key &key) {
		return _tree.upper_bound(key);
	}

	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::const_iterator
	set<Key, Comp, Alloc>::upper_bound(const Key &key) const {
		return _tree.upper_bound(key);
	}

		
	// Observers
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::key_compare
	set<Key, Comp, Alloc>::key_comp(void) const {
		return key_compare();
	}

	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::value_compare
	set<Key, Comp, Alloc>::value_comp(void) const {	
		return value_compare(key_comp());
	}
        

	// Modifiers
	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::iterator
	set<Key, Comp, Alloc>::insert(iterator hint, const value_type &val) {
		return _tree.insert(hint.base(), val);
	}

	template <typename Key, typename Comp, typename Alloc>
	pair<typename set<Key, Comp, Alloc>::iterator, bool>
	set<Key, Comp, Alloc>::insert(const value_type &value) {
		return _tree.insert(value);
	}

	template <typename Key, typename Comp, typename Alloc>
	template <class InputIt>
	void
	set<Key, Comp, Alloc>::insert(InputIt first, InputIt last) {
		_tree.insert(first, last);
	}

	template <typename Key, typename Comp, typename Alloc>
	void
	set<Key, Comp, Alloc>::erase(iterator pos) {
		_tree.erase(pos.base());
	}

	template <typename Key, typename Comp, typename Alloc>
	void
	set<Key, Comp, Alloc>::erase(iterator first, iterator last) {
		_tree.erase(first.base(), last.base());
	}

	template <typename Key, typename Comp, typename Alloc>
	typename set<Key, Comp, Alloc>::size_type
	set<Key, Comp, Alloc>::erase(const Key &key) {
		return _tree.erase(key);
	}

	template <typename Key, typename Comp, typename Alloc>
	void
	set<Key, Comp, Alloc>::swap(set &other) {
		if (this != &other) {
			_tree.swap(other._tree);
		}
	}

	template <typename Key, typename Comp, typename Alloc>
	void
	set<Key, Comp, Alloc>::clear(void) {
		_tree.clear();
	}


    // Non-member function overloads
	template <typename Key, typename Comp, typename Alloc>
    inline bool
    operator==(const set<Key, Comp, Alloc> &lhs, const set<Key, Comp, Alloc> &rhs) {
		return lhs._tree == rhs._tree;
	}

	template<typename Key, typename Comp, typename Alloc>
    inline bool
    operator<(const set<Key, Comp, Alloc> &lhs, const set<Key, Comp, Alloc> &rhs) {
		return lhs._tree < rhs._tree;
	}

	template<typename Key, typename Comp, typename Alloc>
    inline bool
    operator!=(const set<Key, Comp, Alloc> &lhs, const set<Key, Comp, Alloc> &rhs) {
		return !(lhs == rhs);
	}

	template<typename Key, typename Comp, typename Alloc>
    inline bool
    operator>(const set<Key, Comp, Alloc> &lhs, const set<Key, Comp, Alloc> &rhs) {
		return rhs < lhs;
	}

	template<typename Key, typename Comp, typename Alloc>
    inline bool
    operator<=(const set<Key, Comp, Alloc> &lhs, const set<Key, Comp, Alloc> &rhs) {
		return !(rhs < lhs);
	}

	template<typename Key, typename Comp, typename Alloc>
	inline bool
    operator>=(const set<Key, Comp, Alloc> &lhs, const set<Key, Comp, Alloc> &rhs) { 
		return !(lhs < rhs);
	}

	template<typename Key, typename Comp, typename Alloc>
    inline void
    swap(set<Key, Comp, Alloc> &lhs, set<Key, Comp, Alloc> &rhs) { 
		lhs.swap(rhs); 
	}

}