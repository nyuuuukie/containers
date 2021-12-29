#pragma once

#include "type_traits.hpp"
#include <uchar.h>

namespace ft {

	template<typename>
	struct __is_integral__
	: public false_type { };

	template<>
	struct __is_integral__<bool>
	: public true_type { };

	template<>
	struct __is_integral__<char>
	: public true_type { };

	template<>
	struct __is_integral__<signed char>
	: public true_type { };

	template<>
	struct __is_integral__<unsigned char>
	: public true_type { };

	template<>
	struct __is_integral__<char16_t>
	: public true_type { };

	template<>
	struct __is_integral__<char32_t>
	: public true_type { };

	template<>
	struct __is_integral__<short>
	: public true_type { };

	template<>
	struct __is_integral__<unsigned short>
	: public true_type { };

	template<>
	struct __is_integral__<int>
	: public true_type { };

	template<>
	struct __is_integral__<unsigned int>
	: public true_type { };

	template<>
	struct __is_integral__<long>
	: public true_type { };

	template<>
	struct __is_integral__<unsigned long>
	: public true_type { };

	template<>
	struct __is_integral__<long long>
	: public true_type { };

	template<>
	struct __is_integral__<unsigned long long>
	: public true_type { };

	template<typename T>
	struct is_integral
	: public __is_integral__<typename remove_cv<T>::type>::type
	{ };

};