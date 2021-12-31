#pragma once

#include <cmath>

namespace ft {
	
	inline u_int64_t __next_capacity__(u_int64_t capacity)
	{
	    return static_cast<u_int64_t>(1U << (static_cast<u_int64_t>(log2(capacity) + 1)));
	}

}