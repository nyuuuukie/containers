#pragma once

namespace ft {

template <class Key, class Pair, class Compare>
class map_value_compare {
    
private:
    Compare comp;

public:
    
    map_value_compare() : comp() { }
    map_value_compare(Compare c) : comp(c) { }
    
    const Compare&
    key_comp() const { 
        return comp;
    }

    bool 
    operator()(const Pair &x, const Pair &y) const {
        return comp(x.first, y.first);
    }
    
    bool
    operator()(const Pair &x, const Key &y) const {
        return comp(x.first, y);
    }
    
    bool
    operator()(const Key &x, const Pair &y) const {
        return comp(x, y.first);
    }
};

};