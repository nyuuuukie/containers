#include <iostream>
#include <string>
#ifdef STD
namespace ft = std;
# include <map>
#else
# include "map.hpp"
#endif

template <typename Key, typename Val>
void	printAttr(ft::map<Key, Val>& map)
{
	std::cout << "      Empty\t:  " << ((map.empty()) ? "true\n" : "false\n");
	std::cout << "      Size\t:  " << map.size() << "\n";
	std::cout << "      Max size\t:  " << map.max_size() << "\n";
	std::cout << "      Content\t:  [(";
	typename ft::map<Key, Val>::const_iterator	beg = map.begin();
	typename ft::map<Key, Val>::const_iterator	it = beg;
	typename ft::map<Key, Val>::iterator	end = map.end();
	for (; it != end; ++it)
	{
		if (it != beg)
			std::cout << "), (";
		std::cout << (*it).first << " ; " << (*it).second;
	}
	std::cout << ")]\n";
}

template <typename Key, typename Val>
void	printAttr(const ft::map<Key, Val>& map)
{
	std::cout << "      Empty\t:  " << ((map.empty()) ? "true\n" : "false\n");
	std::cout << "      Size\t:  " << map.size() << "\n";
	std::cout << "      Max size\t:  " << map.max_size() << "\n";
	std::cout << "      Content\t:  [(";
	typename ft::map<Key, Val>::const_iterator	beg = map.begin();
	typename ft::map<Key, Val>::const_iterator	it = beg;
	typename ft::map<Key, Val>::const_iterator	end = map.end();
	for (; it != end; ++it)
	{
		if (it != beg)
			std::cout << "), (";
		std::cout << (*it).first << " ; " << (*it).second;
	}
	std::cout << ")]\n";
}

template <typename Iterator>
void	printContent(Iterator first, Iterator last)
{
	Iterator	it = first;
	std::cout << "      Content\t:  [(";
	for (; it != last; ++it)
	{
		if (it != first)
			std::cout << "), (";
		std::cout << (*it).first << " ; " << (*it).second;
	}
	std::cout << ")]\n";
}

typedef ft::pair<int, std::string> ispair;

