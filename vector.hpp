#pragma once
#include <memory>

#include "iterator.hpp"

namespace ft {

	template < typename T, typename Alloc = std::allocator<T> >
	class vector {

        typedef T											value_type;
		typedef size_t										size_type;
        typedef Alloc										allocator_type;
        typedef ptrdiff_t									difference_type;

        typedef typename Alloc::pointer						pointer;
        typedef typename Alloc::const_pointer				const_pointer;
        typedef typename Alloc::reference					reference;
        typedef typename Alloc::const_reference				const_reference;

		typedef ft::normal_iterator<pointer, vector>		iterator;
        typedef ft::normal_iterator<const_pointer, vector>	const_iterator;
        typedef ft::reverse_iterator<iterator>				reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	private:
		allocator_type	_allocator;
		pointer			_start;
		pointer			_finish;
		pointer			_storage_end;

	public:

		explicit 
		vector(const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _start(), _finish(), _storage_end() {}
		
		explicit 
		vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) 
		: _allocator(alloc), _start(), _finish(), _storage_end() {
			// copy data
		}
		
		template <class InputIterator>
        vector(InputIterator first, InputIterator last,
                 const allocator_type& alloc = allocator_type())
		: _allocator(alloc), _start(), _finish(), _storage_end() {
			// copy data
		}
		
		vector(const vector& x) 
		: _alloc(x.get_allocator()), _start(), _finish(), _storage_end() {
			// copy data
		}

		vector &operator=(const vector &x) {
			if (this != &x) {
				clear();
				//copy data
			}
			return *this;
		}

		~vector() {
			clear();
			_allocator.deallocate(_start, capacity());
		}

		// Iterators
		iterator end() {
			return _finish; 
		}
		
		iterator begin() {
			return _start;
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
			return size_type(_alloc.max_size()); 
		}

		size_type capacity() const {
            return size_type(_storage_end - _start);
        }

	 	bool empty() const {
            return begin() == end();
        }

		void resize (size_type n, value_type val = value_type()) {

			if (n > size()) {
				insert(end(), n - size(), val);
			}
			else if (n < size()) {
				
				for (pointer pos = _start + n; pos != _finish; pos++)
				{
					_allocator.destroy(pos);
				}
				_finish = _start + n;
			}
		}

		void reserve (size_type n) {

			if (n > capacity()) {
				pointer m_new = _allocator.allocate(n);

				for (pointer p1 = _start, p2 = m_new; p1 != _finish; p1++, p2++)
				{
					_allocator.construct(p2, *p1);
					_allocator.destroy(p1);
				}
				
				_allocator.deallocate(_start, capacity());

				_start = m_new;
				_finish = m_new + size();
				_storage_end = m_new + n;
			}
		}


		// Element access
		void range_check(size_type n) const {
		
			if (n >= size()) {
				std::string msg = "vector::range_check: " + n + " >= " + size();
				throw std::out_of_range(msg.c_str());
			}
		}
		
		reference operator[](size_type n) {
            return *(_start + n);
        }

        const_reference operator[](size_type n) const {
            return *(_start + n);
        }
	    
		reference at (size_type n) {
			range_check();
			return (*this)[n];
		}
		
		const_reference at (size_type n) const {
			range_check();
			return (*this)[n];
		}

        reference front()
        {
            return* begin();
        }

        const_reference front() const
        {
            return* begin();
        }

        reference back()
        {
            return *(end() - 1);
        }

        const_reference back() const
        {
            return *(end() - 1);
        }

        value_type* data()
        {
			return empty() ? 0 : _start;
        }

        const value_type* data() const
        {
			return empty() ? 0 : _start;
        }


		// Modifiers
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last) {

		}
		
		void assign(size_type n, const value_type& val) {
			if (n > capacity()) {
				vector tmp(n, val, get_allocator());
			  	this->swap(tmp);
			}
			else if (n > size()) {
				
			}
		    else
				_M_erase_at_end(std::fill_n(this->_M_impl._M_start, n, val));
		}

		// Improve?
		void push_back(const value_type& val) {
			if (_finish == _storage_end)
			{
				size_type reqCapacity = capacity() * 2;
				reserve(reqCapacity == 0 ? 2 : reqCapacity);
			}
			_alloc.construct(_finish++, val);
		}

		void pop_back() {
			_allocator.destroy(--_finish);
		}

		iterator insert (iterator position, const value_type& val) {

		}
    	
		void insert (iterator position, size_type n, const value_type& val) {

		}
		
		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last) {

		}

		iterator erase (iterator position) {

		}
		
		iterator erase (iterator first, iterator last) {

		}

		void swap(vector &rhs) {

			if (this != &rhs) {
				pointer __start = _start;
                pointer __finish = _finish;
                pointer __storage_end = _storage_end;

				_start = rhs._start;
				_finish = rhs._finish;
				_storage_end = rhs._storage_end;

				rhs._start = __start;
				rhs._finish = __finish;
				rhs._storage_end = __storage_end;
			}
		}

		void clear() {
			for (pointer ptr = _start; ptr != _finish; ptr++)
			{
				_allocator.destroy(ptr);
			}
			_finish = _start;
		}

		// Allocator
		allocator_type get_allocator() const {
			return allocator_type(_allocator);
		}
	};

	// Non-member function overloads
	template <typename T, typename Alloc>
	inline bool
	operator==(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {

		if (a.size() != b.size()
			return false;
		
		vector<T, Alloc>::const_iterator itA = a.begin();
		vector<T, Alloc>::const_iterator itB = b.begin();
		vector<T, Alloc>::const_iterator endA = a.end();

		for (; itA != endA; itA++, itB++)
			if (!(*itA == *itB))
				return false;

		return true;
	}
	
	template < typename T, typename Alloc >
	inline bool
	operator!=(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {
		return !(a == b);
	}

	template < typename T, typename Alloc >
	inline bool
	operator<(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {

		vector<T, Alloc>::const_iterator itA = a.begin();
		vector<T, Alloc>::const_iterator itB = b.begin();
		vector<T, Alloc>::const_iterator endA = a.end();
		vector<T, Alloc>::const_iterator endB = b.end();
		
		for (; itA != endA && itB != endB; itA++, itB++) {
			if (*itA != *itB)
				return *itA < *itB;
		}
		return itB != endB;

	}

	template < typename T, typename Alloc >
	inline bool
	operator<=(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {
		return !(a < b);
	}

	template < typename T, typename Alloc >
	inline bool
	operator>(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {
		return b < a;
	}

	template < typename T, typename Alloc >
	inline bool
	operator>=(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {
		return !(b < a);
	}

	template < typename T, typename Alloc>
    inline void
    swap(vector<T, Alloc> &a, vector<T, Alloc> &b) {
        a.swap(b);
	}
}