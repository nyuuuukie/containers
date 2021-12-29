#pragma once

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
			insert(begin(), first, last);
		}
        
        vector(const vector& x) 
        : _allocator(x.get_allocator()), _start(), _finish(), _storage_end() {
			insert(begin(), x.first(), x.last());
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
            range_check();
            return (*this)[n];
        }
        
        const_reference at (size_type n) const {
            range_check();
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
            insert(end(), val);
        }

        void pop_back() {
			erase(end() - 1);
        }

        iterator insert(iterator position, const value_type& val) {
			size_type i = ft::distance(begin(), position);
			insert(position, 1, val);
			return begin() + i;
        }

		//void insert(iterator position, size_type n, const value_type& val) {
		//	if (n == 0)
		//		return ;

		//	if (size() + n < capacity()) {
		//		iterator shiftedEnd = end() + n - 1;
		//		iterator lastInserted = position + n;

		//		for (; n != 0; n--)
		//		{
        //        	_allocator.construct(shiftedEnd.base(), *lastInserted);
        //        	_allocator.destroy(lastInserted.base());
		//			_allocator.construct(lastInserted.base(), val);

		//			lastInserted--;
		//			shiftedEnd--;
		//			_finish++;
		//		}
		//	}
		//	else if (size() + n >= capacity()) {

		//		size_type newCapacity = nextPowerOf2(size() + n + 1);
		//		std::cout << newCapacity << std::endl;
		//		pointer start = _allocator.allocate(newCapacity);
		//		pointer finish = start;

		//		iterator it = begin();
		//		for (; it != position; it++, finish++) {
		//			std::cout << 1 << std::endl;
		//			_allocator.construct(finish, *it);
		//			_allocator.destroy(it.base());
		//		}
			
		//		for (; n != 0; n--, finish++) {
		//			std::cout << 2 << std::endl;
		//			_allocator.construct(finish, val);
		//		}

		//		for (; it != end(); it++, finish++) {
		//			std::cout << 3 << std::endl;
		//			_allocator.construct(finish, *it);
		//			_allocator.destroy(it.base());
		//		}

		//		if (_start != 0)
		//			_allocator.deallocate(_start, capacity());

		//		_start = start;
        //        _finish = finish;
        //        _storage_end = start + newCapacity;
		//	}
    	//}
        
		void insert(iterator position, size_type n, const value_type& val) {
			if (n == 0)
				return ;
			else if (size() + n < capacity())
				 __insert_impl(position, n, val);
			else
				__realloc_insert_impl(position, n, val);
		}

		void __insert_impl(iterator position, size_type n, const value_type& val)
		{
			iterator shiftedEnd = end() + n - 1;
			iterator lastInserted = position + n;

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
			size_type newCapacity = nextPowerOf2(size() + n + 1);
			std::cout << newCapacity << std::endl;
			pointer start = _allocator.allocate(newCapacity);
			pointer finish = start;

			iterator it = begin();
			for (; it != position; it++, finish++) {
				std::cout << 1 << std::endl;
				_allocator.construct(finish, *it);
				_allocator.destroy(it.base());
			}
		
			for (; n != 0; n--, finish++) {
				std::cout << 2 << std::endl;
				_allocator.construct(finish, val);
			}

			for (; it != end(); it++, finish++) {
				std::cout << 3 << std::endl;
				_allocator.construct(finish, *it);
				_allocator.destroy(it.base());
			}

			if (_start != 0)
				_allocator.deallocate(_start, capacity());

			_start = start;
            _finish = finish;
            _storage_end = start + newCapacity;
		}

        //template <class InputIterator>
        //void insert(iterator position, InputIterator first, InputIterator last) {
		//	//size_type n = last - first;
		//	size_type n = static_cast<size_type>(ft::distance(first, last));
		//	if (n == 0)
		//		return ;
		//	if (size() + n < capacity()) {
		//		iterator newEnd = end() + n - 1;
		//		//iterator beg = first;
		//		iterator lastInserted = position + n;
		//		for (; first != last; first++)
		//		{
        //        	_allocator.construct(newEnd.base(), *lastInserted);
        //        	_allocator.destroy(lastInserted.base());
		//			_allocator.construct(lastInserted.base(), *first);
		//			lastInserted--;
		//			newEnd--;
		//		}
		//	}
		//	if (size() + n >= capacity()) {
		//		size_type newCapacity = nextPowerOf2(size() + n + 1);
		//		pointer start = _allocator.allocate(newCapacity);
		//		pointer finish = start;
		//		iterator it = begin();
		//		for (; it != position; it++, finish++) {
		//			_allocator.construct(finish, *it);
		//			_allocator.destroy(it.base());
		//		}
		//		for (; first != last; first++, finish++)
		//			_allocator.construct(finish, *first);
		//		for (; it != end(); it++, finish++) {
		//			_allocator.construct(finish, *it);
		//			_allocator.destroy(it.base());
		//		}
		//		_allocator.deallocate(_start, capacity());
		//		_start = start;
        //        _finish = start + size() + n + 1;
        //        _storage_end = start + size() + n + 1;
		//	}
        //}

		template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last) {
			
			size_type n = static_cast<size_type>(ft::distance(first, last));

			if (n == 0)
				return ;
			else if (size() + n < capacity())
				 __insert_impl(position, first, last);
			else
				__realloc_insert_impl(position, first, last);
		}

		template <class InputIterator>
		void __insert_impl(
			iterator position, 
	    	typename enable_if<are_same<is_integral<InputIterator>, false_type>::value, InputIterator>::type first, 
			typename enable_if<are_same<is_integral<InputIterator>, false_type>::value, InputIterator>::type last)
		{	
			iterator newEnd = end() + n - 1;
			iterator lastInserted = position + n;

			for (; first != last; first++)
			{
            	_allocator.construct(newEnd.base(), *lastInserted);
            	_allocator.destroy(lastInserted.base());
				_allocator.construct(lastInserted.base(), *first);

				lastInserted--;
				newEnd--;
			}
		}

		template <class InputIterator>
		void __realloc_insert_impl(
			iterator position, 
	    	typename enable_if<are_same<is_integral<InputIterator>, false_type>::value, InputIterator>::type first, 
			typename enable_if<are_same<is_integral<InputIterator>, false_type>::value, InputIterator>::type last)
		{
			size_type newCapacity = nextPowerOf2(size() + n + 1);
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

			_allocator.deallocate(_start, capacity());

			_start = start;
            _finish = start + size() + n + 1;
            _storage_end = start + size() + n + 1;
		}

        iterator erase(iterator position) {
			return erase(position, position + 1);
        }
        
        iterator erase(iterator first, iterator last) {

			size_type n = ft::distance(first, last);

			pointer f = first->_current;
			for (; f != last; f++)
			{
				pointer proto = f + n;
				_allocator.destroy(f);
				if (proto < _finish)
					_allocator.construct(f, *(proto));
			}
			_finish -= n;
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