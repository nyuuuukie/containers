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
    allocator_type     _alloc;
    pointer            _beg;
    pointer            _data_end;
    pointer            _storage_end;

public:
    explicit vector(const allocator_type &alloc = allocator_type());
    explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());

    template <class InputIt>
    vector(InputIt first, InputIt last, const allocator_type &alloc = allocator_type());

    vector(const vector &other);
    vector &operator=(const vector &other);
    
    ~vector(void);

    allocator_type get_allocator(void) const;


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
    void insert(iterator pos, InputIt first, InputIt last);
    void insert(iterator pos, size_type n, const value_type &val);
    iterator insert(iterator pos, const value_type &val);

    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

    void swap(vector &rhs);
    void clear(void);

private:
    void _range_check(size_type n) const;
    void _move(pointer src, pointer dst, size_type n);

    u_int64_t _next_capacity(u_int64_t capacity);

    template <typename InputIt>
    void _noalloc_insert_impl(iterator pos, size_type n, InputIt first, InputIt last);
    template <typename InputIt>
    void _realloc_insert_impl(iterator pos, size_type n, InputIt first, InputIt last);

    void _noalloc_insert_impl(iterator pos, size_type n, const value_type &val);
    void _realloc_insert_impl(iterator pos, size_type n, const value_type &val);

    template <typename InputIt>
    void _insert(iterator pos, InputIt first, InputIt last, integral_false_type);

    template <typename InputIt>
    void _assign(InputIt first, InputIt last, integral_false_type);

};

template <typename T, typename Alloc>
vector<T, Alloc>::vector(const allocator_type &alloc)
: _alloc(alloc), _beg(NULL), _data_end(NULL), _storage_end(NULL) {}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n, const value_type &val, const allocator_type &alloc) 
: _alloc(alloc), _beg(NULL), _data_end(NULL), _storage_end(NULL) {
    insert(begin(), n, val);
}
        
template <typename T, typename Alloc>
template <class InputIt>
vector<T, Alloc>::vector(InputIt first, InputIt last, const allocator_type& alloc)
: _alloc(alloc), _beg(NULL), _data_end(NULL), _storage_end(NULL) {
    typedef typename is_integral<InputIt>::type check_integral;

    _insert(begin(), first, last, check_integral());
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(const vector &other)
: _alloc(other.get_allocator()), _beg(NULL), _data_end(NULL), _storage_end(NULL) {
    insert(begin(), other.begin(), other.end());
}

template <typename T, typename Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector &other) {
    
    if (this != &other) {
        clear();
        insert(begin(), other.begin(), other.end());
    }
    return *this;
}

template <typename T, typename Alloc>
vector<T, Alloc>::~vector(void) {

    if (_beg != NULL) {
        clear();
        _alloc.deallocate(_beg, capacity());
    }
}


