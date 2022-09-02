#include <iostream>
#ifdef STD
namespace ft = std;
# include <vector>
#else
# include "vector.hpp"
#endif

template <typename T>
void	printAttr(ft::vector<T>& vec)
{
	std::cout << "      Empty\t:  " << ((vec.empty()) ? "true\n" : "false\n");
	std::cout << "      Size\t:  " << vec.size() << "\n";
	std::cout << "      Max size\t:  " << vec.max_size() << "\n";
	std::cout << "      Content\t:  [";
	typename ft::vector<T>::const_iterator	beg = vec.begin();
	typename ft::vector<T>::const_iterator	it = beg;
	typename ft::vector<T>::iterator	end = vec.end();
	for (; it != end; ++it)
	{
		if (it != beg)
			std::cout << ", ";
		std::cout << *it;
	}
	std::cout << "]\n";
}

template <typename T>
void	printContent(ft::vector<T>& vec)
{
	std::cout << "      Content\t:  [";
	typename ft::vector<T>::const_iterator	beg = vec.begin();
	typename ft::vector<T>::const_iterator	it = beg;
	typename ft::vector<T>::iterator	end = vec.end();
	for (; it != end; ++it)
	{
		if (it != beg)
			std::cout << ", ";
		std::cout << *it;
	}
	std::cout << "]\n";
}

