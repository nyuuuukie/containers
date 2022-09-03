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

class A {};

void
print_integral(std::string title, bool value) {
    std::cout << " " << title << (value ? "true" : "false") << std::endl;
}

void
is_integral_test(void) {

    std::cout << "is_integral:" << std::endl;
    print_integral("class      : ", ft::is_integral<A>::value);
    print_integral("float      : ", ft::is_integral<float>::value);
    print_integral("float      : ", ft::is_integral<double>::value);
    print_integral("bool       : ", ft::is_integral<bool>::value);
    print_integral("wchar_t    : ", ft::is_integral<unsigned char>::value);
    print_integral("ushort     : ", ft::is_integral<unsigned short>::value);
    print_integral("uint       : ", ft::is_integral<unsigned int>::value);
    print_integral("ulong      : ", ft::is_integral<unsigned long>::value);
    print_integral("ulong long : ", ft::is_integral<unsigned long long>::value);
    print_integral("wchar_t    : ", ft::is_integral<char>::value);
    print_integral("short      : ", ft::is_integral<short>::value);
    print_integral("int        : ", ft::is_integral<int>::value);
    print_integral("long       : ", ft::is_integral<long>::value);
    print_integral("long long  : ", ft::is_integral<long long>::value);
    print_integral("wchar_t    : ", ft::is_integral<wchar_t>::value);

    print_integral("const class      : ", ft::is_integral<const A>::value);
    print_integral("const float      : ", ft::is_integral<const float>::value);
    print_integral("const double     : ", ft::is_integral<const double>::value);
    print_integral("const bool       : ", ft::is_integral<const bool>::value);
    print_integral("const wchar_t    : ", ft::is_integral<const unsigned char>::value);
    print_integral("const ushort     : ", ft::is_integral<const unsigned short>::value);
    print_integral("const uint       : ", ft::is_integral<const unsigned int>::value);
    print_integral("const ulong      : ", ft::is_integral<const unsigned long>::value);
    print_integral("const ulong long : ", ft::is_integral<const unsigned long long>::value);
    print_integral("const wchar_t    : ", ft::is_integral<const char>::value);
    print_integral("const short      : ", ft::is_integral<const short>::value);
    print_integral("const int        : ", ft::is_integral<const int>::value);
    print_integral("const long       : ", ft::is_integral<const long>::value);
    print_integral("const long long  : ", ft::is_integral<const long long>::value);
    print_integral("const wchar_t    : ", ft::is_integral<const wchar_t>::value);
}