void	map_test()
{
	std::cout << "MAP:\n";

	std::cout << "  Constructors:\n";

	{
		std::cout << "    Defaul constructor:\n";
		ft::map<int, std::string>	map;
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Fill constructor:\n";
		int			iarr[] = { 1, 2, 3, 6, 5, 4, 4 };
		std::string	sarr[] = { "One", "Two", "Three", "Six", "Five", "Four", "asdasda" };
		ispair		parr[7];
		for (size_t i = 0; i < 7; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 7);
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Copy constructor:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		ft::map<int, std::string>	map2(map);
		printAttr(map);
		std::cout << "\n";
		printAttr(map2);
	}

	std::cout << "\n";

	{
		std::cout << "    Assignation operator:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		ft::map<int, std::string>	map2;
		map2 = map;
		printAttr(map);
		std::cout << "\n";
		printAttr(map2);
	}

	std::cout << "\n  Iterators:\n";
	
	{
		std::cout << "    Values from Begin to End:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printContent(map.begin(), map.end());
	}

	std::cout << "\n";
	
	{
		std::cout << "    Values from const Begin to const End:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		const ft::map<int, std::string>	map(parr, parr + 6);
		printContent(map.begin(), map.end());
	}

	std::cout << "\n";
	
	{
		std::cout << "    Values from RBegin to REnd:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printContent(map.rbegin(), map.rend());
	}

	std::cout << "\n";
	
	{
		std::cout << "    Values from const RBegin to const REnd:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		const ft::map<int, std::string>	map(parr, parr + 6);
		printContent(map.rbegin(), map.rend());
	}

	std::cout << "\n  Capacity:\n";

	{
		std::cout << "    Empty (true):\n";
		ft::map<int, std::string>	map;
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Empty (false):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Size:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Max size:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
	}

	std::cout << "\n  Element access:\n";

	{
		std::cout << "    Operator [] (existing element):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		map[6] = "not Six :)";
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Operator [] (non-existing element):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		map[7] = "Seven";
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Operator at (existing element):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		map.at(6) = "not Six :)";
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Operator at (non-existing element):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		try
		{
			map.at(7) = "Seven";
		}
		catch(const std::exception& e)
		{
			std::cout << "      Excetion\t:  " << e.what() << '\n';
		}
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Const Operator at (existing element):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		const ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		map.at(6);
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Const Operator at (non-existing element):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		const ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		try
		{
			map.at(7);
		}
		catch(const std::exception& e)
		{
			std::cout << "      Excetion\t:  " << e.what() << '\n';
		}
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n  Modifiers:\n";

	{
		std::cout << "    Insert single element:\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		printAttr(map);
		map.insert(ft::make_pair(4, "Four"));
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Insert with hint:\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		printAttr(map);
		map.insert(map.begin(), ft::make_pair(4, "Four"));
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Insert range:\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		printAttr(map);
		map.insert(parr2, parr2 + 3);
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Erase single element:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		ft::map<int, std::string>::iterator	it = map.begin();
		++it;
		++it;
		++it;
		map.erase(it);
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Erase key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		map.erase(4);
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Erase range:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		ft::map<int, std::string>::iterator	it = map.begin();
		ft::map<int, std::string>::iterator	it2 = map.begin();
		++it;
		++it2;
		++it2;
		++it2;
		map.erase(it, it2);
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n";

	{
		std::cout << "    Swap:\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		printAttr(map);
		std::cout << "\n";
		printAttr(map2);
		map.swap(map2);
		std::cout << "\n";
		std::cout << "\n";
		printAttr(map);
		std::cout << "\n";
		printAttr(map2);
	}

	std::cout << "\n";

	{
		std::cout << "    Clear:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		map.clear();
		std::cout << "\n";
		printAttr(map);
	}

	std::cout << "\n  Observers:\n";

	{
		std::cout << "    Key Comp (true):\n";
		ft::map<int, std::string>	map;
		std::cout << "      cmp(1, 2)\t:  " << (map.key_comp()(1, 2) ? "true\n" : "false\n");
	}

	std::cout << "\n";

	{
		std::cout << "    Key Comp (false):\n";
		ft::map<int, std::string>	map;
		std::cout << "      cmp(2, 1)\t:  " << (map.key_comp()(2, 1) ? "true\n" : "false\n");
	}

	std::cout << "\n";

	{
		std::cout << "    Value Comp (true):\n";
		ft::map<int, std::string>	map;
		ispair						a = ft::make_pair(1, "a");
		ispair						b = ft::make_pair(2, "b");
		std::cout << "      cmp(1, 2)\t:  " << (map.value_comp()(a, b) ? "true\n" : "false\n");
	}

	std::cout << "\n";

	{
		std::cout << "    Value Comp (false):\n";
		ft::map<int, std::string>	map;
		ispair						a = ft::make_pair(1, "a");
		ispair						b = ft::make_pair(2, "b");
		std::cout << "      cmp(2, 1)\t:  " << (map.value_comp()(b, a) ? "true\n" : "false\n");
	}

	std::cout << "\n  Operations:\n";

	{
		std::cout << "    Find existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		ft::map<int, std::string>::iterator	it = map.find(4);
		std::cout << "\n";
		printContent(it, ++it);
	}

	std::cout << "\n";

	{
		std::cout << "    Find non-existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		ft::map<int, std::string>::iterator	it = map.find(7);
		if (it != map.end())
		{
			std::cout << "\n";
			printContent(it, ++it);
		}
	}

	std::cout << "\n";

	{
		std::cout << "    Count existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		std::cout << "\n";
		std::cout << "      count(4)\t:  " << map.count(4) << "\n";
	}

	std::cout << "\n";

	{
		std::cout << "    Count non-existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		std::cout << "\n";
		std::cout << "      count(7)\t:  " << map.count(7) << "\n";
	}

	std::cout << "\n";

	{
		std::cout << "    Lower bound existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		ft::map<int, std::string>::iterator	it = map.lower_bound(4);
		std::cout << "\n";
		printContent(it, ++it);
	}

	std::cout << "\n";

	{
		std::cout << "    Lower bound non-existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		ft::map<int, std::string>::iterator	it = map.lower_bound(7);
		if (it != map.end())
		{
			std::cout << "\n";
			printContent(it, ++it);
		}
	}

	std::cout << "\n";

	{
		std::cout << "    Upper bound existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		ft::map<int, std::string>::iterator	it = map.upper_bound(4);
		std::cout << "\n";
		printContent(it, ++it);
	}

	std::cout << "\n";

	{
		std::cout << "    Upper bound non-existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		ft::map<int, std::string>::iterator	it = map.upper_bound(7);
		if (it != map.end())
		{
			std::cout << "\n";
			printContent(it, ++it);
		}
	}

	std::cout << "\n";

	{
		std::cout << "    Equal range existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		typedef ft::map<int, std::string>::iterator iter;
		ft::pair<iter, iter>	it = map.equal_range(4);
		std::cout << "\n";
		printContent(it.first, it.second);
	}

	std::cout << "\n";

	{
		std::cout << "    Equal range non-existing key:\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		printAttr(map);
		typedef ft::map<int, std::string>::iterator iter;
		ft::pair<iter, iter>	it = map.equal_range(7);
		std::cout << "\n";
		printContent(it.first, it.second);
	}

	std::cout << "\n  Non-member function overloads:\n";
	
	{
		std::cout << "    Operator == (true):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		std::cout << "      m == m\t:  " << (map == map ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator == (false):\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "      m1 == m2\t:  " << (map == map2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator != (false):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		std::cout << "      m != m\t:  " << (map != map ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator != (true):\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "      m1 != m2\t:  " << (map != map2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator < (false):\n";
		int			iarr[] = { 1, 2, 3, 4, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Four", "Five", "Six" };
		ispair		parr[6];
		for (size_t i = 0; i < 6; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		ft::map<int, std::string>	map(parr, parr + 6);
		std::cout << "      m < m\t:  " << (map < map ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator < (true):\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "      m1 < m2\t:  " << (map < map2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator <= (false):\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "      m2 <= m1\t:  " << (map2 <= map ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator <= (true):\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "      m1 <= m2\t:  " << (map <= map2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator > (true):\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "      m2 > m1\t:  " << (map2 > map ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator > (false):\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "      m1 > m2\t:  " << (map > map2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator >= (true):\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "      m2 >= m1\t:  " << (map2 >= map ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator >= (false):\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		std::cout << "      m1 >= m2\t:  " << (map >= map2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Swap:\n";
		int			iarr[] = { 1, 2, 3, 5, 6 };
		std::string	sarr[] = { "One", "Two", "Three", "Five", "Six" };
		ispair		parr[5];
		for (size_t i = 0; i < 5; i++)
			parr[i] = ft::make_pair(iarr[i], sarr[i]);
		int			iarr2[] = { 4, 7, 8 };
		std::string	sarr2[] = { "Four", "Seven", "Eight" };
		ispair		parr2[3];
		for (size_t i = 0; i < 3; i++)
			parr2[i] = ft::make_pair(iarr2[i], sarr2[i]);
		ft::map<int, std::string>	map(parr, parr + 5);
		ft::map<int, std::string>	map2(parr2, parr2 + 3);
		printContent(map.begin(), map.end());
		printContent(map2.begin(), map2.end());
		std::cout << "\n";
		ft::swap(map, map2);
		printContent(map.begin(), map.end());
		printContent(map2.begin(), map2.end());
	}
}