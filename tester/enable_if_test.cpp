#include <sstream>
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

template <typename T>
std::string
to_str(T t1, typename ft::enable_if< ft::is_same<std::string, T>::value, T >::type t) {
    (void)t1;
    return (t);
}

template <typename T>
std::string
to_str(T t1, typename ft::enable_if< !ft::is_same<std::string, T>::value, T >::type t) {   
    (void)t1;
    std::stringstream ss;
    ss << t;
    std::string str = ss.str();
    return (str);
}

void 
enable_if_test(void) {
    std::cout << " enable_if:" << std::endl;
    const std::string str = "abracadabra";
    unsigned int num = 42;
    std::cout << "exp: " << num << ", got: " << to_str(num, num) << std::endl;
    std::cout << "exp: " << str << ", got: " << to_str(str, str) << std::endl;
}
