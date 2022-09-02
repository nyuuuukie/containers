#include <iostream>

#ifdef _CONTAINER_TESTER_STD
namespace ft = std;
# include <stack>
#else
# include "stack.hpp"
#endif

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

    int val = 5;
    StackCheck<int>::value_type stack_value_type = 0;
    StackCheck<int>::size_type stack_size_type = 0;
    StackCheck<int>::reference stack_reference = val;
    StackCheck<int>::const_reference stack_const_reference = val;
	stack_value_type = 0;
	stack_size_type = 0;
	stack_reference = stack_const_reference;

	std::cout << "---------- stack:" << std::endl;

	int	first[] = { 3, 14, 15, 92, 65, 359 };
	int	r_first[] = { 359, 65, 92, 15, 14, 3 };

	std::cout << "----- Member functions:" << std::endl;
	{
		std::cout << " constructor:" << std::endl;
		ft::stack<int> st;
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " empty (true):" << std::endl;
		ft::stack<int> st;
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " empty (false):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(r_first[i]);
		}
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " size:" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(r_first[i]);
		}
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " top:" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(r_first[i]);
		}
		std::cout << " content : [ " << st.top() << " ]" << std::endl;
		std::cout << std::endl;
	}

	{
		std::cout << " push:" << std::endl;
		ft::stack<int>	st;
		for (size_t i = 0; i < 6; i++) {
			st.push(r_first[i]);
		}
		print_stack(st);
		std::cout << std::endl;
	}

	{
		std::cout << " pop:" << std::endl;
		ft::stack<int>	st;
		for (size_t i = 0; i < 6; i++) {
			st.push(r_first[i]);
		}
		st.pop();
		print_stack(st);
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator== (true):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(first[i]);
		}
		std::cout << " s == s: " << (st == st) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator== (false):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(r_first[i]);
		}
		std::cout << " s1 == s2: " << (st1 == st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (false):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(first[i]);
		}
		std::cout << " s != s: " << (st != st) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator!= (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(r_first[i]);
		}
		std::cout << " s1 != s2: " << (st1 != st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (false):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(first[i]);
		}
		std::cout << " s < s: " << (st < st) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator< (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(r_first[i]);
		}
		std::cout << " s1 < s2: " << (st1 < st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " Operator<= (false):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(r_first[i]);
		}
		std::cout << " s2 <= s1: " << (st2 <= st1) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator<= (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(r_first[i]);
		}
		std::cout << " s1 <= s2: " << (st1 <= st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (false):" << std::endl;
		ft::stack<int> st;
		for (size_t i = 0; i < 6; i++) {
			st.push(first[i]);
		}
		std::cout << " s > s: " << (st > st) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator> (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(r_first[i]);
		}
		std::cout << " s2 > s1: " << (st2 > st1) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator>= (false):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(r_first[i]);
		}
		std::cout << " s1 >= s2: " << (st1 >= st2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		std::cout << " operator>= (true):" << std::endl;
		ft::stack<int> st1;
		ft::stack<int> st2;
		for (size_t i = 0; i < 6; i++) {
			st1.push(first[i]);
		}
		for (size_t i = 0; i < 6; i++) {
			st2.push(r_first[i]);
		}
		std::cout << " s2 >= s1: " << (st2 >= st1) << std::endl;
	}
}
