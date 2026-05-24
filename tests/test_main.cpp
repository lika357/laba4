#include <iostream>

#include "assert.hpp"
#include "tests.hpp"

int main()
{

    std::cout << "true " << get_true_tests() << "\n";
    std::cout << "false " << get_failed_tests() << "\n";

    return get_failed_tests();
}