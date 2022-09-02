#pragma once

#include <iostream>

#ifdef STD
namespace ft = std;
# include <stack>
#else
# include "stack.hpp"
#endif

template<typename T>
class StackCheck : public ft::stack<T> {

public:
	StackCheck(void) {
        std::cout << "Stack constr" << std::endl;
    }

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
void	print_stack(ft::stack<T>& st) {
	std::cout << " Empty  : " << (st.empty()) << std::endl;
	std::cout << " Size   : " << st.size() << std::endl;
	std::cout << " Content: [";
	while (st.size() != 0) {
		std::cout << st.top();
		st.pop();
		if (st.size() != 0) {
			std::cout << ", ";
		}
	}
	std::cout << "]" << std::endl;
}

void	stack_test(void) {

    int val = 5;
    StackCheck<int> tstack;
    StackCheck<int>::value_type stack_value_type;
    StackCheck<int>::size_type stack_size_type;
    StackCheck<int>::reference stack_reference = val;
    StackCheck<int>::const_reference stack_const_reference = val;

	std::cout << "STACK:" << std::endl;

	int	first[] = { 3, 14, 15, 92, 65, 359 };
	int	second[] = { 359, 65, 92, 15, 14, 3 };

	std::cout << " Member functions:" << std::endl;
	{
		std::cout << " Constructor:" << std::endl;
		ft::stack<int> st;
		print_stack(st);
	}
	std::cout << std::endl;

	{
		std::cout << " Empty (true):" << std::endl;
		ft::stack<int> st;
		print_stack(st);
	}
	std::cout << std::endl;

	{
		std::cout << " Empty (false):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(second[i]);
		}
		print_stack(st);
	}
	std::cout << std::endl;

	{
		std::cout << " Size:" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(second[i]);
		}
		print_stack(st);
	}
	std::cout << std::endl;

	{
		std::cout << " Top:" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(second[i]);
		}
		std::cout << " Content: [" << st.top() << "]" << std::endl;
	}
	std::cout << std::endl;

	{
		std::cout << " Push:" << std::endl;
		ft::stack<int>	st;
		for (size_t i = 0; i < 6; i++) {
			st.push(second[i]);
		}
		print_stack(st);
	}
	std::cout << std::endl;

	{
		std::cout << " Pop:" << std::endl;
		ft::stack<int>	st;
		for (size_t i = 0; i < 6; i++) {
			st.push(second[i]);
		}
		st.pop();
		print_stack(st);
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator == (true):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(first[i]);
		}
		std::cout << " s == s: " << (st == st) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator == (false):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(second[i]);
		}
		std::cout << " s1 == s2: " << (st1 == st2) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator != (false):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(first[i]);
		}
		std::cout << " s != s\t:  " << (st != st) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator != (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(second[i]);
		}
		std::cout << " s1 != s2: " << (st1 != st2) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator < (false):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(first[i]);
		}
		std::cout << " s < s: " << (st < st) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator < (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(second[i]);
		}
		std::cout << " s1 < s2: " << (st1 < st2) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator <= (false):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(second[i]);
		}
		std::cout << " s2 <= s1: " << (st2 <= st1) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator <= (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(second[i]);
		}
		std::cout << " s1 <= s2: " << (st1 <= st2) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator > (false):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(first[i]);
		}
		std::cout << " s > s: " << (st > st) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator > (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(second[i]);
		}
		std::cout << " s2 > s1: " << (st2 > st1) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator >= (false):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(second[i]);
		}
		std::cout << " s1 >= s2: " << (st1 >= st2) << std::endl;
	}
	std::cout << std::endl;
	
	{
		std::cout << " Operator >= (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(second[i]);
		}
		std::cout << " s2 >= s1: " << (st2 >= st1) << std::endl;
	}
}
