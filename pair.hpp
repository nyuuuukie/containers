#pragma once

namespace ft {

	template <class T1, class T2> 
	struct pair {

		// Member types
		typedef T1 first_type;
		typedef T2 second_type;

		// Member objects
		T1 first;
		T2 second;

		// Member functions
		pair()
		: first(), second() { }

		pair(const T1& _first, const T2& _second)
		: first(_first), second(_second) { }

	    template<typename U1, typename U2>
		pair(const pair<U1, U2>& p)
		: first(p.first), second(p.second) { }
	};

	template<typename T1, typename T2>
    inline bool
    operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    { return lhs.first == rhs.first && lhs.second == rhs.second; }

	template<typename T1, typename T2>
    inline bool
    operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    { return lhs.first < rhs.first || lhs.second < rhs.second; }

	template<typename T1, typename T2>
    inline bool
    operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    { return !(lhs == rhs); }

	template<typename T1, typename T2>
    inline bool
    operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    { return rhs < lhs; }

	template<typename T1, typename T2>
    inline bool
    operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    { return !(rhs < lhs); }

	template<typename T1, typename T2>
    inline bool
    operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    { return !(lhs < rhs); }

	template<typename T1, typename T2>
    inline pair<T1, T2>
    make_pair(T1 first, T2 second)
    { return pair<T1, T2>(first, second); }

};
