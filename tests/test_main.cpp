#include <iostream>

#include "assert.hpp"
#include "tests.hpp"

int main()
{
    test_size_finite();
    test_size_infinite();

    std::cout << "true " << get_true_tests() << "\n";
    std::cout << "false " << get_failed_tests() << "\n";

    return get_failed_tests();
}