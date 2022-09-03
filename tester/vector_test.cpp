#include <iostream>

#ifdef _CONTAINER_TESTER_STD
namespace ft = std;
# include <vector>
#else
# include "vector.hpp"
#endif

typedef int key_t;

template <typename T>
void
print_vector_content(ft::vector<T> &vec) {
	std::cout << " content  : [";
	typename ft::vector<T>::const_iterator it = vec.begin();
	typename ft::vector<T>::const_iterator end = vec.end();
	for (; it != end; ++it) {
		std::cout << " ";
		std::cout << *it;
	}
	std::cout << " ]" << std::endl;
}

template <typename T>
void
print_vector(ft::vector<T>& vec) {
	std::cout << " empty    : " << vec.empty() << std::endl;
	std::cout << " size     : " << vec.size() << std::endl;
	std::cout << " max_size : " << vec.max_size() << std::endl;
	print_vector_content(vec);
}

void
vector_test(void) {

	std::cout << "---------- vector " << std::endl;

	const key_t   arr[] = { 21, 42, 84, 168, 336, 672 };
	const key_t r_arr[] = { 672, 336, 168, 84, 42, 21 };
	const std::size_t size_arr = sizeof(arr) / sizeof(arr[0]);
	const std::size_t size_r_arr = sizeof(r_arr) / sizeof(r_arr[0]);

	const std::size_t emptysize = 0;
	const std::size_t nonemptysize_small = 3;
	const std::size_t nonemptysize_large = 21;
	const key_t default_value = 42;

	std::cout << "----- Constructors:" << std::endl;
	{
		std::cout << " default constructor:" << std::endl;
		ft::vector<key_t>	vec;
		print_vector(vec);
		std::cout << std::endl;
	}

	{
		std::cout << " constructor(n, val),  (size 0):" << std::endl;
		ft::vector<key_t> vec(emptysize);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " constructor(n, val), (default val):" << std::endl;
		ft::vector<key_t> vec(nonemptysize_large);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " constructor(n, val):" << std::endl;
		ft::vector<key_t> vec(nonemptysize_large, default_value);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " constructor(first, last):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " copy constructor:" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(vec1);
		print_vector(vec2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator= (empty array):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2 = vec1;
		print_vector(vec2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator= (non-empty array):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(nonemptysize_large);
		vec2 = vec1;
		print_vector(vec2);
		std::cout << std::endl;
	}
	
	std::cout << "----- Iterators:" << std::endl;
	{
		std::cout << " begin() -> end()" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [";
		ft::vector<key_t>::iterator it = vec.begin();
		ft::vector<key_t>::iterator end = vec.end();
		for (; it != end; ++it) {
			std::cout << " ";
			std::cout << *it;
		}
		std::cout << " ]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " begin() const -> end() const" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [";
		ft::vector<key_t>::const_iterator	it = vec.begin();
		ft::vector<key_t>::const_iterator	end = vec.end();
		for (; it != end; ++it) {
			std::cout << " ";
			std::cout << *it;
		}
		std::cout << " ]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " rbegin() -> rend()" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [";
		ft::vector<key_t>::reverse_iterator it = vec.rbegin();
		ft::vector<key_t>::reverse_iterator end = vec.rend();
		for (; it != end; ++it) {
			std::cout << " ";
			std::cout << *it;
		}
		std::cout << " ]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " rbegin() const -> rend() const" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [";
		ft::vector<key_t>::const_reverse_iterator	it = vec.rbegin();
		ft::vector<key_t>::const_reverse_iterator	end = vec.rend();
		for (; it != end; ++it) {
			std::cout << " ";
			std::cout << *it;
		}
		std::cout << " ]" << std::endl;
		std::cout << std::endl;
	}

	std::cout << "----- Capacity:" << std::endl;
	{
		std::cout << " size:" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " max_size:" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " resize (expand):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.resize(nonemptysize_large);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " resize (narrow):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.resize(nonemptysize_small);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " capacity:" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " empty (true):" << std::endl;
		ft::vector<key_t> vec(emptysize);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " empty (false):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " reserve (expand):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.reserve(21);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " reserve (narrow):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.reserve(2);
		print_vector(vec);
		std::cout << std::endl;
	}

	std::cout << "----- Element access:" << std::endl;
	{
		std::cout << " operator[] :" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content:  [ ";
		for (size_t i = 0; i < vec.size(); ++i) {
			std::cout << " ";
			std::cout << vec[i];
		}
		std::cout << " ]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator[] const:" << std::endl;
		const ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content:  [";
		for (size_t i = 0; i < vec.size(); ++i) {
			std::cout << " ";
			std::cout << vec[i];
		}
		std::cout << "]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " at:" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [ ";
		for (size_t i = 0; i < vec.size(); ++i) {
			std::cout << " ";
			std::cout << vec.at(i);
		}
		std::cout << "]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " at const:" << std::endl;
		const ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [ ";
		for (size_t i = 0; i < vec.size(); ++i)
		{
			std::cout << " ";
			std::cout << vec.at(i);
		}
		std::cout << "]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " front:" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [ " << vec.front() << " ]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " front const:" << std::endl;
		const ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [ " << vec.front() << " ]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " back:" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [ " << vec.back() << " ]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " back const:" << std::endl;
		const ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " content: [ " << vec.back() << " ]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " data:" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		key_t *data = vec.data();
		std::cout << " content: [ " << *data << " ]" << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " data const:" << std::endl;
		const ft::vector<key_t> vec(arr, arr + size_arr);
		const key_t*		data = vec.data();
		std::cout << " content: [ " << *data << " ]" << std::endl;
		std::cout << std::endl;
	}


	std::cout << "----- Modifiers:" << std::endl;
	{
		std::cout << " assign(first, last) (narrow):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.assign(arr, arr + 3);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " assign(first, last) (expand):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr - 1);
		vec.assign(arr, arr + size_arr);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " assign(n, val) (narrow):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.assign(nonemptysize_small, default_value);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " assign(n, val) (expand):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.assign(nonemptysize_large, default_value);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " push_back (empty):" << std::endl;
		ft::vector<key_t> vec(emptysize);
		vec.push_back(default_value);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " push_back (non-empty):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.push_back(default_value);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " pop_back:" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.pop_back();
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " insert(pos, val):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.insert(vec.begin() + 2, default_value);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " insert(pos, n, val):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.insert(vec.begin() + 2, nonemptysize_small, default_value);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " insert(pos, first, last):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.insert(vec.begin() + 2, arr, arr + size_arr);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " erase(pos):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.erase(vec.begin() + 2);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " erase(first, last):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.erase(vec.begin() + 2, vec.end() - 1);
		print_vector(vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " swap:" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		print_vector_content(vec1);
		std::cout << std::endl;
		print_vector_content(vec2);
		vec1.swap(vec2);
		print_vector_content(vec1);
		print_vector_content(vec2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " clear:" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		vec.clear();
		print_vector(vec);
		std::cout << std::endl;
	}


	std::cout << "----- Non-member function overloads:" << std::endl;
	{
		std::cout << " operator== (true):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " v == v: " << (vec == vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator== (false):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		std::cout << " v1 == v2: " << (vec1 == vec2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (false):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " v != v: " << (vec != vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (true):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		std::cout << " v1 != v2:  " << (vec1 != vec2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (false):" << std::endl;
		ft::vector<key_t> vec(arr, arr + size_arr);
		std::cout << " v < v: " << (vec < vec);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (true):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		std::cout << " v1 < v2: " << (vec1 < vec2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator<= (false):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		std::cout << " v2 <= v1: " << (vec2 <= vec1);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator<= (true):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		std::cout << " v1 <= v2: " << (vec1 <= vec2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (true):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		std::cout << " v2 > v1: " << (vec2 > vec1);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (false):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		std::cout << " v1 > v2: " << (vec1 > vec2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator>= (true):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		std::cout << " v2 >= v1: " << (vec2 >= vec1);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator>= (false):" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		std::cout << " v1 >= v2:  " << (vec1 >= vec2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " swap:" << std::endl;
		ft::vector<key_t> vec1(arr, arr + size_arr);
		ft::vector<key_t> vec2(r_arr, r_arr + size_r_arr);
		print_vector_content(vec1);
		std::cout << std::endl;
		print_vector_content(vec2);
		ft::swap(vec1, vec2);
		print_vector_content(vec1);
		print_vector_content(vec2);
	}
}