// Iterators
template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::end(void) {
    return iterator(_data_end);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::begin(void) {
    return iterator(_beg);
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
    return const_iterator(_data_end);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::begin(void) const {
    return const_iterator(_beg);
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
    return size_type(_data_end - _beg);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::capacity(void) const {
    return size_type(_storage_end - _beg);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::max_size(void) const { 
    return size_type(_alloc.max_size()); 
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
        for (pointer pos = _beg + n; pos != _data_end; pos++) {
            _alloc.destroy(pos);
        }
        _data_end = _beg + n; // start + n + 1 maybe ?
    }
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::reserve(size_type n) {

    if (n > capacity()) {

        pointer new_storage = _alloc.allocate(n);

        pointer src = _beg;
        pointer dst = new_storage;
        for (; src != _data_end; src++, dst++) {
            _alloc.construct(dst, *src);
            _alloc.destroy(src);
        } 
        _alloc.deallocate(_beg, capacity());

        _beg = new_storage;
        _data_end = new_storage + size();
        _storage_end = new_storage + n;
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
    return _beg[n];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reference
vector<T, Alloc>::operator[](size_type n) const {
    return _beg[n];
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
template <class InputIt>
void
vector<T, Alloc>::assign(InputIt first, InputIt last) {
    typedef typename is_integral<InputIt>::type check_integral;

    _assign(first, last, check_integral());
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::assign(size_type n, const value_type &val) {

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
vector<T, Alloc>::insert(iterator pos, size_type n, const value_type &val) {

    if (n == 0) {
        return ;
    } else if (size() + n < capacity()) {
        _noalloc_insert_impl(pos, n, val);
    } else {
        _realloc_insert_impl(pos, n, val);
    }
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::insert(iterator pos, const value_type& val) {

    size_type i = ft::distance(begin(), pos);
    insert(pos, 1, val);
    return begin() + i;
}

template <typename T, typename Alloc>
template <typename InputIt>
void
vector<T, Alloc>::insert(iterator pos, InputIt first, InputIt last) {
    typedef typename is_integral<InputIt>::type check_integral;
    
    _insert(pos, first, last, check_integral());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::erase(iterator pos) {
    return erase(pos, pos + 1);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::erase(iterator first, iterator last) {

    size_type offset = static_cast<size_type>(ft::distance(begin(), first));
    size_type n = static_cast<size_type>(ft::distance(first, last));
    
    for (iterator it = first; it != last; ++it) {
        _alloc.destroy(it.base());
    }
    
    // Move trailing elements if there are
    if (last != end()) {
        _move(last.base(), first.base(), n);
    }

    _data_end = _data_end - n;
    return first; // Not sure
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::swap(vector &rhs) {

    if (this != &rhs) {
        allocator_type tmp_alloc = _alloc;
        pointer tmp_start = _beg;
        pointer tmp_finish = _data_end;
        pointer tmp_storage_end = _storage_end;

        _alloc = rhs._alloc;
        _beg = rhs._beg;
        _data_end = rhs._data_end;
        _storage_end = rhs._storage_end;

        rhs._alloc = tmp_alloc;
        rhs._beg = tmp_start;
        rhs._data_end = tmp_finish;
        rhs._storage_end = tmp_storage_end;
    }
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::clear(void) {

    for (pointer ptr = _beg; ptr != _data_end; ptr++) {
        _alloc.destroy(ptr);
    }
    _data_end = _beg;
}


// Allocator
template <typename T, typename Alloc>
typename vector<T, Alloc>::allocator_type
vector<T, Alloc>::get_allocator(void) const {
    return allocator_type(_alloc);
}


// Implementation
template <typename T, typename Alloc>
void
vector<T, Alloc>::_move(pointer src, pointer dst, size_type n) {
    while (n != 0) {
        _alloc.construct(dst, *src);
        _alloc.destroy(src);
        src++;
        dst++;
        n--;
    }
}

template <typename T, typename Alloc>
inline u_int64_t
vector<T, Alloc>::_next_capacity(u_int64_t capacity) {
    return (1U << static_cast<u_int64_t>(log2(capacity) + 1)) + 1;
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
vector<T, Alloc>::_insert(iterator pos, InputIt first, InputIt last, integral_false_type) {

    size_type n = ft::distance(first, last);

    if (n == 0) {
        return ;
    } else if (size() + n < capacity()) {
        _noalloc_insert_impl(pos, n, first, last);
    } else {
        _realloc_insert_impl(pos, n, first, last);
    }
}

template <typename T, typename Alloc>
template <typename InputIt>
void
vector<T, Alloc>::_noalloc_insert_impl(iterator pos, size_type n, InputIt first, InputIt last) {	
    iterator dst = end() + n;
    iterator src = pos + n - 1;

    for (; first != last; first++) {
        _alloc.construct(dst.base(), *src);
        _alloc.destroy(src.base());
        _alloc.construct(src.base(), *first);

        src--;
        dst--;
        _data_end++;
    }
}

template <typename T, typename Alloc>
template <typename InputIt>
void
vector<T, Alloc>::_realloc_insert_impl(iterator pos, size_type n, InputIt first, InputIt last) {

    size_type upd_capacity = _next_capacity(size() + n);
    pointer start = _alloc.allocate(upd_capacity);
    pointer finish = start;

    iterator it = begin();
    for (; it != pos; it++, finish++) {
        _alloc.construct(finish, *it);
        _alloc.destroy(it.base());
    }

    for (; first != last; first++, finish++) {
        _alloc.construct(finish, *first);
    }

    for (; it != end(); it++, finish++) {
        _alloc.construct(finish, *it);
        _alloc.destroy(it.base());
    }

    if (_beg != NULL) {
        _alloc.deallocate(_beg, capacity());
    }

    _beg = start;
    _data_end = finish;
    _storage_end = start + upd_capacity;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_noalloc_insert_impl(iterator pos, size_type n, const value_type &val) {

    iterator dst = end() + n;
    iterator src = pos + n - 1;

    for (; n != 0; n--) {
        _alloc.construct(dst.base(), *src);
        _alloc.destroy(src.base());
        _alloc.construct(src.base(), val);

        src--;
        dst--;
        _data_end++;
    }
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_realloc_insert_impl(iterator pos, size_type n, const value_type &val) {

    size_type upd_capacity = _next_capacity(size() + n);
    pointer start = _alloc.allocate(upd_capacity);
    pointer finish = start;

    iterator it = begin();
    for (; it != pos; it++, finish++) {
        _alloc.construct(finish, *it);
        _alloc.destroy(it.base());
    }

    for (; n != 0; n--, finish++) {
        _alloc.construct(finish, val);
    }

    for (; it != end(); it++, finish++) {
        _alloc.construct(finish, *it);
        _alloc.destroy(it.base());
    }

    if (_beg != NULL) {
        _alloc.deallocate(_beg, capacity());
    }

    _beg = start;
    _data_end = finish;
    _storage_end = start + upd_capacity;
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
