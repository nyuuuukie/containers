#include <iostream>
#include "vector.hpp"
#include <vector>
#include <list>

struct It {

};

int main()
{
	{
		ft::vector<int> b;

		b.push_back(65);
		b.push_back(75);
		b.push_back(85);
		b.push_back(95);
		b.push_back(105);
		b.push_back(115);

		//b.erase(b.begin(), b.end());
		auto beg = b.begin();
		auto end = b.end();
		for (;beg != end; beg++)
		{
			std::cout <<  *beg << std::endl;
		}
		std::cout << "size: " << b.size() << std::endl;
		std::cout << "capacity: " << b.capacity() << std::endl;	
	}
	return 0;
}
