#include <iostream>

#ifdef _CONTAINER_TESTER_STD
	namespace ft = std;
	# include <set>
#else
	# include "set.hpp"
#endif

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

	int	arr[] = { 1, 2, 3, 4, 5, 6 };
	const int arr_size = sizeof(arr) / sizeof(arr[0]);

	int	arr2[] = { 1, 2, 3, 5, 6 };
	const int arr2_size = sizeof(arr2) / sizeof(arr2[0]);
	
	int	arr3[] = { 4, 7, 8 };
	const int arr3_size = sizeof(arr3) / sizeof(arr3[0]);
	
	std::cout << "----- Constructors:" << std::endl;
	{
		std::cout << " constructor (default):" << std::endl;
		ft::set<int> set;
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " constructor(first, last):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " copy constructor:" << std::endl;
		ft::set<int> set1(arr, arr + arr_size);
		ft::set<int> set2(set1);
			std::cout << std::endl;
		print_set(set1);
		print_set(set2);
		std::cout << std::endl;
	}

	{
		std::cout << " operator= :" << std::endl;
		ft::set<int> set1(arr, arr + arr_size);
		ft::set<int> set2;
		set2 = set1;
			std::cout << std::endl;
		print_set(set1);
		print_set(set2);
		std::cout << std::endl;
	}

	std::cout << "----- Iterators:" << std::endl;
	{
		std::cout << " begin() -> end()" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set_content(set.begin(), set.end());
		std::cout << std::endl;
	}
	
	{
		std::cout << " begin() const -> end() const:" << std::endl;
		const ft::set<int> set(arr, arr + arr_size);
		print_set_content(set.begin(), set.end());
		std::cout << std::endl;
	}
	
	{
		std::cout << " rbegin() -> rend():" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set_content(set.rbegin(), set.rend());
		std::cout << std::endl;
	}
	
	{
		std::cout << " const rbegin() -> const rend()" << std::endl;
		const ft::set<int> set(arr, arr + arr_size);
		print_set_content(set.rbegin(), set.rend());
		std::cout << std::endl;
	}

	std::cout << "----- Capacity:" << std::endl;
	{
		std::cout << " empty (true):" << std::endl;
		ft::set<int> set;
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " empty (false):" << std::endl;	
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " size:" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " max_size:" << std::endl;
		ft::set<int>	set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
	}

	std::cout << "----- Modifiers:" << std::endl;
	{
		std::cout << " insert(val): " << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		print_set(set);
		std::cout << std::endl;
		set.insert(4);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " insert with hint:" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		print_set(set);
		std::cout << std::endl;
		set.insert(set.begin(), 4);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " insert(first, last):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		print_set(set);
		std::cout << std::endl;
		set.insert(arr3, arr3 + arr3_size);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " erase(pos):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		ft::set<int>::iterator it = set.begin();
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
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		set.erase(4);
		print_set(set);
		std::cout << std::endl;
	}

	{
		std::cout << " erase(first, last):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		ft::set<int>::iterator it = set.begin();
		ft::set<int>::iterator it2 = set.begin();
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
		ft::set<int>	set(arr2, arr2 + arr2_size);
		ft::set<int>	set2(arr3, arr3 + arr3_size);
			std::cout << std::endl;
		print_set(set);
		print_set(set2);
			std::cout << std::endl;
		set.swap(set2);
		std::cout << std::endl;
			std::cout << std::endl;
		print_set(set);
		print_set(set2);
		std::cout << std::endl;
	}

	{
		std::cout << " clear:" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		set.clear();
		print_set(set);
		std::cout << std::endl;
	}

	std::cout << "----- Observers:" << std::endl;
	{
		std::cout << " key_comp (true):" << std::endl;
		ft::set<int> set;
		std::cout << " cmp(21, 42):  " << (set.key_comp()(21, 42));
		std::cout << std::endl;
	}

	{
		std::cout << " key_comp (false):" << std::endl;
		ft::set<int>	set;
		std::cout << " cmp(42, 21):  " << (set.key_comp()(42, 21));
		std::cout << std::endl;
	}

	{
		std::cout << " value_comp (true):" << std::endl;
		ft::set<int> set;
		std::cout << " cmp(21, 42): " << (set.value_comp()(21, 42));
		std::cout << std::endl;
	}

	{
		std::cout << " value_comp (false):" << std::endl;
		ft::set<int> set;
		std::cout << " cmp(42, 21): " << (set.value_comp()(42, 21));
		std::cout << std::endl;
	}

	std::cout << "----- Operations:" << std::endl;
	{
		std::cout << " find(existing val):" << std::endl;
		ft::set<int>	set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		ft::set<int>::iterator	it = set.find(4);
		print_set_content(it, ++it);
		std::cout << std::endl;
	}

	{
		std::cout << " find(non-existing val):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		ft::set<int>::iterator	it = set.find(7);
		if (it != set.end()) {
			std::cout << std::endl;
			print_set_content(it, ++it);
		}
		std::cout << std::endl;
	}

	{
		std::cout << " count(existing val):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		std::cout << " count(4): " << set.count(4) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << " count(non-existing val):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		std::cout << " count(7): " << set.count(7) << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << " lower_bound(existing val):" << std::endl;
		ft::set<int>	set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		ft::set<int>::iterator it = set.lower_bound(4);
		print_set_content(it, ++it);
		std::cout << std::endl;
	}

	{
		std::cout << " lower_bound(non-existing val):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		ft::set<int>::iterator it = set.lower_bound(7);
		if (it != set.end()) {
			std::cout << std::endl;
			print_set_content(it, ++it);
		}
		std::cout << std::endl;
	}

	{
		std::cout << " upper_bound(existing val):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;
		ft::set<int>::iterator	it = set.upper_bound(4);
		print_set_content(it, ++it);
		std::cout << std::endl;
	}

	{
		std::cout << " upper_bound(non-existing val):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		ft::set<int>::iterator it = set.upper_bound(7);
		if (it != set.end()) {
			std::cout << std::endl;
			print_set_content(it, ++it);
		}
		std::cout << std::endl;
	}

	{
		typedef ft::set<int>::iterator iter;
		
		std::cout << " equal_range(existing val):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		std::cout << std::endl;

		ft::pair<iter, iter> it = set.equal_range(4);
		print_set_content(it.first, it.second);
		std::cout << std::endl;
	}

	{
		std::cout << " equal_range(non-existing val):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		print_set(set);
		typedef ft::set<int>::iterator iter;
			std::cout << std::endl;
		ft::pair<iter, iter> it = set.equal_range(7);
		print_set_content(it.first, it.second);
		std::cout << std::endl;
	}

	std::cout << "----- Non-member function overloads:" << std::endl;
	{
		std::cout << " operator== (true):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		std::cout << " s == s: " << (set == set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator== (false):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 == s2: " << (set == set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (false):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		std::cout << " s != s:  " << (set != set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator != (true):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 != s2:  " << (set != set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (false):" << std::endl;
		ft::set<int> set(arr, arr + arr_size);
		std::cout << " s < s: " << (set < set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (true):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 < s2: " << (set < set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator<= (false):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		std::cout << " s2 <= s1: " << (set2 <= set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator<= (true):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 <= s2: " << (set <= set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (true):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		std::cout << " s2 > s1: " << (set2 > set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (false):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 > s2: " << (set > set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator >= (true):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		std::cout << " s2 >= s1: " << (set2 >= set);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator>= (false):" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		std::cout << " s1 >= s2: " << (set >= set2);
		std::cout << std::endl;
	}
	
	{
		std::cout << " swap:" << std::endl;
		ft::set<int> set(arr2, arr2 + arr2_size);
		ft::set<int> set2(arr3, arr3 + arr3_size);
		print_set_content(set.begin(), set.end());
		std::cout << std::endl;
		print_set_content(set2.begin(), set2.end());
		ft::swap(set, set2);
		print_set_content(set.begin(), set.end());
		print_set_content(set2.begin(), set2.end());
	}
}