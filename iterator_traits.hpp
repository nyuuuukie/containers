#pragma once 

#include <cstddef>

namespace ft {
	
	template <typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T*, typename Reference = T&> 
    struct iterator {
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Category  iterator_category;        
    };

	struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	
	// Iterator traits
    template <class Iterator>
    struct iterator_traits {
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T>
    struct iterator_traits<T*> {
        typedef T*                             pointer;
        typedef T&                             reference;
        typedef T                              value_type;
        typedef ptrdiff_t                      difference_type;
        typedef ft::random_access_iterator_tag iterator_category;
    };

    template <class T>
    struct iterator_traits<const T*> {
        typedef const T*                       pointer;
        typedef const T&                       reference;
        typedef T                              value_type;
        typedef ptrdiff_t                      difference_type;
        typedef ft::random_access_iterator_tag iterator_category;
    };

};