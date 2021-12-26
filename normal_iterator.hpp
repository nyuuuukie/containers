#pragma once

#include "iterator_traits.hpp"
#include "iterator_functions.hpp"

namespace ft {

	template <typename arg1, typename arg2, typename result>
    struct binary_function
    {
		typedef arg1	first_argument_type; 
		typedef arg2 	second_argument_type;
		typedef result 	result_type;
    };

	template<typename arg, typename result>
    struct unary_function
    {
		typedef arg		argument_type;   
		typedef result	result_type;  
    };

	template<typename T>
    struct identity : public unary_function<T, T>
    {
		T& operator()(T& x) const { return x; }
		const T& operator()(const T& x) const { return x; }
    };

	template<typename T>
    struct less : public binary_function<T, T, bool>
    {
      	bool operator()(const T& lhs, const T& rhs) const { return lhs < rhs; }
    };

	template<typename Pair>
    struct select1st : public unary_function<Pair, typename Pair::first_type>
    {
		typename Pair::first_type& 
		operator()(Pair& __x) const { return __x.first; }

		const typename Pair::first_type&
		operator()(const Pair& __x) const { return __x.first; }
	};

	

	

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {

		typename iterator_traits<InputIterator>::difference_type n;
		for (n = 0; first != last; first++, n++);
		return (n);
	}

	template<bool, typename>
    struct __enable_if 
    { };

  	template<typename T>
    struct __enable_if<true, T>
    { typedef T __type; };


	struct __true_type { };
  	struct __false_type { };

	template<typename, typename>
    struct __are_same
    {
      enum { __value = 0 };
      typedef __false_type __type;
    };

	template<typename T>
    struct __are_same<T, T>
    {
      enum { __value = 1 };
      typedef __true_type __type;
    };



    template <class T>
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

		//explicit
		normal_iterator(const T& iter)
        : _current(iter) { }

        //template<typename _Iter>
        //normal_iterator(const normal_iterator<_Iter, 
		//typename __enable_if<__are_same<_Iter, typename Cont::pointer>::__value, Cont>::__type> & __i> &iter)
        //: _current(iter.base()) { }

		normal_iterator(const normal_iterator &iter)
		: _current(iter._current) { }

        template<typename _Iter>
        normal_iterator(const normal_iterator<_Iter> &iter)
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
    template <typename Iterator1, class Iterator2>
    bool operator==( const normal_iterator<Iterator1>& lhs,
                    const normal_iterator<Iterator2>& rhs ) {
        return lhs.base() == rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator!=( const normal_iterator<Iterator1>& lhs,
                    const normal_iterator<Iterator2>& rhs ) {
        return lhs.base() != rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<( const normal_iterator<Iterator1>& lhs,
                    const normal_iterator<Iterator2>& rhs ) {
        return lhs.base() < rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<=( const normal_iterator<Iterator1>& lhs,
                    const normal_iterator<Iterator2>& rhs ) {
        return lhs.base() <= rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>( const normal_iterator<Iterator1>& lhs,
                    const normal_iterator<Iterator2>& rhs ) {
        return lhs.base() > rhs.base();
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>=( const normal_iterator<Iterator1>& lhs,
                    const normal_iterator<Iterator2>& rhs ) {
        return lhs.base() >= rhs.base();
    }


    template <class Iterator>
    bool operator==( const normal_iterator<Iterator>& lhs,
                     const normal_iterator<Iterator>& rhs ) {
        return lhs.base() == rhs.base();
    }

    template <class Iterator>
    bool operator!=( const normal_iterator<Iterator>& lhs,
                     const normal_iterator<Iterator>& rhs ) {
        return lhs.base() != rhs.base();
    }

    template <class Iterator>
    bool operator<( const normal_iterator<Iterator>& lhs,
                    const normal_iterator<Iterator>& rhs ) {
        return lhs.base() < rhs.base();
    }

    template <class Iterator>
    bool operator>( const normal_iterator<Iterator>& lhs,
                    const normal_iterator<Iterator>& rhs ) {
        return lhs.base() > rhs.base();
    }

    template <class Iterator>
    bool operator<=( const normal_iterator<Iterator>& lhs,
                     const normal_iterator<Iterator>& rhs ) {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator>
    bool operator>=( const normal_iterator<Iterator>& lhs,
                     const normal_iterator<Iterator>& rhs ) {
        return lhs.base() >= rhs.base();
    }

    template <class Iterator>
    inline typename normal_iterator<Iterator>::difference_type
    operator-( const normal_iterator<Iterator>& lhs, 
	           const normal_iterator<Iterator>& rhs) {
        return rhs.base() - lhs.base();
    }

    template <class Iterator>
    inline normal_iterator<Iterator>
    operator+( typename normal_iterator<Iterator>::difference_type n,
               const normal_iterator<Iterator>& i ) {
        return normal_iterator<Iterator>(i.base() + n);
    }
}