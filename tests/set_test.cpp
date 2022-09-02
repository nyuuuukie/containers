#include <iostream>
#include <string>
#ifdef STD
namespace ft = std;
# include <set>
#else
# include "set.hpp"
#endif

template <typename Key>
void	printAttr(ft::set<Key>& set)
{
	std::cout << "      Empty\t:  " << ((set.empty()) ? "true\n" : "false\n");
	std::cout << "      Size\t:  " << set.size() << "\n";
	std::cout << "      Max size\t:  " << set.max_size() << "\n";
	std::cout << "      Content\t:  [";
	typename ft::set<Key>::const_iterator	beg = set.begin();
	typename ft::set<Key>::const_iterator	it = beg;
	typename ft::set<Key>::iterator	end = set.end();
	for (; it != end; ++it)
	{
		if (it != beg)
			std::cout << ", ";
		std::cout << *it;
	}
	std::cout << "]\n";
}

template <typename Iterator>
void	printContent(Iterator first, Iterator last)
{
	Iterator	it = first;
	std::cout << "      Content\t:  [";
	for (; it != last; ++it)
	{
		if (it != first)
			std::cout << ", ";
		std::cout << *it;
	}
	std::cout << "]\n";
}

void	set_test()
{
	std::cout << "SET:\n";

	std::cout << "  Constructors:\n";

	{
		std::cout << "    Defaul constructor:\n";
		ft::set<int>	set;
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Fill constructor:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Copy constructor:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set1(arr, arr + 6);
		ft::set<int>	set2(set1);
		printAttr(set1);
		std::cout << "\n";
		printAttr(set2);
	}

	std::cout << "\n";

	{
		std::cout << "    Assignation operator:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set1(arr, arr + 6);
		ft::set<int>	set2;
		set2 = set1;
		printAttr(set1);
		std::cout << "\n";
		printAttr(set2);
	}

	std::cout << "\n  Iterators:\n";
	
	{
		std::cout << "    Values from Begin to End:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printContent(set.begin(), set.end());
	}

	std::cout << "\n";
	
	{
		std::cout << "    Values from const Begin to const End:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		const ft::set<int>	set(arr, arr + 6);
		printContent(set.begin(), set.end());
	}

	std::cout << "\n";
	
	{
		std::cout << "    Values from RBegin to REnd:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printContent(set.rbegin(), set.rend());
	}

	std::cout << "\n";
	
	{
		std::cout << "    Values from const RBegin to const REnd:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		const ft::set<int>	set(arr, arr + 6);
		printContent(set.rbegin(), set.rend());
	}

	std::cout << "\n  Capacity:\n";

	{
		std::cout << "    Empty (true):\n";
		ft::set<int>	set;
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Empty (false):\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Size:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Max size:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
	}

	std::cout << "\n  Modifiers:\n";

	{
		std::cout << "    Insert single element:\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		ft::set<int>	set(arr, arr + 5);
		printAttr(set);
		set.insert(4);
		std::cout << "\n";
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Insert with hint:\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		ft::set<int>	set(arr, arr + 5);
		printAttr(set);
		set.insert(set.begin(), 4);
		std::cout << "\n";
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Insert range:\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		printAttr(set);
		set.insert(arr2, arr2 + 3);
		std::cout << "\n";
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Erase single element:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		ft::set<int>::iterator	it = set.begin();
		++it;
		++it;
		++it;
		set.erase(it);
		std::cout << "\n";
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Erase key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		set.erase(4);
		std::cout << "\n";
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Erase range:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		ft::set<int>::iterator	it = set.begin();
		ft::set<int>::iterator	it2 = set.begin();
		++it;
		++it2;
		++it2;
		++it2;
		set.erase(it, it2);
		std::cout << "\n";
		printAttr(set);
	}

	std::cout << "\n";

	{
		std::cout << "    Swap:\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		printAttr(set);
		std::cout << "\n";
		printAttr(set2);
		set.swap(set2);
		std::cout << "\n";
		std::cout << "\n";
		printAttr(set);
		std::cout << "\n";
		printAttr(set2);
	}

	std::cout << "\n";

	{
		std::cout << "    Clear:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		set.clear();
		std::cout << "\n";
		printAttr(set);
	}

	std::cout << "\n  Observers:\n";

	{
		std::cout << "    Key Comp (true):\n";
		ft::set<int>	set;
		std::cout << "      cmp(1, 2)\t:  " << (set.key_comp()(1, 2) ? "true\n" : "false\n");
	}

	std::cout << "\n";

	{
		std::cout << "    Key Comp (false):\n";
		ft::set<int>	set;
		std::cout << "      cmp(2, 1)\t:  " << (set.key_comp()(2, 1) ? "true\n" : "false\n");
	}

	std::cout << "\n";

	{
		std::cout << "    Value Comp (true):\n";
		ft::set<int>	set;
		std::cout << "      cmp(1, 2)\t:  " << (set.value_comp()(1, 2) ? "true\n" : "false\n");
	}

	std::cout << "\n";

	{
		std::cout << "    Value Comp (false):\n";
		ft::set<int>	set;
		std::cout << "      cmp(2, 1)\t:  " << (set.value_comp()(2, 1) ? "true\n" : "false\n");
	}

	std::cout << "\n  Operations:\n";

	{
		std::cout << "    Find existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		ft::set<int>::iterator	it = set.find(4);
		std::cout << "\n";
		printContent(it, ++it);
	}

	std::cout << "\n";

	{
		std::cout << "    Find non-existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		ft::set<int>::iterator	it = set.find(7);
		if (it != set.end())
		{
			std::cout << "\n";
			printContent(it, ++it);
		}
	}

	std::cout << "\n";

	{
		std::cout << "    Count existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		std::cout << "\n";
		std::cout << "      count(4)\t:  " << set.count(4) << "\n";
	}

	std::cout << "\n";

	{
		std::cout << "    Count non-existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		std::cout << "\n";
		std::cout << "      count(7)\t:  " << set.count(7) << "\n";
	}

	std::cout << "\n";

	{
		std::cout << "    Lower bound existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		ft::set<int>::iterator	it = set.lower_bound(4);
		std::cout << "\n";
		printContent(it, ++it);
	}

	std::cout << "\n";

	{
		std::cout << "    Lower bound non-existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		ft::set<int>::iterator	it = set.lower_bound(7);
		if (it != set.end())
		{
			std::cout << "\n";
			printContent(it, ++it);
		}
	}

	std::cout << "\n";

	{
		std::cout << "    Upper bound existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		ft::set<int>::iterator	it = set.upper_bound(4);
		std::cout << "\n";
		printContent(it, ++it);
	}

	std::cout << "\n";

	{
		std::cout << "    Upper bound non-existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		ft::set<int>::iterator	it = set.upper_bound(7);
		if (it != set.end())
		{
			std::cout << "\n";
			printContent(it, ++it);
		}
	}

	std::cout << "\n";

	{
		std::cout << "    Equal range existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		typedef ft::set<int>::iterator iter;
		ft::pair<iter, iter>	it = set.equal_range(4);
		std::cout << "\n";
		printContent(it.first, it.second);
	}

	std::cout << "\n";

	{
		std::cout << "    Equal range non-existing key:\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		printAttr(set);
		typedef ft::set<int>::iterator iter;
		ft::pair<iter, iter>	it = set.equal_range(7);
		std::cout << "\n";
		printContent(it.first, it.second);
	}

	std::cout << "\n  Non-member function overloads:\n";
	
	{
		std::cout << "    Operator == (true):\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		std::cout << "      s == s\t:  " << (set == set ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator == (false):\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "      s1 == s2\t:  " << (set == set2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator != (false):\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		std::cout << "      s != s\t:  " << (set != set ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator != (true):\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "      s1 != s2\t:  " << (set != set2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator < (false):\n";
		int			arr[] = { 1, 2, 3, 4, 5, 6 };
		ft::set<int>	set(arr, arr + 6);
		std::cout << "      s < s\t:  " << (set < set ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator < (true):\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "      s1 < s2\t:  " << (set < set2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator <= (false):\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "      s2 <= s1\t:  " << (set2 <= set ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator <= (true):\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "      s1 <= s2\t:  " << (set <= set2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator > (true):\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "      s2 > s1\t:  " << (set2 > set ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator > (false):\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "      s1 > s2\t:  " << (set > set2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator >= (true):\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "      s2 >= s1\t:  " << (set2 >= set ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator >= (false):\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		std::cout << "      s1 >= s2\t:  " << (set >= set2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Swap:\n";
		int			arr[] = { 1, 2, 3, 5, 6 };
		int			arr2[] = { 4, 7, 8 };
		ft::set<int>	set(arr, arr + 5);
		ft::set<int>	set2(arr2, arr2 + 3);
		printContent(set.begin(), set.end());
		printContent(set2.begin(), set2.end());
		std::cout << "\n";
		ft::swap(set, set2);
		printContent(set.begin(), set.end());
		printContent(set2.begin(), set2.end());
	}
}