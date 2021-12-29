#include <iostream>

#include <map>

int main()
{
	std::map<std::string, int> a;
	std::map<std::string, int> b;

	std::cout << a.end()->second << " " << b.end()->second << std::endl;  

	a.insert(a.end(), std::make_pair("Hello", 1));
	a.insert(a.end(), std::make_pair("Dear", 2));
	a.insert(a.end(), std::make_pair("Ilnur", 3));
	a.insert(a.end(), std::make_pair("!", 4));

	auto it = a.begin();

	std::cout << (it->first) << "" << (it->second) << std::endl;
	it++;
	
	std::cout << (it->first) << "" << (it->second) << std::endl;
	it++;

	std::cout << (it->first) << "" << (it->second) << std::endl;
	it++;

	std::cout << (it->first) << "" << (it->second) << std::endl;
	it++;

	std::cout << (it->first) << "" << (it->second) << std::endl;
	it++;

	std::cout << (it->first) << "" << (it->second) << std::endl;
	it++;

	std::cout << (it->first) << "" << (it->second) << std::endl;
	it++;

	std::cout << (it->first) << "" << (it->second) << std::endl;
	it++;

	std::cout << (it->first) << "" << (it->second) << std::endl;
	it++;

	std::cout << (it->first) << std::endl;
	it++;

	std::cout << (it->first) << std::endl;
	it--;
	std::cout << (it->first) << std::endl;

	std::cout << a.size() << " " << std::endl;
	return 0;
}
