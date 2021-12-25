#pragma once

#include <memory>

#include "pair.hpp"
#include "normal_iterator.hpp"
#include "reverse_iterator.hpp"

#include "utils.hpp"

namespace ft {

	template < typename Key, typename T, 
	typename Compare = ft::less<Key>, 
	typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map {
	
	public:
		typedef Key 										key_type;
		typedef T 											mapped_type;
		typedef ft::pair<const Key, T>						value_type;
        typedef size_t                                   	size_type;
        typedef typename iterator::difference_type     		difference_type;
		typedef Compare										key_compare;
        typedef Alloc                               		allocator_type;

        typedef typename Alloc::pointer         pointer;
        typedef typename Alloc::const_pointer   const_pointer;
        typedef typename Alloc::reference       value_type&;
        typedef typename Alloc::const_reference const value_type&;

        typedef ft::normal_iterator<value_type>           iterator;
        typedef ft::normal_iterator<const value_type>     const_iterator;
        typedef ft::reverse_iterator<iterator>            reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>      const_reverse_iterator;

		// Member classes
		class value_compare : ft::binary_function<value_type, value_type, bool> {
			
			// Protected member objects
			protected:
				Compare _c;
			
			// Member functions
			value_compare( Compare c ) : _c(c) {}
			
			public:
			bool operator()( const value_type& lhs, const value_type& rhs ) const {
				return _c(lhs.first, rhs.first);
			}
		};

	private:
        allocator_type     _allocator;
        pointer            _start;
        pointer            _finish;
        pointer            _storage_end;

    public:
		map() {}

		explicit
		map( const Compare& comp, const Alloc& alloc = Alloc() );

		template <class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc() );

		map( const map& other ) {}

		map& operator=( const map& other ) {}
        
		~map() {}

		// Allocator
        allocator_type get_allocator() const {
            return allocator_type(_allocator);
        }

		// Element access
		T& at( const Key& key ) {}

		const T& at( const Key& key ) const {}

		T& operator[]( const Key& key ) {}

        // Iterators
        iterator end() {
            return iterator(_finish);
        }
        
        iterator begin() {
            return iterator(_start);
        }
        
        reverse_iterator rend() {
            return reverse_iterator(begin());
        }
        
        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }
        
        const_iterator end() const {
            return _finish;
        }
        
        const_iterator begin() const {
            return _start;
        }
        
        const_reverse_iterator rend() const {
            return reverse_iterator(begin());
        }
        
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }


        // Capacity
        size_type size() const {
            return size_type(_finish - _start);
        }

        size_type max_size() const { 
            return size_type(_allocator.max_size()); 
        }

        size_type capacity() const {
            return size_type(_storage_end - _start);
        }

        bool empty() const {
            return begin() == end();
        }

        // Element access
        void range_check(size_type n) const {
        
            if (n >= size()) {
				char msg[100] = {0};
				sprintf(msg, "map::range_check: %zu >= %zu", n, size());
                throw std::out_of_range(msg);
            }
        }
        
		// 
		size_type count( const Key& key ) const {}

		iterator find( const Key& key ) {}
		const_iterator find( const Key& key ) const {}

		ft::pair<iterator,iterator> equal_range( const Key& key ) {}
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {}

		iterator lower_bound( const Key& key ) {}
		const_iterator lower_bound( const Key& key ) const {}

		iterator upper_bound( const Key& key ) {}
		const_iterator upper_bound( const Key& key ) const {}

		// Observers
		key_compare key_comp() const {}
		ft::map::value_compare value_comp() const {}
        // Modifiers
      
        iterator insert(iterator position, const value_type& val) {
			size_type i = ft::distance(begin(), position);
			insert(position, 1, val);
			return begin() + i;
        }

		std::pair<iterator, bool> insert( const value_type& value );

		template< class InputIt >
		void insert( InputIt first, InputIt last );

        void erase(iterator position) {
			return erase(position, position + 1);
        }
        
        void erase(iterator first, iterator last) {

        }

        void swap(map &other) {

            if (this != &other) {
               
            }
        }

        void clear() {
          
        }
    };

    // Non-member function overloads
	template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator==( const map<Key, T, Compare, Alloc>& lhs,
	    		const map<Key, T, Compare, Alloc>& rhs)
    { return lhs._M_t == rhs._M_t; }

	template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator<( const map<Key, T, Compare, Alloc>& lhs,
	      	   const map<Key, T, Compare, Alloc>& rhs)
    { return lhs._M_t < rhs._M_t; }

	template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator!=( const map<Key, T, Compare, Alloc>& lhs,
	       		const map<Key, T, Compare, Alloc>& rhs)
    { return !(lhs == rhs); }

	template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator>( const map<Key, T, Compare, Alloc>& lhs,
	      	   const map<Key, T, Compare, Alloc>& rhs)
    { return rhs < lhs; }

	template<typename Key, typename T, typename Compare, typename Alloc>
    inline bool
    operator<=( const map<Key, T, Compare, Alloc>& lhs,
	       		const map<Key, T, Compare, Alloc>& rhs)
    { return !(rhs < lhs); }

	template<typename Key, typename T, typename Compare, typename Alloc>
	inline bool
    operator>=( const map<Key, T, Compare, Alloc>& lhs,
	      		const map<Key, T, Compare, Alloc>& rhs)
    { return !(lhs < rhs); }

	template<typename Key, typename T, typename Compare, typename Alloc>
    inline void
    swap( map<Key, T, Compare, Alloc>& lhs,
		  map<Key, T, Compare, Alloc>& rhs )
    { lhs.swap(rhs); }
}