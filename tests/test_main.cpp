#include <iostream>

#include "assert.hpp"
#include "tests.hpp"

int main()
{
    test_size_finite();
    test_size_infinite();
    test_lazy_empty();
    test_lazy_from_array();
    test_lazy_from_sequence();
    test_lazy_with_generator();
    test_lazy_copy();
    test_lazy_get_finite();
    test_lazy_get_infinite();
    test_lazy_get_out_of_range();
    test_lazy_get_first_finite();
    test_lazy_get_first_infinite();
    test_lazy_get_first_empty();
    test_lazy_get_last_finite();
    test_lazy_get_last_infinite();
    test_lazy_get_last_empty();
    test_lazy_materialized_count_finite();
    test_lazy_materialized_count_infinite();
    test_lazy_subsequence_finite();
    test_lazy_subsequence_infinite();
    test_lazy_append();
    test_lazy_prepend();
    test_lazy_insert_at();
    test_lazy_concat();
    test_lazy_map();
    test_lazy_where();
    test_lazy_reduce();
    test_stream_read_finite();
    test_stream_read_infinite();
    test_fibonacci();
    test_squares();
    test_doubler();
    test_factorial();
    test_file_write_read();
    test_file_open_error();
    test_file_write_position();
    test_file_read_position();
    test_file_read_with_serializer();
    test_file_write_default_serializer();

    std::cout << "true " << get_true_tests() << "\n";
    std::cout << "false " << get_failed_tests() << "\n";

    return get_failed_tests();
}