#pragma once

#include <cmath>
#include <memory>
#include <iostream>

#include "is_integral.hpp"
#include "normal_iterator.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"

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
    explicit vector(const allocator_type &alloc = allocator_type());
    explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());

    template <class InputIt>
    vector(InputIt first, InputIt last, const allocator_type &alloc = allocator_type());

    vector(const vector &other);
    vector &operator=(const vector &other);
    
    ~vector(void);


    iterator begin(void);
    iterator end(void);
    reverse_iterator rbegin(void);
    reverse_iterator rend(void);
    const_iterator begin(void) const;
    const_iterator end(void) const;
    const_reverse_iterator rbegin(void) const;
    const_reverse_iterator rend(void) const;


    size_type size(void) const;
    size_type max_size(void) const;
    size_type capacity(void) const;
    bool empty(void) const;
    void resize(size_type n, value_type val = value_type());
    void reserve(size_type n);


    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    reference at(size_type n);
    const_reference at(size_type n) const;
    reference front(void);
    const_reference front(void) const;
    reference back(void);
    const_reference back(void) const;
    

    template <class InputIt>
    void assign(InputIt first, InputIt last);
    void assign(size_type n, const value_type &val);

    void push_back(const value_type &val);
    void pop_back(void);

    template <typename InputIt>
    void insert(iterator position, InputIt first, InputIt last);
    void insert(iterator position, size_type n, const value_type &val);
    iterator insert(iterator position, const value_type& val);

    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);

    void swap(vector &rhs);
    void clear(void);


    allocator_type get_allocator(void) const;


private:
    void _range_check(size_type n) const;
    void _move(pointer src, pointer dst, size_type n);

    u_int64_t _next_capacity(u_int64_t capacity);

    template <typename InputIt>
    void _insert_impl(iterator pos, size_type n, InputIt first, InputIt last);

    template <typename InputIt>
    void _realloc_insert_impl(iterator pos, size_type n, InputIt first, InputIt last);

    void _insert_impl(iterator pos, size_type n, const value_type &val);
    void _realloc_insert_impl(iterator pos, size_type n, const value_type &val);

    template <typename InputIt>
    void _insert(iterator position, InputIt first, InputIt last, integral_false_type);

    template <typename InputIt>
    void _assign(InputIt first, InputIt last, integral_false_type);

};

template <typename T, typename Alloc>
vector<T, Alloc>::vector(const allocator_type &alloc)
: _allocator(alloc), _start(NULL), _finish(NULL), _storage_end(NULL) {}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n, const value_type &val, const allocator_type &alloc) 
: _allocator(alloc), _start(NULL), _finish(NULL), _storage_end(NULL) {
    insert(begin(), n, val);
}
        
template <typename T, typename Alloc>
template <class InputIt>
vector<T, Alloc>::vector(InputIt first, InputIt last, const allocator_type& alloc)
: _allocator(alloc), _start(NULL), _finish(NULL), _storage_end(NULL) {
    typedef typename is_integral<InputIt>::type check_integral;

    __insert(begin(), first, last, check_integral());
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(const vector &other)
: _allocator(other.get_allocator()), _start(NULL), _finish(NULL), _storage_end(NULL) {
    insert(begin(), other.begin(), other.end());
}

template <typename T, typename Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector &other) {
    
    if (this != &other) {
        clear();
        _allocator = other.get_allocator();
        _start = NULL;
        _finish = NULL;
        _storage_end = NULL;

        insert(begin(), other.begin(), other.end());
    }
    return *this;
}

template <typename T, typename Alloc>
vector<T, Alloc>::~vector(void) {
    if (_start != NULL) {
        clear();
        _allocator.deallocate(_start, capacity());
    }
}


