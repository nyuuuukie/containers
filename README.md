# STL-containers

## Description

The aim of this project is to reproduce some of basic STL-containers:
- [std::vector](http://www.cplusplus.com/reference/vector/vector)
- [std::stack](http://www.cplusplus.com/reference/stack/stack)
- [std::map](http://www.cplusplus.com/reference/map/map)
- [std::set](http://www.cplusplus.com/reference/set/set)

All the containers are located in the ft namespace

ft::map and ft::set implementations use Red-Black Tree as the underlying data structure.

## Red-black tree
ft::rbt implemented as a independent container and could be used separately from set or map.
```c++
#include "rbt.hpp"
```

### Console visualizer

For example, these lines

```c++
#include "rbt.hpp"
#include "rbt_visualizer.hpp"

int main() {

    ft::rbt<int> tree;
    for (int i = 1; i < 10; i++) {
        tree.insert(i);
    }

    ft::rbt_visualizer<int> rbv;
    rbv.visualize(tree);
    
    return 0;
}
```

will produce this output to stdout:
![VisualizatorExample](./screenshots/visualizer.png)

Compile

Tests

