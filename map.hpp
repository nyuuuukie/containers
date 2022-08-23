#pragma once

#include <memory>

#include "pair.hpp"
#include "reverse_iterator.hpp"

#include "rb_tree.hpp"

namespace ft {

	template < typename Key, typename T, 
	typename Comp = ft::less<Key>, 
	typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
	
	public:
		typedef Key 									key_type;
		typedef T 										mapped_type;
		typedef ft::pair<const Key, T>					value_type;
        typedef size_t                                  size_type;
        typedef typename iterator::difference_type     	difference_type;
		typedef Comp									key_compare;
        typedef Alloc                               	allocator_type;

        typedef typename Alloc::pointer        			pointer;
        typedef typename Alloc::const_pointer  			const_pointer;
        typedef typename Alloc::reference      			reference;
        typedef typename Alloc::const_reference			const_reference;

		typedef rb_tree<value_type, key_compare, allocator_type> tree_type;

        typedef typename tree_type::iterator       		    iterator;
        typedef typename tree_type::const_iterator 		    const_iterator;
        typedef typename tree_type::reverse_iterator        reverse_iterator;
        typedef typename tree_type::const_reverse_iterator  const_reverse_iterator;

		// Member classes
		class value_compare : ft::binary_function<value_type, value_type, bool> {
			
			// Member functions
			public:
				bool operator()( const value_type& lhs, const value_type& rhs ) const {
					return _c(lhs.first, rhs.first);
				}

			// Protected member objects
			protected:
				Comp _c;

				value_compare( Comp c ) : _c(c) {}			
		};

	private:
        tree_type _tree;

    public:
		map() {}

		explicit
		map( const Comp& comp, const Alloc& alloc = Alloc() );

		template <class InputIt>
		map(InputIt first, InputIt last, const Comp& comp = Comp(), const Alloc& alloc = Alloc()) {
			_tree.insert(first, last);
		}

		map( const map& other ) : _tree(other._tree) {}

		map& operator=( const map& other ) {
			if (this != &other) {
				_tree = other._tree;
			}
			return *this;
		}
        
		~map() {}


		// Allocator
        allocator_type get_allocator() const {
            return allocator_type(_tree.get_allocator());
        }


        // Element access
		T& at( const Key& key ) {
			iterator it = find(key);
			
			if (it == end()) {
	            throw std::out_of_range("map::at() - value not found");
			}
			return it->second;
		}

		const T& at( const Key& key ) const {
			const_iterator it = find(key);
			
			if (it == end()) {
            	throw std::out_of_range("map::at() - value not found");
			}
			return it->second;
		}

		T& operator[]( const Key& key ) {
			iterator it = find(key);
			
			pair<iterator, bool> ins;
			if (it == end()) {
				ins = insert(make_pair(key_type(key), mapped_type()));
			}
			return ins->first->second;
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
		size_type count( const Key& key ) const {
			return _tree.find(key) != _tree.end();
		}

		iterator find( const Key& key ) {
			return _tree.find(key);
		}

		const_iterator find( const Key& key ) const {
			return _tree.find(key);
		}

		pair<iterator, iterator> equal_range( const Key& key ) {
			return _tree.equal_range(key);
		}

		pair<const_iterator, const_iterator> equal_range( const Key& key ) const {
			return _tree.equal_range(key);
		}

		iterator lower_bound( const Key& key ) {
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound( const Key& key ) const {
			return _tree.lower_bound(key);
		}

		iterator upper_bound( const Key& key ) {
			return _tree.upper_bound(key);
		}

		const_iterator upper_bound( const Key& key ) const {
			return _tree.upper_bound(key);
		}

		
		// Observers
		key_compare key_comp() const {
			return _tree.key_comp();
		}

		value_compare value_comp() const {
			return value_compare(key_comp());
		}
        

		// Modifiers
        iterator insert(iterator position, const value_type& val) {
			size_type i = ft::distance(begin(), position);
			insert(position, 1, val);
			return begin() + i;
        }

		pair<iterator, bool> insert( const value_type& value ) {
			return _tree.insert(value);
		}

		template <class InputIt>
		void insert( InputIt first, InputIt last ) {
			_tree.insert(first, last);
		}

        void erase(iterator position) {
			erase(position, position + 1);
        }
        
        void erase(iterator first, iterator last) {
			_tree.erase(first, last);
        }

        void swap(map &other) {
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
    operator==( const map<Key, T, Comp, Alloc>& lhs,
	    		const map<Key, T, Comp, Alloc>& rhs)
    { return lhs._tree == rhs._tree; }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline bool
    operator<( const map<Key, T, Comp, Alloc>& lhs,
	      	   const map<Key, T, Comp, Alloc>& rhs)
    { return lhs._tree < rhs._tree; }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline bool
    operator!=( const map<Key, T, Comp, Alloc>& lhs,
	       		const map<Key, T, Comp, Alloc>& rhs)
    { return !(lhs == rhs); }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline bool
    operator>( const map<Key, T, Comp, Alloc>& lhs,
	      	   const map<Key, T, Comp, Alloc>& rhs)
    { return rhs < lhs; }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline bool
    operator<=( const map<Key, T, Comp, Alloc>& lhs,
	       		const map<Key, T, Comp, Alloc>& rhs)
    { return !(rhs < lhs); }

	template<typename Key, typename T, typename Comp, typename Alloc>
	inline bool
    operator>=( const map<Key, T, Comp, Alloc>& lhs,
	      		const map<Key, T, Comp, Alloc>& rhs)
    { return !(lhs < rhs); }

	template<typename Key, typename T, typename Comp, typename Alloc>
    inline void
    swap( map<Key, T, Comp, Alloc>& lhs,
		  map<Key, T, Comp, Alloc>& rhs )
    { lhs.swap(rhs); }
}