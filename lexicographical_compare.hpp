#pragma once

namespace ft {

template <class InputIt1, class InputIt2>
bool
lexicographical_compare(InputIt1 beg1, InputIt1 end1, InputIt2 beg2, InputIt2 end2) {

    for ( ; beg1 != end1 && beg2 != end2; ++beg1, ++beg2) {

        if (*beg1 < *beg2) {
            return true;
        }
        if (*beg2 < *beg1) {
            return false;
        }

    }
    return (beg1 == end1 && beg2 != end2);
}

template <class InputIt1, class InputIt2, class Compare>
bool
lexicographical_compare(InputIt1 beg1, InputIt1 end1, InputIt2 beg2, InputIt2 end2, Compare comp) {
    
    for ( ; beg1 != end1 && beg2 != end2; ++beg1, ++beg2) {
        
        if (comp(*beg1, *beg2)) {
            return true;
        }   
        if (comp(*beg2, *beg1)) {
            return false;
        }

    }
    return (beg1 == end1 && beg2 != end2);
}

}