// Iterators
template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::end(void) {
    return iterator(_finish);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::begin(void) {
    return iterator(_start);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rend(void) {
    return reverse_iterator(begin());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rbegin(void) {
    return reverse_iterator(--end());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::end(void) const {
    return const_iterator(_finish);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::begin(void) const {
    return const_iterator(_start);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rend(void) const {
    return reverse_iterator(begin());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rbegin(void) const {
    return const_reverse_iterator(end());
}


// Capacity
template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::size(void) const {
    return size_type(_finish - _start);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::capacity(void) const {
    return size_type(_storage_end - _start);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::max_size(void) const { 
    return size_type(_allocator.max_size()); 
}

template <typename T, typename Alloc>
bool
vector<T, Alloc>::empty(void) const {
    return (size() == 0);
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::resize(size_type n, value_type val) {

    if (n == size()) {
        return ;
    } else if (n > size()) {
        insert(end(), n - size(), val);
    } else {
        for (pointer pos = _start + n; pos != _finish; pos++) {
            _allocator.destroy(pos);
        }
        _finish = _start + n; // start + n + 1 maybe ?
    }
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::reserve(size_type n) {

    if (n > capacity()) {

        pointer m_new = _allocator.allocate(n);
        pointer src = _start;
        pointer dst = m_new;
        for (; src != _finish; src++, dst++) {
            _allocator.construct(dst, *src);
            _allocator.destroy(src);
        } 
        _allocator.deallocate(_start, capacity());

        _start = m_new;
        _finish = m_new + size();
        _storage_end = m_new + n;
    }
}


// Element access
template <typename T, typename Alloc>
void
vector<T, Alloc>::_range_check(size_type n) const {

    if (n >= size()) {
        char msg[100] = {0};
        sprintf(msg, "vector::range_check: %zu >= %zu", n, size());
        throw std::out_of_range(msg);
    }
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::operator[](size_type n) {
    return _start[n];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::operator[](size_type n) const {
    return _start[n];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::at(size_type n) {
    _range_check(n);
    return (*this)[n];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::at(size_type n) const {
    _range_check(n);
    return (*this)[n];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::front(void) {
    return *begin();
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::front(void) const {
    return *begin();
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::back(void) {
    return *(end() - 1);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::back(void) const {
    return *(end() - 1);
}


// Modifiers

template <typename T, typename Alloc>
template <class InputIterator>
void
vector<T, Alloc>::assign(InputIterator first, InputIterator last) {
    typedef typename is_integral<InputIterator>::type check_integral;

    _assign(first, last, check_integral());
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::assign(size_type n, const value_type& val) {
    if (n >= capacity()) {
        vector tmp(n, val, get_allocator());
        swap(tmp);
    } else {
        clear();
        insert(begin(), n, val);
    }
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::push_back(const value_type &val) {
    insert(end(), size_type(1), val);
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::pop_back(void) {

    if (size() > 0) {
        erase(end() - 1);
    }
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::insert(iterator position, size_type n, const value_type &val) {

    if (n == 0) {
        return ;
    } else if (size() + n < capacity()) {
        _insert_impl(position, n, val);
    } else {
        _realloc_insert_impl(position, n, val);
    }
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::insert(iterator position, const value_type& val) {

    size_type i = ft::distance(begin(), position);
    insert(position, 1, val);
    return begin() + i;
}

template <typename T, typename Alloc>
template <typename InputIt>
void
vector<T, Alloc>::insert(iterator position, InputIt first, InputIt last) {
    typedef typename is_integral<InputIt>::type check_integral;
    
    _insert(position, first, last, check_integral());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::erase(iterator position) {
    return erase(position, position + 1);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::erase(iterator first, iterator last) {

    size_type offset = static_cast<size_type>(ft::distance(begin(), first));
    size_type n = static_cast<size_type>(ft::distance(first, last));
    
    for (iterator it = first; it != last; ++it) {
        _allocator.destroy(it.base());
    }
    
    // Move trailing elements if there are
    if (last != end()) {
        _move(last.base(), first.base(), n);
    }

    _finish = _finish - n;
    return first; // Not sure
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::swap(vector &rhs) {

    if (this != &rhs) {
        allocator_type tmp_alloc = _allocator;
        pointer tmp_start = _start;
        pointer tmp_finish = _finish;
        pointer tmp_storage_end = _storage_end;

        _allocator = rhs._allocator;
        _start = rhs._start;
        _finish = rhs._finish;
        _storage_end = rhs._storage_end;

        rhs._allocator = tmp_alloc;
        rhs._start = tmp_start;
        rhs._finish = tmp_finish;
        rhs._storage_end = tmp_storage_end;
    }
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::clear(void) {

    for (pointer ptr = _start; ptr != _finish; ptr++) {
        _allocator.destroy(ptr);
    }
    _finish = _start;
}


// Allocator
template <typename T, typename Alloc>
typename vector<T, Alloc>::allocator_type
vector<T, Alloc>::get_allocator(void) const {
    return allocator_type(_allocator);
}


// Implementation
template <typename T, typename Alloc>
void
vector<T, Alloc>::_move(pointer src, pointer dst, size_type n) {
    while (n != 0) {
        _allocator.construct(dst, *src);
        _allocator.destroy(src);
        src++;
        dst++;
        n--;
    }
}

template <typename T, typename Alloc>
inline u_int64_t
vector<T, Alloc>::_next_capacity(u_int64_t capacity) {
    return static_cast<u_int64_t>(1U << static_cast<u_int64_t>(log2(capacity) + 1));
}

template <typename T, typename Alloc>
template <typename InputIt>
void
vector<T, Alloc>::_assign(InputIt first, InputIt last, integral_false_type) {
    size_type n = ft::distance(first, last);

    if (n >= capacity()) {
        vector tmp(first, last, get_allocator());
        swap(tmp);
    } else {
        clear();
        insert(begin(), first, last);
    }
}

template <typename T, typename Alloc>
template <typename InputIt>
void
vector<T, Alloc>::_insert(iterator position, InputIt first, InputIt last, integral_false_type) {
    size_type n = ft::distance(first, last);

    if (n == 0) {
        return ;
    } else if (size() + n < capacity()) {
        _insert_impl(position, n, first, last);
    } else {
        _realloc_insert_impl(position, n, first, last);
    }
}

template <typename T, typename Alloc>
template <typename InputIt>
void
vector<T, Alloc>::_insert_impl(iterator position, size_type n, InputIt first, InputIt last) {	
    iterator dst = end() + n;
    iterator src = position + n - 1;

    for (; first != last; first++) {
        _allocator.construct(dst.base(), *src);
        _allocator.destroy(src.base());
        _allocator.construct(src.base(), *first);

        src--;
        dst--;
        _finish++;
    }
}

template <typename T, typename Alloc>
template <typename InputIt>
void
vector<T, Alloc>::_realloc_insert_impl(iterator position, size_type n, InputIt first, InputIt last) {

    size_type newCapacity = _next_capacity(size());
    pointer start = _allocator.allocate(newCapacity);
    pointer finish = start;

    iterator it = begin();
    for (; it != position; it++, finish++) {
        _allocator.construct(finish, *it);
        _allocator.destroy(it.base());
    }

    for (; first != last; first++, finish++) {
        _allocator.construct(finish, *first);
    }

    for (; it != end(); it++, finish++) {
        _allocator.construct(finish, *it);
        _allocator.destroy(it.base());
    }

    if (_start != 0) {
        _allocator.deallocate(_start, capacity());
    }

    _start = start;
    _finish = finish;
    _storage_end = start + newCapacity;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_insert_impl(iterator position, size_type n, const value_type& val) {

    iterator dst = end() + n;
    iterator src = position + n - 1;

    for (; n != 0; n--) {
        _allocator.construct(dst.base(), *src);
        _allocator.destroy(src.base());
        _allocator.construct(src.base(), val);

        src--;
        dst--;
        _finish++;
    }
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_realloc_insert_impl(iterator position, size_type n, const value_type& val) {

    size_type newCapacity = _next_capacity(size());
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
        

// Non-member function overloads
template <typename T, typename Alloc>
inline bool
operator==(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {

    if (a.size() != b.size()) {
        return false;
    }

    typename vector<T, Alloc>::const_iterator beg_a = a.begin();
    typename vector<T, Alloc>::const_iterator beg_b = b.begin();
    typename vector<T, Alloc>::const_iterator end_a = a.end();

    for ( ;beg_a != end_a; beg_a++, beg_b++) {
        if (!(*beg_a == *beg_b)) {
            return false;
        }
    }

    return true;
}

template <typename T, typename Alloc>
inline bool
operator!=(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {
    return !(a == b);
}

template < typename T, typename Alloc >
inline bool
operator<(const vector<T, Alloc> &a, const vector<T, Alloc> &b) {
    return (ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()));
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

};
