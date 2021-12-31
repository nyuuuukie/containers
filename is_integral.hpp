#pragma once

#include "type_traits.hpp"
#include <uchar.h>

namespace ft {

	template<typename T, T __v>
	struct integral_constant
	{
		static const T	                    value = __v;
		typedef T                           value_type;
		typedef integral_constant<T, __v>   type;
		//const operator value_type() const { return value; }
	};

	typedef integral_constant<bool, true>     integral_true_type;
	typedef integral_constant<bool, false>    integral_false_type;

	template<typename>
	struct __is_integral__
	: public integral_false_type { };

	template<>
	struct __is_integral__<bool>
	: public integral_true_type { };

	template<>
	struct __is_integral__<char>
	: public integral_true_type { };

	template<>
	struct __is_integral__<signed char>
	: public integral_true_type { };

	template<>
	struct __is_integral__<unsigned char>
	: public integral_true_type { };

	template<>
	struct __is_integral__<char16_t>
	: public integral_true_type { };

	template<>
	struct __is_integral__<char32_t>
	: public integral_true_type { };

	template<>
	struct __is_integral__<short>
	: public integral_true_type { };

	template<>
	struct __is_integral__<unsigned short>
	: public integral_true_type { };

	template<>
	struct __is_integral__<int>
	: public integral_true_type { };

	template<>
	struct __is_integral__<unsigned int>
	: public integral_true_type { };

	template<>
	struct __is_integral__<long>
	: public integral_true_type { };

	template<>
	struct __is_integral__<unsigned long>
	: public integral_true_type { };

	template<>
	struct __is_integral__<long long>
	: public integral_true_type { };

	template<>
	struct __is_integral__<unsigned long long>
	: public integral_true_type { };

	template<typename T>
	struct is_integral
	: public __is_integral__<typename remove_cv<T>::type>::type
	{ };

};