void	vector_test()
{
	std::cout << "VECTOR:\n";

	std::cout << "  Constructors:\n";

	{
		std::cout << "    Defaul constructor:\n";
		ft::vector<int>	vec;
		printAttr(vec);
	}

	std::cout << "\n";

	{
		std::cout << "    Fill constructor (with size 0):\n";
		ft::vector<int> vec(0);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Fill constructor (with size 21):\n";
		ft::vector<int> vec(21);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Fill constructor (with size 21 and val 42):\n";
		ft::vector<int> vec(21, 42);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Range constructor:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Copy constructor:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec1(arr, arr + 6);
		ft::vector<int> vec2(vec1);
		printAttr(vec2);
	}

	std::cout << "\n  Assignation operator:\n";
	
	{
		std::cout << "    Assignation operator (with empty start array):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec1(arr, arr + 6);
		ft::vector<int> vec2 = vec1;
		printAttr(vec2);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Assignation operator (with non-empty start array):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec1(arr, arr + 6);
		ft::vector<int> vec2(7);
		vec2 = vec1;
		printAttr(vec2);
	}

	std::cout << "\n  Iterators:\n";
	
	{
		std::cout << "    Values from Begin to End:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [";
		ft::vector<int>::iterator	beg = vec.begin();
		ft::vector<int>::iterator	it = beg;
		ft::vector<int>::iterator	end = vec.end();
		for (; it != end; ++it)
		{
			if (it != beg)
				std::cout << ", ";
			std::cout << *it;
		}
		std::cout << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Values from const Begin to const End:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [";
		ft::vector<int>::const_iterator	beg = vec.begin();
		ft::vector<int>::const_iterator	it = beg;
		ft::vector<int>::const_iterator	end = vec.end();
		for (; it != end; ++it)
		{
			if (it != beg)
				std::cout << ", ";
			std::cout << *it;
		}
		std::cout << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Values from RBegin to REnd:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [";
		ft::vector<int>::reverse_iterator	beg = vec.rbegin();
		ft::vector<int>::reverse_iterator	it = beg;
		ft::vector<int>::reverse_iterator	end = vec.rend();
		for (; it != end; ++it)
		{
			if (it != beg)
				std::cout << ", ";
			std::cout << *it;
		}
		std::cout << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Values from const RBegin to const REnd:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [";
		ft::vector<int>::const_reverse_iterator	beg = vec.rbegin();
		ft::vector<int>::const_reverse_iterator	it = beg;
		ft::vector<int>::const_reverse_iterator	end = vec.rend();
		for (; it != end; ++it)
		{
			if (it != beg)
				std::cout << ", ";
			std::cout << *it;
		}
		std::cout << "]\n";
	}

	std::cout << "\n  Capacity:\n";
	
	{
		std::cout << "    Size:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Max size:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Resize (increase):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.resize(21);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Resize (decrease):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.resize(3);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Capacity:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Empty (true):\n";
		ft::vector<int> vec(0);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Empty (false):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Reserve (more):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.reserve(21);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Reserve (less):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.reserve(2);
		printAttr(vec);
	}

	std::cout << "\n  Element access:\n";
	
	{
		std::cout << "    Operator []:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [";
		for (size_t i = 0; i < vec.size(); ++i)
		{
			if (i != 0)
				std::cout << ", ";
			std::cout << vec[i];
		}
		std::cout << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Const operator []:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		const ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [";
		for (size_t i = 0; i < vec.size(); ++i)
		{
			if (i != 0)
				std::cout << ", ";
			std::cout << vec[i];
		}
		std::cout << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    At:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [";
		for (size_t i = 0; i < vec.size(); ++i)
		{
			if (i != 0)
				std::cout << ", ";
			std::cout << vec.at(i);
		}
		std::cout << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Const At:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		const ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [";
		for (size_t i = 0; i < vec.size(); ++i)
		{
			if (i != 0)
				std::cout << ", ";
			std::cout << vec.at(i);
		}
		std::cout << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Front:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [" << vec.front() << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Const Front:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		const ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [" << vec.front() << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Back:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [" << vec.back() << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Const Back:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		const ft::vector<int> vec(arr, arr + 6);
		std::cout << "      Content\t:  [" << vec.back() << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Data:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		int*			data = vec.data();
		std::cout << "      Content\t:  [" << *data << "]\n";
	}

	std::cout << "\n";
	
	{
		std::cout << "    Const Data:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		const ft::vector<int> vec(arr, arr + 6);
		const int*		data = vec.data();
		std::cout << "      Content\t:  [" << *data << "]\n";
	}

	std::cout << "\n  Modifiers:\n";
	
	{
		std::cout << "    Assign range (less):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.assign(arr, arr + 3);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Assign range (more):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 5);
		vec.assign(arr, arr + 6);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Assign fill (less):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.assign(3, 42);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Assign fill (more):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.assign(21, 42);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Push back (empty):\n";
		ft::vector<int> vec(0);
		vec.push_back(42);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Push back (non-empty):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.push_back(42);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Pop back:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.pop_back();
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Insert single element:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.insert(vec.begin() + 2, 42);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Insert fill:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.insert(vec.begin() + 2, 3, 42);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Insert range:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.insert(vec.begin() + 2, arr, arr + 6);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Erase single element:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.erase(vec.begin() + 2);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Erase range:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.erase(vec.begin() + 2, vec.end() - 1);
		printAttr(vec);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Swap:\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		printContent(vec1);
		printContent(vec2);
		std::cout << "\n";
		vec1.swap(vec2);
		printContent(vec1);
		printContent(vec2);
	}

	std::cout << "\n";
	
	{
		std::cout << "    Clear:\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		vec.clear();
		printAttr(vec);
	}

	std::cout << "\n  Non-member function overloads:\n";
	
	{
		std::cout << "    Operator == (true):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      v == v\t:  " << (vec == vec ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator == (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		std::cout << "      v1 == v2\t:  " << (vec1 == vec2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator != (false):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      v != v\t:  " << (vec != vec ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator != (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		std::cout << "      v1 != v2\t:  " << (vec1 != vec2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator < (false):\n";
		int				arr[] = { 3, 14, 15, 92, 65, 359 };
		ft::vector<int> vec(arr, arr + 6);
		std::cout << "      v < v\t:  " << (vec < vec ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator < (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		std::cout << "      v1 < v2\t:  " << (vec1 < vec2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator <= (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		std::cout << "      v2 <= v1\t:  " << (vec2 <= vec1 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator <= (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		std::cout << "      v1 <= v2\t:  " << (vec1 <= vec2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator > (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		std::cout << "      v2 > v1\t:  " << (vec2 > vec1 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator > (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		std::cout << "      v1 > v2\t:  " << (vec1 > vec2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator >= (true):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		std::cout << "      v2 >= v1\t:  " << (vec2 >= vec1 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Operator >= (false):\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		std::cout << "      v1 >= v2\t:  " << (vec1 >= vec2 ? "true\n" : "false\n");
	}

	std::cout << "\n";
	
	{
		std::cout << "    Swap:\n";
		int				arr1[] = { 3, 14, 15, 92, 65, 359 };
		int				arr2[] = { 359, 65, 92, 15, 14, 3 };
		ft::vector<int> vec1(arr1, arr1 + 6);
		ft::vector<int> vec2(arr2, arr2 + 6);
		printContent(vec1);
		printContent(vec2);
		std::cout << "\n";
		ft::swap(vec1, vec2);
		printContent(vec1);
		printContent(vec2);
	}
}