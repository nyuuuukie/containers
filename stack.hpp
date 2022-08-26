#pragma once

#include "vector.hpp"

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack {

		// Member types
		public:
		typedef Container 							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference  		reference;
		typedef typename Container::const_reference const_reference;

		// Member functions
		explicit stack( const Container& cont = Container() ) : c(cont) {}
		
		stack( stack &other ) {
			*this = other;
		}
		~stack() {}
		
		stack& operator=( const stack& other ) {
			if (this != &other) {
				c = other.c;
			}
			return *this;
		}

		// Element access
		reference top() {
			return c.back();
		}

		const_reference top() const {
			return c.back();
		}
		
		// Capacity
		bool empty() const {
			return c.empty();
		}

		size_type size() const {
			return c.size();
		}

		// Modifiers
		void push( const value_type& value ) {
			c.push_back(value);
		}

		void pop() {
			c.pop_back();
		}

		// Member objects
		protected:
			Container c;	

	};

	// Non-member functions
	template< class T, class Container >
	inline bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs == rhs;
	}

	template< class T, class Container >
	inline bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs != rhs;
	}

	template< class T, class Container >
	inline bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs < rhs;
	}

	template< class T, class Container >
	inline bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs <= rhs;
	}

	template< class T, class Container >
	inline bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs > rhs;
	}

	template< class T, class Container >
	inline bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs >= rhs;
	}

};