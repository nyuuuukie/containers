#include <iostream>

#ifdef _CONTAINER_TESTER_STD
namespace ft = std;
# include <stack>
#else
# include "stack.hpp"
#endif

typedef int key_t;

template<typename T>
class StackCheck : public ft::stack<T> {

public:
	StackCheck(void) { }

	StackCheck(const StackCheck<T> &other) { 
        *this = other;
    }

	StackCheck<T>& operator=(const StackCheck<T>& other) {
		this->c = other.c;
		return *this;
	}
	~StackCheck(void) {}

	typedef typename ft::stack<T>::container_type::iterator iterator;
    typedef typename ft::stack<T>::value_type value_type;
    typedef typename ft::stack<T>::size_type size_type;
    typedef typename ft::stack<T>::reference reference;
    typedef typename ft::stack<T>::const_reference const_reference;

	iterator begin(void) { return this->c.begin(); }
	iterator end(void) { return this->c.end(); }
};

template <typename T>
void
print_stack(ft::stack<T>& st) {
	std::cout << " empty   : " << st.empty() << std::endl;
	std::cout << " size    : " << st.size() << std::endl;
	std::cout << " content : [";
	while (st.size() != 0) {
		std::cout << " ";
		std::cout << st.top();
		st.pop();
	}
	std::cout << " ]" << std::endl;
}

void
stack_test(void) {

    key_t val = 5;
    StackCheck<key_t>::value_type stack_value_type = 0;
    StackCheck<key_t>::size_type stack_size_type = 0;
    StackCheck<key_t>::reference stack_reference = val;
    StackCheck<key_t>::const_reference stack_const_reference = val;
	stack_value_type = 0;
	stack_size_type = 0;
	stack_reference = stack_const_reference;

	std::cout << "---------- stack:" << std::endl;

	const key_t arr[] = { 21, 42, 84, 168, 336, 672 };
	const key_t r_arr[] = { 672, 336, 168, 84, 42, 21 };

	const std::size_t size_arr = sizeof(arr) / sizeof(arr[0]);
	const std::size_t size_r_arr = sizeof(r_arr) / sizeof(r_arr[0]);

	std::cout << "----- Member functions:" << std::endl;
	{
		std::cout << " constructor:" << std::endl;
		ft::stack<key_t> st;
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " empty (true):" << std::endl;
		ft::stack<key_t> st;
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " empty (false):" << std::endl;
		ft::stack<key_t> st;
		for (size_t i = 0; i < size_r_arr; i++) {
			st.push(r_arr[i]);
		}
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " size:" << std::endl;
		ft::stack<key_t> st;
		for (size_t i = 0; i < size_r_arr; i++) {
			st.push(r_arr[i]);
		}
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " top:" << std::endl;
		ft::stack<key_t> st;
		for (size_t i = 0; i < size_r_arr; i++) {
			st.push(r_arr[i]);
		}
		std::cout << " content : [ " << st.top() << " ]" << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << " push:" << std::endl;
		ft::stack<key_t> st;
		for (size_t i = 0; i < size_r_arr; i++) {
			st.push(r_arr[i]);
		}
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " pop:" << std::endl;
		ft::stack<key_t> st;
		for (size_t i = 0; i < size_r_arr; i++) {
			st.push(r_arr[i]);
		}
		st.pop();
		print_stack(st);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator== (true):" << std::endl;
		ft::stack<key_t> st;
		for (size_t i = 0; i < size_arr; i++) {
			st.push(arr[i]);
		}
		std::cout << " s == s: " << (st == st) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator== (false):" << std::endl;
		ft::stack<key_t> st1;
		ft::stack<key_t> st2;
		for (size_t i = 0; i < size_arr; i++) {
			st1.push(arr[i]);
		}
		for (size_t i = 0; i < size_r_arr; i++) {
			st2.push(r_arr[i]);
		}
		std::cout << " s1 == s2: " << (st1 == st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (false):" << std::endl;
		ft::stack<key_t> st;
		for (size_t i = 0; i < size_arr; i++) {
			st.push(arr[i]);
		}
		std::cout << " s != s: " << (st != st) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (true):" << std::endl;
		ft::stack<key_t> st1;
		ft::stack<key_t> st2;
		for (size_t i = 0; i < size_arr; i++) {
			st1.push(arr[i]);
		}
		for (size_t i = 0; i < size_r_arr; i++) {
			st2.push(r_arr[i]);
		}
		std::cout << " s1 != s2: " << (st1 != st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (false):" << std::endl;
		ft::stack<key_t> st;
		for (size_t i = 0; i < size_arr; i++) {
			st.push(arr[i]);
		}
		std::cout << " s < s: " << (st < st) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (true):" << std::endl;
		ft::stack<key_t> st1;
		ft::stack<key_t> st2;
		for (size_t i = 0; i < size_arr; i++) {
			st1.push(arr[i]);
		}
		for (size_t i = 0; i < size_r_arr; i++) {
			st2.push(r_arr[i]);
		}
		std::cout << " s1 < s2: " << (st1 < st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " Operator<= (false):" << std::endl;
		ft::stack<key_t> st1;
		ft::stack<key_t> st2;
		for (size_t i = 0; i < size_arr; i++) {
			st1.push(arr[i]);
		}
		for (size_t i = 0; i < size_r_arr; i++) {
			st2.push(r_arr[i]);
		}
		std::cout << " s2 <= s1: " << (st2 <= st1) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator<= (true):" << std::endl;
		ft::stack<key_t> st1;
		ft::stack<key_t> st2;
		for (size_t i = 0; i < size_arr; i++) {
			st1.push(arr[i]);
		}
		for (size_t i = 0; i < size_r_arr; i++) {
			st2.push(r_arr[i]);
		}
		std::cout << " s1 <= s2: " << (st1 <= st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (false):" << std::endl;
		ft::stack<key_t> st;
		for (size_t i = 0; i < size_arr; i++) {
			st.push(arr[i]);
		}
		std::cout << " s > s: " << (st > st) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (true):" << std::endl;
		ft::stack<key_t> st1;
		ft::stack<key_t> st2;
		for (size_t i = 0; i < size_arr; i++) {
			st1.push(arr[i]);
		}
		for (size_t i = 0; i < size_r_arr; i++) {
			st2.push(r_arr[i]);
		}
		std::cout << " s2 > s1: " << (st2 > st1) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator>= (false):" << std::endl;
		ft::stack<key_t> st1;
		ft::stack<key_t> st2;
		for (size_t i = 0; i < size_arr; i++) {
			st1.push(arr[i]);
		}
		for (size_t i = 0; i < size_r_arr; i++) {
			st2.push(r_arr[i]);
		}
		std::cout << " s1 >= s2: " << (st1 >= st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator>= (true):" << std::endl;
		ft::stack<key_t> st1;
		ft::stack<key_t> st2;
		for (size_t i = 0; i < size_arr; i++) {
			st1.push(arr[i]);
		}
		for (size_t i = 0; i < size_r_arr; i++) {
			st2.push(r_arr[i]);
		}
		std::cout << " s2 >= s1: " << (st2 >= st1) << std::endl;
	}
}
