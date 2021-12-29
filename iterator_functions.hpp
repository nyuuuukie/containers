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
      	bool operator()(const T& lhs, const T& rhs) const { return lhs < rhs; }
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
		operator()(Pair& __x) const { return __x.first; }

		const typename Pair::first_type&
		operator()(const Pair& __x) const { return __x.first; }
	};


	template<class Iterator>
	typename std::iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last)
	{
		if ( are_same<typename ft::iterator_traits<Iterator>::iterator_category, ft::random_access_iterator_tag>::value )
		    return last - first;
		else {
		    typename iterator_traits<Iterator>::difference_type n;
			for (n = 0; first != last; first++, n++);
			return (n);
		}
	}

	//template <class InputIterator>
	//typename iterator_traits<InputIterator>::difference_type
	//distance(InputIterator first, InputIterator last) {
	//	typename iterator_traits<InputIterator>::difference_type n;
	//	for (n = 0; first != last; first++, n++);
	//	return (n);
	//}

};