#pragma once

namespace ft {

    template<class InputIt1, class InputIt2>
	bool
    equal(InputIt1 beg1, InputIt1 end1, InputIt2 beg2)	{
		
        for (; beg1 != end1; ++beg1, ++beg2) {
			// ! ==
            if (*beg1 != *beg2) {
				return false;
            }
        }
		return true;
	}

	template<class InputIt1, class InputIt2, class BinPredicate>
	bool
    equal(InputIt1 beg1, InputIt1 end1, InputIt2 beg2, BinPredicate pred) {
		
        for (; beg1 != end1; ++beg1, ++beg2) {	
            if (!pred(*beg1, *beg2)) {
				return false;
            }
        }
		return true;
	}

};