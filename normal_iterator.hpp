#pragma once

#include "iterator_traits.hpp"
#include "iterator_functions.hpp"

namespace ft {

    template <class T, class Container>
    class normal_iterator
    {
        typedef iterator_traits<T> _traits_type;

        protected:
            T _current;

        public:
            typedef typename _traits_type::pointer             pointer;
            typedef typename _traits_type::reference           reference;
            typedef typename _traits_type::value_type          value_type;
            typedef typename _traits_type::difference_type     difference_type;
            typedef random_access_iterator_tag 				   iterator_category;

        normal_iterator() 
        : _current(T()) { }

		explicit
		normal_iterator(const T& ptr)
        : _current(ptr) { }

        template<typename Iter>
        normal_iterator( const normal_iterator<Iter, 
		typename enable_if< are_same<Iter, typename Container::pointer>::value, Container>::type> &iter)
        : _current(iter.base()) { }


        reference operator*() const {
            return *_current;
        }

        pointer operator->() const {
            return _current;
        }

        normal_iterator& operator++() {
            ++_current;
            return *this;
        }

        normal_iterator operator++(int) {
            return normal_iterator(_current++);
        }

        // Bidirectional iterator requirements
        normal_iterator& operator--() {
		    --_current;
            return *this;
        }

        normal_iterator operator--(int) {
            return normal_iterator(_current--);
	    }


        // Random access iterator requirements
        reference operator[](difference_type n) const {
            return _current[n];
        }

        normal_iterator& operator+=(difference_type n) {
            _current += n;
            return *this;
        }

        normal_iterator operator+(difference_type n) const {
            return normal_iterator(_current + n);
        }

        normal_iterator& operator-=(difference_type n) {
            _current -= n;
            return *this;
        }

        normal_iterator operator-(difference_type n) const {
            return normal_iterator(_current - n);
        }

        const T base() const {
            return _current;
        }
    };


    // Non-member comparison overloads    
    template <typename IteratorL, class IteratorR, class Container>
    bool operator==( const normal_iterator<IteratorL, Container>& lhs,
                     const normal_iterator<IteratorR, Container>& rhs ) {
        return lhs.base() == rhs.base();
    }

    template <typename IteratorL, typename IteratorR, class Container>
    bool operator!=( const normal_iterator<IteratorL, Container>& lhs,
                     const normal_iterator<IteratorR, Container>& rhs ) {
        return lhs.base() != rhs.base();
    }

    template <typename IteratorL, typename IteratorR, class Container>
    bool operator<( const normal_iterator<IteratorL, Container>& lhs,
                    const normal_iterator<IteratorR, Container>& rhs ) {
        return lhs.base() < rhs.base();
    }

    template <typename IteratorL, typename IteratorR, class Container>
    bool operator<=( const normal_iterator<IteratorL, Container>& lhs,
                     const normal_iterator<IteratorR, Container>& rhs ) {
        return lhs.base() <= rhs.base();
    }

    template <typename IteratorL, typename IteratorR, class Container>
    bool operator>( const normal_iterator<IteratorL, Container>& lhs,
                    const normal_iterator<IteratorR, Container>& rhs ) {
        return lhs.base() > rhs.base();
    }

    template <typename IteratorL, typename IteratorR, class Container>
    bool operator>=( const normal_iterator<IteratorL, Container>& lhs,
                     const normal_iterator<IteratorR, Container>& rhs ) {
        return lhs.base() >= rhs.base();
    }

	template<typename IteratorL, typename IteratorR, typename Container>
    inline typename normal_iterator<IteratorL, Container>::difference_type
    operator-( const normal_iterator<IteratorL, Container>& lhs,
	     	   const normal_iterator<IteratorR, Container>& rhs)
    { 
		return lhs.base() - rhs.base(); }


    template <class Iterator, class Container>
    bool operator==( const normal_iterator<Iterator, Container>& lhs,
                     const normal_iterator<Iterator, Container>& rhs ) {
        return lhs.base() == rhs.base();
    }

    template <class Iterator, class Container>
    bool operator!=( const normal_iterator<Iterator, Container>& lhs,
                     const normal_iterator<Iterator, Container>& rhs ) {
        return lhs.base() != rhs.base();
    }

    template <class Iterator, class Container>
    bool operator<( const normal_iterator<Iterator, Container>& lhs,
                    const normal_iterator<Iterator, Container>& rhs ) {
        return lhs.base() < rhs.base();
    }

    template <class Iterator, class Container>
    bool operator>( const normal_iterator<Iterator, Container>& lhs,
                    const normal_iterator<Iterator, Container>& rhs ) {
        return lhs.base() > rhs.base();
    }

    template <class Iterator, class Container>
    bool operator<=( const normal_iterator<Iterator, Container>& lhs,
                     const normal_iterator<Iterator, Container>& rhs ) {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator, class Container>
    bool operator>=( const normal_iterator<Iterator, Container>& lhs,
                     const normal_iterator<Iterator, Container>& rhs ) {
        return lhs.base() >= rhs.base();
    }

    template <class Iterator, class Container>
    inline typename normal_iterator<Iterator, Container>::difference_type
    operator-( const normal_iterator<Iterator, Container>& lhs, 
	           const normal_iterator<Iterator, Container>& rhs) {
        return lhs.base() - rhs.base();
    }

    template <class Iterator, class Container>
    inline normal_iterator<Iterator, Container>
    operator+( typename normal_iterator<Iterator, Container>::difference_type n,
               const normal_iterator<Iterator, Container>& i ) {
        return normal_iterator<Iterator, Container>(i.base() + n);
    }

}