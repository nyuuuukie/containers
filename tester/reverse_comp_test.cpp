#include <iostream>

#ifdef _CONTAINER_TESTER_STD
	namespace ft = std;
	# include <vector>
    # include <stack>
    # include <map>
    # include <set>
#else
    # include "vector.hpp"
    # include "stack.hpp"
    # include "map.hpp"
    # include "set.hpp"
#endif

void
reverse_comp_test(void) {
    int arr[] = {0, 1, 2, 3};
    ft::reverse_iterator<int *>
        x(&arr[4]),
        y(&arr[4]),
        z(&arr[3]);
    
    std::cout << "*x: " << *x << std::endl;
    std::cout << "*y: " << *y << std::endl;
    std::cout << "*z: " << *z << std::endl; 
    std::cout << "(x == y): " << (x == y) << std::endl;     
    std::cout << "(x != y): " << (x != y) << std::endl;     
    std::cout << "(x < y) : " << (x < y)  << std::endl;       
    std::cout << "(x <= y): " << (x <= y) << std::endl;     
    std::cout << "(x == z): " << (x == z) << std::endl;     
    std::cout << "(x != z): " << (x != z) << std::endl;     
    std::cout << "(x < z) : " << (x < z)  << std::endl; 
    std::cout << "(x <= z): " << (x <= z) << std::endl;
}
