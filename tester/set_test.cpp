#include <iostream>

#ifdef _CONTAINER_TESTER_STD
	namespace ft = std;
	# include <set>
#else
	# include "set.hpp"
#endif

typedef int key_t;

template <typename It>
void
print_set_content(It first, It last) {
	std::cout << " content  : [";
	for (; first != last; ++first) {
		std::cout << " ";
		std::cout << *first;
	}
	std::cout << " ]" << std::endl;
}

template <typename T>
void
print_set(ft::set<T> &set) {
	std::cout << " empty    : " << set.empty() << std::endl;
	std::cout << " size     : " << set.size() << std::endl;
	std::cout << " max_size : " << set.max_size() << std::endl;
	print_set_content(set.begin(), set.end());
}

void
set_test(void) {

	std::cout << "---------- set:" << std::endl;

	key_t arr[] = { 21, 42, 84, 168, 336, 672 };
	const key_t arr_size = sizeof(arr) / sizeof(arr[0]);
	const key_t arr_exist_key = 168;
	const key_t arr_nonexist_key = 1024;

	key_t arr2[] = { 21, 42, 84, 336, 672 };
	const key_t arr2_size = sizeof(arr2) / sizeof(arr2[0]);
	
	key_t arr3[] = { 168, 1344, 2688 };
	const key_t arr3_size = sizeof(arr3) / sizeof(arr3[0]);
	
	const key_t comp_a = 21;
	const key_t comp_b = 42;

	std::cout << "----- Constructors:" << std::endl;
	{
		std::cout << " constructor (default):" << std::endl;
		ft::set<key_t> set;
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " constructor(first, last):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " copy constructor:" << std::endl;
		ft::set<key_t> set1(arr, arr + arr_size);
		ft::set<key_t> set2(set1);
		std::cout << std::endl;
		print_set(set1);
		print_set(set2);
		std::cout << std::endl;
	}

	{
		std::cout << " operator= :" << std::endl;
		ft::set<key_t> set1(arr, arr + arr_size);
		ft::set<key_t> set2;
		set2 = set1;
		std::cout << std::endl;
		print_set(set1);
		print_set(set2);
		std::cout << std::endl;
	}

	std::cout << "----- Iterators:" << std::endl;
	{
		std::cout << " begin() -> end()" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set_content(set.begin(), set.end());
		std::cout << std::endl;
	}
	
	{
		std::cout << " begin() const -> end() const:" << std::endl;
		const ft::set<key_t> set(arr, arr + arr_size);
		print_set_content(set.begin(), set.end());
		std::cout << std::endl;
	}
	
	{
		std::cout << " rbegin() -> rend():" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set_content(set.rbegin(), set.rend());
		std::cout << std::endl;
	}
	
	{
		std::cout << " const rbegin() -> const rend()" << std::endl;
		const ft::set<key_t> set(arr, arr + arr_size);
		print_set_content(set.rbegin(), set.rend());
		std::cout << std::endl;
	}

	std::cout << "----- Capacity:" << std::endl;
	{
		std::cout << " empty (true):" << std::endl;
		ft::set<key_t> set;
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " empty (false):" << std::endl;	
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " size:" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " max_size:" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
	}

	std::cout << "----- Modifiers:" << std::endl;
	{
		std::cout << " insert(val): " << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		print_set(set);
		std::cout << std::endl;
		set.insert(4);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " insert with hint:" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		print_set(set);
		std::cout << std::endl;
		set.insert(set.begin(), 4);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " insert(first, last):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		print_set(set);
		std::cout << std::endl;
		set.insert(arr3, arr3 + arr3_size);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " erase(pos):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		ft::set<key_t>::iterator it = set.begin();
		++it;
		++it;
		++it;
		std::cout << std::endl;
		set.erase(it);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " erase(val):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		set.erase(4);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " erase(first, last):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		ft::set<key_t>::iterator it = set.begin();
		ft::set<key_t>::iterator it2 = set.begin();
		++it;
		++it2;
		++it2;
		++it2;
		std::cout << std::endl;
		set.erase(it, it2);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " swap:" << std::endl;
		ft::set<key_t>	set(arr2, arr2 + arr2_size);
		ft::set<key_t>	set2(arr3, arr3 + arr3_size);
		print_set(set);
		std::cout << std::endl;
		print_set(set2);
		std::cout << std::endl;
		set.swap(set2);
		std::cout << std::endl;
		print_set(set);
		std::cout << std::endl;
		print_set(set2);
		std::cout << std::endl;
	}

	{
		std::cout << " clear:" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		set.clear();
		print_set(set);
		std::cout << std::endl;
	}

	std::cout << "----- Observers:" << std::endl;
	{
		std::cout << " key_comp (true):" << std::endl;
		ft::set<key_t> set;
		std::cout << " cmp(" << comp_a << ", " << comp_b << "): " << (set.key_comp()(comp_a, comp_b));
		std::cout << std::endl;
	}

	{
		std::cout << " key_comp (false):" << std::endl;
		ft::set<key_t> set;
		std::cout << " cmp(" << comp_b << ", " << comp_a << "): " << (set.key_comp()(comp_b, comp_a));
		std::cout << std::endl;
	}

	{
		std::cout << " value_comp (true):" << std::endl;
		ft::set<key_t> set;
		std::cout<< " cmp(" << comp_a << ", " << comp_b << "): " << (set.value_comp()(comp_a, comp_b));
		std::cout << std::endl;
	}

	{
		std::cout << " value_comp (false):" << std::endl;
		ft::set<key_t> set;
		std::cout << " cmp(" << comp_b << ", " << comp_a << "): " << (set.value_comp()(comp_b, comp_a));
		std::cout << std::endl;
	}

	std::cout << "----- Operations:" << std::endl;
	{
		std::cout << " find(existing val):" << std::endl;
		ft::set<key_t>	set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		ft::set<key_t>::iterator	it = set.find(arr_exist_key);
		print_set_content(it, ++it);
		std::cout << std::endl;
	}

	{
		std::cout << " find(non-existing val):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		ft::set<key_t>::iterator	it = set.find(arr_nonexist_key);
		if (it != set.end()) {
			std::cout << std::endl;
			print_set_content(it, ++it);
		}
		std::cout << std::endl;
	}

	{
		std::cout << " count(existing val):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		std::cout << " count(" << arr_exist_key << "): " << set.count(arr_exist_key) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << " count(non-existing val):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		std::cout << " count(" << arr_nonexist_key << "): " << set.count(arr_nonexist_key) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << " lower_bound(existing val):" << std::endl;
		ft::set<key_t>	set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		ft::set<key_t>::iterator it = set.lower_bound(arr_exist_key);
		print_set_content(it, ++it);
		std::cout << std::endl;
	}

	{
		std::cout << " lower_bound(non-existing val):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		ft::set<key_t>::iterator it = set.lower_bound(arr_nonexist_key);
		if (it != set.end()) {
			std::cout << std::endl;
			print_set_content(it, ++it);
		}
		std::cout << std::endl;
	}

	{
		std::cout << " upper_bound(existing val):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		ft::set<key_t>::iterator	it = set.upper_bound(arr_exist_key);
		print_set_content(it, ++it);
		std::cout << std::endl;
	}

	{
		std::cout << " upper_bound(non-existing val):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		ft::set<key_t>::iterator it = set.upper_bound(arr_nonexist_key);
		if (it != set.end()) {
			std::cout << std::endl;
			print_set_content(it, ++it);
		}
		std::cout << std::endl;
	}

	{
		typedef ft::set<key_t>::iterator iter;
		
		std::cout << " equal_range(existing val):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		ft::pair<iter, iter> it = set.equal_range(arr_exist_key);
		print_set_content(it.first, it.second);
		std::cout << std::endl;
	}

	{
		std::cout << " equal_range(non-existing val):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		print_set(set);
		typedef ft::set<key_t>::iterator iter;
		std::cout << std::endl;
		ft::pair<iter, iter> it = set.equal_range(arr_nonexist_key);
		print_set_content(it.first, it.second);
		std::cout << std::endl;
	}

	std::cout << "----- Non-member function overloads:" << std::endl;
	{
		std::cout << " operator== (true):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		std::cout << " s == s: " << (set == set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator== (false):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 == s2: " << (set == set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (false):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		std::cout << " s != s:  " << (set != set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator != (true):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 != s2: " << (set != set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (false):" << std::endl;
		ft::set<key_t> set(arr, arr + arr_size);
		std::cout << " s < s: " << (set < set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (true):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 < s2: " << (set < set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator<= (false):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		std::cout << " s2 <= s1: " << (set2 <= set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator<= (true):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 <= s2: " << (set <= set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (true):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		std::cout << " s2 > s1: " << (set2 > set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (false):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 > s2: " << (set > set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator >= (true):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		std::cout << " s2 >= s1: " << (set2 >= set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator>= (false):" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 >= s2: " << (set >= set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " swap:" << std::endl;
		ft::set<key_t> set(arr2, arr2 + arr2_size);
		ft::set<key_t> set2(arr3, arr3 + arr3_size);
		print_set_content(set.begin(), set.end());
		std::cout << std::endl;
		print_set_content(set2.begin(), set2.end());
		ft::swap(set, set2);
		print_set_content(set.begin(), set.end());
		print_set_content(set2.begin(), set2.end());
	}
}