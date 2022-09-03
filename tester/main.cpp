#include <iostream>
#include <iomanip>
#include <time.h>
#include <set>

# define VECTOR  "vector"
# define STACK   "stack"
# define MAP     "map"
# define SET     "set"
# define EXTRA   "extra"

void is_integral_test(void);
void enable_if_test(void);
void reverse_comp_test(void);

void vector_test(void);
void stack_test(void);
void map_test(void);
void set_test(void);

int print_usage(char **argv) {
    std::cerr << "Usage: " << argv[0] << " [cycles = 1] [containers = all]" << std::endl;
    std::cerr << "  cycles: the number of test runs" << std::endl;
    std::cerr << "  containers: "VECTOR"/"STACK"/"MAP"/"SET << std::endl;
    return 1;
}

int main(int argc, char **argv) {

    bool _set = false;
    bool _map = false;
    bool _stack = false;
    bool _vector = false;
    bool _extra = false;

    int cycles = argc > 1 ? std::atoi(argv[1]) : 1;
    if (cycles < 1) {
        return print_usage(argv);
    }

    if (argc > 2) {
        for (int i = 2; i < argc; ++i) {
            std::string str = argv[i];
            if (str == VECTOR) {
                _vector = true;
            } else if (str == STACK) {
                _stack = true;
            } else if (str == SET) {
                _set = true;
            } else if (str == MAP) {
                _map = true;
            } else if (str == EXTRA) {
                _extra = true;
            } else {
                return print_usage(argv);
            }
        }
    } else {
        _set = true;
        _map = true;
        _stack = true;
        _vector = true;
        _extra = true;
    }

    if (_extra) {
        enable_if_test();
        reverse_comp_test();
        is_integral_test();
    }

    clock_t start_time = clock();
    for (int i = 0; i < cycles; i++) {
        if (_vector) vector_test();
        if (_stack) stack_test();
        if (_map) map_test();
        if (_set) set_test();
    }
    clock_t end_time = clock();

    double total = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    double avg = total / cycles;
    std::cerr << std::setw(13) << std::left << argv[0] << "-> ";
    std::cerr << "cycles: " << cycles << ", ";
    std::cerr << "total: " << total << " sec" << ", ";
    std::cerr << "avg: "   << avg   << " sec" << std::endl;
    return 0;
}