#include <iostream>

#include <map>
#include <vector>

#include "vector.hpp"

class A {

public:
    int a5;
    int a6;

	A(int a) {
		a5 = 5;
		a6 = a;
	}

	A(const A &a) {
		a5 = a.a5;
		a6 = a.a6;
	}
};

template <class T>
struct cmp : std::binary_function<T, T, bool>
{
    bool operator()(const T& x, const T& y) const {
       return x.a6 < y.a6;
	}
};

int main() {
	
	std::map<A, std::string> m;

	m.insert(std::make_pair(A(4), "z"));
	m.insert(std::make_pair(A(2), "y"));
	m.insert(std::make_pair(A(3), "x"));
	m.insert(std::make_pair(A(1), "w"));

	std::cout << &m.begin()->first << std::endl;
	return 0;
}
