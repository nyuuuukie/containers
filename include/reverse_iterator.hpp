#pragma once

#include "iterator_traits.hpp"
#include "iterator_functions.hpp"

namespace ft {

    template <typename _Iterator>
    class reverse_iterator
	: public iterator<
        typename iterator_traits<_Iterator>::iterator_category, 
        typename iterator_traits<_Iterator>::value_type,
        typename iterator_traits<_Iterator>::difference_type,
        typename iterator_traits<_Iterator>::pointer,
        typename iterator_traits<_Iterator>::reference> 
	{
        typedef iterator_traits<_Iterator>    __traits_type;

        protected:
        	_Iterator _current;

        public:
            typedef _Iterator                                    iterator_type;
            typedef typename __traits_type::pointer              pointer;
            typedef typename __traits_type::reference            reference;
            typedef typename __traits_type::value_type           value_type;
            typedef typename __traits_type::difference_type      difference_type;
            typedef typename __traits_type::iterator_category    iterator_category;

            reverse_iterator() : _current() { }

            explicit 
            reverse_iterator(iterator_type it) : _current(it) { }

            reverse_iterator(const reverse_iterator &it)
            : _current(it._current) { }

            template<class _Iter>
            reverse_iterator(const reverse_iterator<_Iter> &it)
            : _current(it.base()) { }

            iterator_type base() const { 
                return _current;
            }

            reference operator*() const {
                _Iterator tmp = _current;
                tmp--;
                return *tmp;
            }

            pointer operator->() const {
                _Iterator tmp = _current;
                tmp--;
                return *tmp;
            }

            reverse_iterator& operator++() {
                --_current;
                return *this;
            }

            reverse_iterator operator++(int) {
                reverse_iterator tmp = *this;
                --_current;
                return tmp;
            }

            reverse_iterator& operator--() {
                ++_current;
                return *this;
            }

            reverse_iterator operator--(int) {
                reverse_iterator tmp = *this;
                ++_current;
                return tmp;
            }

            reverse_iterator operator+(difference_type n) const {
                return reverse_iterator(_current - n);
            }

            reverse_iterator& operator+=(difference_type n) {
                _current -= n;
                return *this;
            }

            reverse_iterator operator-(difference_type n) const {
                return reverse_iterator(_current + n);
            }

            reverse_iterator& operator-=(difference_type n) {
                _current += n;
                return *this;
            }

            reference operator[](difference_type n) const {
                return *(*this + n);
            }

        };


    // Non-member comparison overloads    
    template <class Iterator1, class Iterator2>
    bool operator==( const reverse_iterator<Iterator1>& lhs,
                     const reverse_iterator<Iterator2>& rhs ) {
        return lhs.base() == rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator!=( const reverse_iterator<Iterator1>& lhs,
                     const reverse_iterator<Iterator2>& rhs ) {
        return lhs.base() != rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator<( const reverse_iterator<Iterator1>& lhs,
                    const reverse_iterator<Iterator2>& rhs ) {
        return lhs.base() < rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator<=( const reverse_iterator<Iterator1>& lhs,
                     const reverse_iterator<Iterator2>& rhs ) {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator>( const reverse_iterator<Iterator1>& lhs,
                    const reverse_iterator<Iterator2>& rhs ) {
        return lhs.base() > rhs.base();
    }

    template <class Iterator1, class Iterator2>
    bool operator>=( const reverse_iterator<Iterator1>& lhs,
                     const reverse_iterator<Iterator2>& rhs ) {
        return lhs.base() >= rhs.base();
    }


    template <class Iterator>
    bool operator==( const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<Iterator>& rhs ) {
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator!=( const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<Iterator>& rhs ) {
        return lhs.base() != rhs.base();
    }

    template <class Iterator>
    bool operator<( const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs ) {
        return lhs.base() < rhs.base();
    }

    template <class Iterator>
    bool operator>( const reverse_iterator<Iterator>& lhs,
                    const reverse_iterator<Iterator>& rhs ) {
        return lhs.base() > rhs.base();
    }

    template <class Iterator>
    bool operator<=( const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<Iterator>& rhs ) {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator>
    bool operator>=( const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<Iterator>& rhs ) {
        return lhs.base() >= rhs.base();
    }


	// Arithmetic
    template <class Iterator>
    inline typename reverse_iterator<Iterator>::difference_type
    operator-( const reverse_iterator<Iterator>& lhs, 
	           const reverse_iterator<Iterator>& rhs) {
        return rhs.base() - lhs.base();
    }

    template <class Iterator>
    inline reverse_iterator<Iterator>
    operator+( typename reverse_iterator<Iterator>::difference_type n,
               const reverse_iterator<Iterator>& i ) {
        return reverse_iterator<Iterator>(i.base() - n);
    }

};