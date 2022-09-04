#include <iostream>
#include <map>

#ifdef _CONTAINER_TESTER_STD
	namespace ft = std;
    # include <map>
#else
    # include "map.hpp"
#endif


class A {
public:
    int a5;
    int a6;

	A(void) {
		a5 = 0;
		a6 = 0;
	};

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
struct cmp : std::binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const {
       return x.a6 < y.a6;
	}
};

void
map_comp_use_test(void) {
	
	ft::map<A, std::string, cmp<A> > m;

	m.insert(ft::make_pair(A(4), "fourth"));
	m.insert(ft::make_pair(A(2), "second"));
	m.insert(ft::make_pair(A(3), "third"));
	m.insert(ft::make_pair(A(1), "first"));

	ft::map<A, std::string, cmp<A> >::const_iterator it = m.begin(); 
	for (; it != m.end(); ++it) {
		std::cout << it->second << std::endl;
	}

}