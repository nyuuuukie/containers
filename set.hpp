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

    public:
		set() {}

		explicit
		set(const Comp &comp, const Alloc &alloc = Alloc());

		template <class InputIt>
		set(InputIt first, InputIt last, const Comp &comp = Comp(), const Alloc &alloc = Alloc()) {
			_tree.insert(first, last);
		}

		set(const set &other) : _tree(other._tree) {}

		set &operator=(const set &other) {
			if (this != &other) {
				_tree = other._tree;
			}
			return *this;
		}
        
		~set() {}


		// Allocator
        allocator_type get_allocator() const {
            return allocator_type(_tree.get_allocator());
        }


        // Iterators
        iterator end() {
            return _tree.end();
        }
        
        iterator begin() {
            return _tree.begin();
        }
        
        reverse_iterator rend() {
            return _tree.rend();
        }
        
        reverse_iterator rbegin() {
            return _tree.rbegin();
        }
        
        const_iterator end() const {
            return _tree.end();
        }
        
        const_iterator begin() const {
            return _tree.begin();
        }
        
        const_reverse_iterator rend() const {
            return _tree.rend();
        }
        
        const_reverse_iterator rbegin() const {
            return _tree.rbegin();
        }


        // Capacity
        size_type size() const {
            return _tree.size();
        }

        size_type max_size() const { 
            return _tree.max_size(); 
        }

        bool empty() const {
            return _tree.empty();
        }

        
		// Lookup 
		size_type count(const Key &key) const {
			return _tree.find(key) != _tree.end();
		}

		iterator find(const Key &key) {
			return _tree.find(key);
		}

		const_iterator find(const Key &key) const {
			return _tree.find(key);
		}

		pair<iterator, iterator> equal_range(const Key &key) {
			return _tree.equal_range(key);
		}

		pair<const_iterator, const_iterator> equal_range(const Key &key) const {
			return _tree.equal_range(key);
		}

		iterator lower_bound(const Key &key) {
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound(const Key &key) const {
			return _tree.lower_bound(key);
		}

		iterator upper_bound(const Key &key) {
			return _tree.upper_bound(key);
		}

		const_iterator upper_bound(const Key &key) const {
			return _tree.upper_bound(key);
		}

		
		// Observers
		key_compare key_comp() const {
			return key_compare();
		}

		value_compare value_comp() const {
			return value_compare(key_comp());
		}
        

		// Modifiers
        iterator insert(iterator position, const value_type &val) {
			size_type i = ft::distance(begin(), position);
			insert(position, 1, val);
			return begin() + i;
        }

		pair<iterator, bool> insert(const value_type &value) {
			iterator it = _tree.insert(value);
			return ft::make_pair(it, true);
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last) {
			_tree.insert(first, last);
		}

        void erase(iterator position) {
			erase(position, position + 1);
        }
        
        void erase(iterator first, iterator last) {
			_tree.erase(first, last);
        }

		size_type erase(const Key &key) {
			_tree.erase(key);
		}

        void swap(set &other) {
            if (this != &other) {
               _tree.swap(other._tree);
            }
        }

        void clear() {
			_tree.clear();
        }
    };

    // Non-member function overloads
	template<typename Key, typename T, typename Comp, typename Alloc>
    inline bool
    operator==( const set<Key, Comp, Alloc> &lhs,
	    		const set<Key, Comp, Alloc> &rhs)
    { return lhs._tree == rhs._tree; }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline bool
    operator<( const set<Key, Comp, Alloc> &lhs,
	      	   const set<Key, Comp, Alloc> &rhs)
    { return lhs._tree < rhs._tree; }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline bool
    operator!=( const set<Key, Comp, Alloc> &lhs,
	       		const set<Key, Comp, Alloc> &rhs)
    { return !(lhs == rhs); }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline bool
    operator>( const set<Key, Comp, Alloc> &lhs,
	      	   const set<Key, Comp, Alloc> &rhs)
    { return rhs < lhs; }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline bool
    operator<=( const set<Key, Comp, Alloc> &lhs,
	       		const set<Key, Comp, Alloc> &rhs)
    { return !(rhs < lhs); }

	template<typename Key, typename T, typename Comp, typename Alloc>
	inline bool
    operator>=( const set<Key, Comp, Alloc> &lhs,
	      		const set<Key, Comp, Alloc> &rhs)
    { return !(lhs < rhs); }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline void
    swap( set<Key, Comp, Alloc> &lhs,
		  set<Key, Comp, Alloc> &rhs) { 
		lhs.swap(rhs); 
	}
}