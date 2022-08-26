#pragma once

#include <cmath>
#include <memory>

#include "is_integral.hpp"
#include "normal_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <typename T, typename Alloc = std::allocator<T> >
class vector {
	
	public:
        typedef typename Alloc::pointer          			pointer;
        typedef typename Alloc::const_pointer    			const_pointer;
        typedef typename Alloc::reference        			reference;
        typedef typename Alloc::const_reference  			const_reference;

        typedef ft::normal_iterator<pointer, vector>        iterator;
        typedef ft::normal_iterator<const_pointer, vector>  const_iterator;
        typedef ft::reverse_iterator<iterator>       		reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> 		const_reverse_iterator;

        typedef T                                       	value_type;
        typedef size_t                                  	size_type;
        typedef Alloc                                   	allocator_type;
        typedef typename iterator::difference_type      	difference_type;

	private:
        allocator_type     _allocator;
        pointer            _start;
        pointer            _finish;
        pointer            _storage_end;

    public:
        explicit 
        vector(const allocator_type& alloc = allocator_type())
        : _allocator(alloc), _start(), _finish(), _storage_end() {}
        
        explicit 
        vector(size_type n, const value_type& val = value_type(),
               const allocator_type& alloc = allocator_type()) 
        : _allocator(alloc), _start(), _finish(), _storage_end() {
			insert(begin(), n, val);
        }
        
        template <class InputIterator>
        vector(InputIterator first, InputIterator last,
               const allocator_type& alloc = allocator_type())
        : _allocator(alloc), _start(), _finish(), _storage_end() {
	
			typedef typename is_integral<InputIterator>::type check_integral;

			__insert(begin(), first, last, check_integral());
		}
        
        vector(const vector &other) 
        : _allocator(other.get_allocator()), _start(), _finish(), _storage_end() {
			insert(begin(), other.begin(), other.end());
        }

        vector &operator=(const vector &x) {
            if (this != &x) {
                clear();
				insert(begin(), x.first(), x.last());
            }
            return *this;
        }

