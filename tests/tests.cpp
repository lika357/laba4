#include "assert.hpp"
#include "lazy_sequence.hpp"
#include "size.hpp"

int doubler(const ArraySequence<int>& cache)
{
    return cache.GetLast() * 2;
}

void test_lazy_empty()
{
    LazySequence<int> lazy;

    Size size = lazy.GetLength();
    assert_func(!size.IsInfinite());
    assert_func(size.GetValue() == 0);
}

void test_lazy_from_array()
{
    int items[] = {10, 20, 30};
    LazySequence<int> lazy(items, 3);

    Size size = lazy.GetLength();
    assert_func(!size.IsInfinite());
    assert_func(size.GetValue() == 3);
}

void test_lazy_from_sequence()
{
    int items[] = {5, 15, 25};
    ArraySequence<int> seq(items);
    LazySequence<int> lazy(&seq);

    Size size = lazy.GetLength();
    assert_func(!size.IsInfinite());
    assert_func(size.GetValue() == 3);
}

void test_lazy_with_generator()
{
    int initial[] = {3};
    LazySequence<int> lazy(doubler, initial, 1);

    Size size = lazy.GetLength();
    assert_func(size.IsInfinite());
}

void test_lazy_copy()
{
    int items[] = {1, 2, 3};
    LazySequence<int> original(items, 3);
    LazySequence<int> copy(original);

    Size size = copy.GetLength();
    assert_func(!size.IsInfinite());
    assert_func(size.GetValue() == 3);
}

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