#include <iostream>

#include <vector>
// #include "vector.hpp"


#include <map>
class A {
// public:
//     int a1;
//     int a2;
//     int a3;
//     int a4;
//     int a5;
//     int a6;

	// A(int a) {
	// 	a1 = 1;
	// 	a2 = 2;
	// 	a3 = 3;
	// 	a4 = 4;
	// 	a5 = 5;
	// 	a6 = a;
	// }

	// A(const A &a) {
	// 	a1 = a.a1;
	// 	a2 = a.a2;
	// 	a3 = a.a3;
	// 	a4 = a.a4;
	// 	a5 = a.a5;
	// 	a6 = a.a6;
	// }
};

// template <class T>
// struct cmp : std::binary_function<T, T, bool>
// {
//     bool operator()(const T& x, const T& y) const {
//        return x.a6 < y.a6;
// 	}
// };

int main() {
	
	std::map<A, std::string > m;

	m.insert(std::make_pair(A(), "z"));
	m.insert(std::make_pair(A(), "y"));
	m.insert(std::make_pair(A(), "x"));
	m.insert(std::make_pair(A(), "w"));

	std::cout << &m.begin()->first << std::endl;
	return 0;
}
