#include "rbt.hpp"
#include "rbt_visualizer.hpp"

int main() {

    {
        ft::rbt<int> tree;
        for (int i = 1; i < 10; i++) {
            tree.insert(i);
        }
        tree.erase(6);
        ft::rbt_visualizer rbv(tree);
    }

    {
        ft::rbt<int> tree;
        for (int i = -2; i < 10; i++) {
            tree.insert(i);
        }
        ft::rbt_visualizer rbv(tree);
    }

    {
        ft::rbt<int> tree;
        for (int i = 1; i < 20; i++) {
            tree.insert(rand() % 100);
        }
        tree.erase(65);
        ft::rbt_visualizer rbv(tree);
    }

    return 0;
}