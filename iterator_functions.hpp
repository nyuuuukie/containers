#pragma once

#include "iterator_traits.hpp"

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
    struct less : public binary_function<T, T, bool>
    {
      	bool operator()(const T &lhs, const T &rhs) const {
			return lhs < rhs;
		}
    };

	
	template<typename T>
    struct identity : public unary_function<T, T>
    {
		T& operator()(T& x) const { return x; }
		const T& operator()(const T& x) const { return x; }
    };

	
	template<typename Pair>
    struct select1st : public unary_function<Pair, typename Pair::first_type>
    {
		typename Pair::first_type& 
		operator()(Pair& x) const { return x.first; }

		const typename Pair::first_type&
		operator()(const Pair& x) const { return x.first; }
	};


	template<typename Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator&) { 
		return typename iterator_traits<Iterator>::iterator_category(); 
	}

	template<class It>
	typename ft::iterator_traits<It>::difference_type 
	_distance(It first, It last, ft::input_iterator_tag)
	{
	    typename ft::iterator_traits<It>::difference_type result = 0;
	    while (first != last) {
	        ++first;
	        ++result;
	    }
	    return result;
	}
	 
	template<class It>
	typename ft::iterator_traits<It>::difference_type 
	_distance(It first, It last, ft::random_access_iterator_tag)
	{
	    return last - first;
	}

	template<class It>
	typename ft::iterator_traits<It>::difference_type 
	distance(It first, It last)
	{
	    return _distance(first, last, ft::iterator_category(first));
	}


};