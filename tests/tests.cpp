#include "assert.hpp"
#include "size.hpp"

void test_size_finite()
{
    Size s(5);
    assert_func(!s.IsInfinite());
    assert_func(s.GetValue() == 5);
}

void test_size_infinite()
{
    Size s = Size::Infinite();
    assert_func(s.IsInfinite());
}