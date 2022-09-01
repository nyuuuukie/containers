#pragma once

#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {

public:
	typedef Container 							container_type;
	typedef typename Container::value_type		value_type;
	typedef typename Container::size_type		size_type;
	typedef typename Container::reference  		reference;
	typedef typename Container::const_reference const_reference;

	// Member functions
	explicit stack(const Container &container = Container());
		
	stack(stack &other);
	~stack(void);
		
	stack &operator=(const stack &other);

	// Element access
	reference top(void);
	const_reference top(void) const;


	// Capacity
	bool empty(void) const;
	size_type size(void) const;


	// Modifiers
	void push(const value_type &value);
	void pop(void);

	template <class V, class U>
	friend bool operator==(const stack<V, U> &lhs, const stack<V, U> &rhs);

	template <class V, class U>
	friend bool operator<(const stack<V, U> &lhs, const stack<V, U> &rhs);

protected:
	// Member objects
	Container c;

};

template <class T, class Container>
stack<T, Container>::stack(const Container &cont) : c(cont) {}
		
template <class T, class Container>
stack<T, Container>::stack(stack &other) {
	std::cout << "stack::copy const" << std::endl;
	*this = other;
}

template <class T, class Container>
stack<T, Container>::~stack(void) {}
		
template <class T, class Container>
stack<T, Container>& stack<T, Container>::operator=(const stack &other) {
	std::cout << "stack::operator=" << std::endl;
	if (this != &other) {
		c = other.c;
	}
	return *this;
}

template <class T, class Container>
typename stack<T, Container>::reference 
stack<T, Container>::top(void) {
	return c.back();
}

template <class T, class Container>
typename stack<T, Container>::const_reference
stack<T, Container>::top(void) const {
	return c.back();
}

template <class T, class Container>
bool
stack<T, Container>::empty() const {
	return c.empty();
}

template <class T, class Container>
typename stack<T, Container>::size_type
stack<T, Container>::size(void) const {
	return c.size();
}


template <class T, class Container>
void
stack<T, Container>::push(const value_type &value) {
	c.push_back(value);
}

template <class T, class Container>
void
stack<T, Container>::pop(void) {
	c.pop_back();
}

// Non-member functions
template <class T, class Container>
inline bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
	return lhs.c == rhs.c;
}

template <class T,  class Container>
inline bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
	return lhs.c < rhs.c;
}

template <class T,  class Container>
inline bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
	return !(lhs == rhs);
}

template <class T,  class Container>
inline bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
	return !(lhs < rhs);
}

template <class T, class Container>
inline bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
	return !(rhs < lhs);
}

template <class T,  class Container>
inline bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs) {
	return rhs < lhs;
}

};