#pragma once 

namespace ft {

	struct true_type { };
  	struct false_type { };

	template<bool, typename>
    struct enable_if { };

  	template<typename T>
    struct enable_if<true, T> { 
		typedef T type;
	};

 	
	// are_same
	template<typename, typename>
    struct are_same {
		enum { value = 0 };
		typedef false_type type;
    };

	template<typename T>
    struct are_same<T, T> {
		enum { value = 1 };
		typedef true_type type;
    };

	template<typename>
	struct is_const
	: public false_type { };

	template<typename T>
	struct is_const<T const>
	: public true_type { };

	template<typename>
	struct is_volatile
	: public false_type { };

	template<typename T>
	struct is_volatile<T volatile>
	: public true_type { };

	template<typename T>
	struct remove_reference {
		typedef T type;
	};

	template<typename T>
	struct remove_reference<T&> {
		typedef T type;
	};

	template<typename T>
	struct remove_const {
		typedef T type;
	};

	template<typename T>
	struct remove_const<T const> { 
		typedef T type;
	};

	template<typename T>
	struct remove_volatile { 
		typedef T type; 
	};

	template<typename T>
	struct remove_volatile<T volatile> {
		typedef T type;
	};

	template<typename T>
	struct remove_cv {
		typedef typename
		remove_const<typename remove_volatile<T>::type>::type  type;
	};

};