        ~vector() {
			if (_start != 0) {
            	clear();
            	_allocator.deallocate(_start, capacity());
			}
        }

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
            return reverse_iterator(--end());
        }
        
        const_iterator end() const {
            return const_iterator(_finish);
        }
        
        const_iterator begin() const {
            return const_iterator(_start);
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

        void resize(size_type n, value_type val = value_type()) {

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

        void reserve(size_type n) {

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
				char msg[100] = {0};
				sprintf(msg, "vector::range_check: %zu >= %zu", n, size());
                throw std::out_of_range(msg);
            }
        }
        
        reference operator[](size_type n) {
            return *(_start + n);
        }

        const_reference operator[](size_type n) const {
            return *(_start + n);
        }
        
        reference at (size_type n) {
            range_check(n);
            return (*this)[n];
        }
        
        const_reference at (size_type n) const {
            range_check(n);
            return (*this)[n];
        }

        reference front()
        {
            return *begin();
        }

        const_reference front() const
        {
            return *begin();
        }

        reference back()
        {
            return *(end() - 1);
        }

        const_reference back() const
        {
            return *(end() - 1);
        }


        // Modifiers
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {
			typedef typename is_integral<InputIterator>::type check_integral;

			__assign(first, last, check_integral());
        }

        void assign(size_type n, const value_type& val) {
            if (n >= capacity()) {
                vector tmp(n, val, get_allocator());
                swap(tmp);
            }
            else {
				clear();
				insert(begin(), n, val);
            }
        }

        void push_back(const value_type& val) {
            insert(end(), size_type(1), val);
        }

        void pop_back() {
			if (size() > 0) {
				erase(end() - 1);
			}
        }

		void insert(iterator position, size_type n, const value_type& val) {
			if (n == 0)
				return ;
			else if (size() + n < capacity())
				__insert_impl(position, n, val);
			else
				__realloc_insert_impl(position, n, val);
		}

        iterator insert(iterator position, const value_type& val) {

			size_type i = ft::distance(begin(), position);
			insert(position, 1, val);
			return begin() + i;
        }

		template <typename InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last) {
			typedef typename is_integral<InputIterator>::type check_integral;
			
			__insert(position, first, last, check_integral());
		}

        iterator erase(iterator position) {
			return erase(position, position + 1);
        }
        
        iterator erase(iterator first, iterator last) {

			size_type n = static_cast<size_type>(ft::distance(first, last));
			
			while (first != last) {
				_allocator.destroy(first.base());
				first++;
			}			

			if (last != end()) {
				iterator newPlace = last - n;
				while (last != end()) {
					_allocator.construct(newPlace.base(), *last);
					_allocator.destroy(last.base());
					last++;
					newPlace++;
				}
			}
			_finish = _finish - n;
			return begin() + n;
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
            for (pointer ptr = _start; ptr != _finish; ptr++) {
                _allocator.destroy(ptr);
            }
            _finish = _start;
        }


        // Allocator
        allocator_type get_allocator() const {
            return allocator_type(_allocator);
        }


	private:

		//Helpers
		inline u_int64_t
		__next_capacity(u_int64_t capacity)
		{
		    return static_cast<u_int64_t>(1U << static_cast<u_int64_t>(log2(capacity) + 1));
		}

		template <typename InputIterator>
		void __assign(InputIterator first, InputIterator last, integral_false_type) {
			size_type n = ft::distance(first, last);

			if (n >= capacity()) {
				vector tmp(first, last, get_allocator());
                swap(tmp);
            }
            else {
				clear();
				insert(begin(), first, last);
            }
		}

		template <typename InputIterator>
		void __insert(iterator position, InputIterator first, InputIterator last, integral_false_type) {
			size_type n = ft::distance(first, last);

			if (n == 0)
				return ;
			else if (size() + n < capacity())
				__insert_impl(position, n, first, last);
			else
				__realloc_insert_impl(position, n, first, last);
		}

		template <typename InputIterator>
		void __insert_impl(iterator position, size_type n, InputIterator first, InputIterator last)
		{	
			iterator newEnd = end() + n;
			iterator lastInserted = position + n - 1;

			for (; first != last; first++)
			{
            	_allocator.construct(newEnd.base(), *lastInserted);
            	_allocator.destroy(lastInserted.base());
				_allocator.construct(lastInserted.base(), *first);

				lastInserted--;
				newEnd--;
				_finish++;
			}
		}

		template <typename InputIterator>
		void __realloc_insert_impl(iterator position, size_type n, InputIterator first, InputIterator last)
		{
			size_type newCapacity = __next_capacity(size());
			pointer start = _allocator.allocate(newCapacity);
			pointer finish = start;

			iterator it = begin();
			for (; it != position; it++, finish++) {
				_allocator.construct(finish, *it);
				_allocator.destroy(it.base());
			}
		
			for (; first != last; first++, finish++)
				_allocator.construct(finish, *first);

			for (; it != end(); it++, finish++) {
				_allocator.construct(finish, *it);
				_allocator.destroy(it.base());
			}

			if (_start != 0)
				_allocator.deallocate(_start, capacity());

			_start = start;
            _finish = finish;
            _storage_end = start + newCapacity;
		}

		void __insert_impl(iterator position, size_type n, const value_type& val)
		{
			iterator shiftedEnd = end() + n;
			iterator lastInserted = position + n - 1;

			for (; n != 0; n--)
			{
            	_allocator.construct(shiftedEnd.base(), *lastInserted);
            	_allocator.destroy(lastInserted.base());
				_allocator.construct(lastInserted.base(), val);

				lastInserted--;
				shiftedEnd--;
				_finish++;
			}
		}

		void __realloc_insert_impl(iterator position, size_type n, const value_type& val)
		{
			size_type newCapacity = __next_capacity(size());
			pointer start = _allocator.allocate(newCapacity);
			pointer finish = start;

			iterator it = begin();
			for (; it != position; it++, finish++) {
				_allocator.construct(finish, *it);
				_allocator.destroy(it.base());
			}
		
			for (; n != 0; n--, finish++) {
				_allocator.construct(finish, val);
			}

			for (; it != end(); it++, finish++) {
				_allocator.construct(finish, *it);
				_allocator.destroy(it.base());
			}

			if (_start != 0)
				_allocator.deallocate(_start, capacity());

			_start = start;
            _finish = finish;
            _storage_end = start + newCapacity;
		}
        
    };


    // Non-member function overloads
    template <typename T, typename Alloc>
    inline bool
    operator==(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {

        if (a.size() != b.size())
            return false;

        typename vector<T, Alloc>::const_iterator itA = a.begin();
        typename vector<T, Alloc>::const_iterator itB = b.begin();
        typename vector<T, Alloc>::const_iterator endA = a.end();

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

        typename vector<T, Alloc>::const_iterator itA = a.begin();
        typename vector<T, Alloc>::const_iterator itB = b.begin();
        typename vector<T, Alloc>::const_iterator endA = a.end();
        typename vector<T, Alloc>::const_iterator endB = b.end();
        
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