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

void test_lazy_get_finite()
{
    int items[] = {10, 20, 30};
    LazySequence<int> lazy(items, 3);

    assert_func(lazy.Get(0) == 10);
    assert_func(lazy.Get(1) == 20);
    assert_func(lazy.Get(2) == 30);
}

void test_lazy_get_infinite()
{
    int initial[] = {3};
    LazySequence<int> lazy(doubler, initial, 1);

    assert_func(lazy.Get(0) == 3);
    assert_func(lazy.Get(1) == 6);
    assert_func(lazy.Get(2) == 12);
    assert_func(lazy.Get(3) == 24);
}

void test_lazy_get_out_of_range()
{
    int items[] = {1, 2, 3};
    LazySequence<int> lazy(items, 3);

    bool caught = false;
    try
    {
        lazy.Get(5);
    }
    catch (const IndexOutOfRange&)
    {
        caught = true;
    }
    assert_func(caught);
}

void test_lazy_get_first_finite()
{
    int items[] = {10, 20, 30};
    LazySequence<int> lazy(items, 3);

    assert_func(lazy.GetFirst() == 10);
}

void test_lazy_get_first_infinite()
{
    int initial[] = {7};
    LazySequence<int> lazy(doubler, initial, 1);

    assert_func(lazy.GetFirst() == 7);
}
void test_lazy_get_first_empty()
{
    LazySequence<int> lazy;

    bool caught = false;
    try
    {
        lazy.GetFirst();
    }
    catch (const InvalidArgument&)
    {
        caught = true;
    }
    assert_func(caught);
}
void test_lazy_get_last_finite()
{
    int items[] = {10, 20, 30};
    LazySequence<int> lazy(items, 3);

    assert_func(lazy.GetLast() == 30);
}

void test_lazy_get_last_infinite()
{
    int initial[] = {5};
    LazySequence<int> lazy(doubler, initial, 1);

    bool caught = false;
    try
    {
        lazy.GetLast();
    }
    catch (const InvalidArgument&)
    {
        caught = true;
    }
    assert_func(caught);
}

void test_lazy_get_last_empty()
{
    LazySequence<int> lazy;

    bool caught = false;
    try
    {
        lazy.GetLast();
    }
    catch (const InvalidArgument&)
    {
        caught = true;
    }
    assert_func(caught);
}

void test_lazy_materialized_count_finite()
{
    int items[] = {5, 10, 15};
    LazySequence<int> lazy(items, 3);

    assert_func(lazy.GetMaterializedCount() == 3);
}

void test_lazy_materialized_count_infinite()
{
    int initial[] = {7};
    LazySequence<int> lazy(doubler, initial, 1);

    assert_func(lazy.GetMaterializedCount() == 1);
    lazy.Get(2);
    assert_func(lazy.GetMaterializedCount() == 3);
}

void test_lazy_subsequence_finite()
{
    int items[] = {10, 20, 30, 40, 50};
    LazySequence<int> lazy(items, 5);

    LazySequence<int>* sub = lazy.GetSubsequence(1, 3);
    assert_func(sub->GetLength().GetValue() == 3);
    assert_func(sub->Get(0) == 20);
    assert_func(sub->Get(1) == 30);
    assert_func(sub->Get(2) == 40);
}

void test_lazy_subsequence_infinite()
{
    int initial[] = {3};
    LazySequence<int> lazy(doubler, initial, 1);

    LazySequence<int>* sub = lazy.GetSubsequence(2, 4);
    assert_func(sub->GetLength().GetValue() == 3);
    assert_func(sub->Get(0) == 12);
    assert_func(sub->Get(1) == 24);
    assert_func(sub->Get(2) == 48);
}
void test_lazy_append()
{
    int items[] = {10, 20};
    LazySequence<int> lazy(items, 2);

    lazy.Append(30);

    assert_func(lazy.GetLength().GetValue() == 3);
    assert_func(lazy.GetLast() == 30);
}
void test_lazy_prepend()
{
    int items[] = {20, 30};
    LazySequence<int> lazy(items, 2);

    lazy.Prepend(10);

    assert_func(lazy.GetLength().GetValue() == 3);
    assert_func(lazy.GetFirst() == 10);
}
void test_lazy_insert_at()
{
    int items[] = {10, 30};
    LazySequence<int> lazy(items, 2);

    lazy.InsertAt(20, 1);

    assert_func(lazy.GetLength().GetValue() == 3);
    assert_func(lazy.Get(0) == 10);
    assert_func(lazy.Get(1) == 20);
    assert_func(lazy.Get(2) == 30);
}
void test_lazy_concat()
{
    int items1[] = {1, 2};
    int items2[] = {3, 4};
    LazySequence<int> lazy1(items1, 2);
    LazySequence<int> lazy2(items2, 2);

    lazy1.Concat(&lazy2);

    assert_func(lazy1.GetLength().GetValue() == 4);
    assert_func(lazy1.Get(0) == 1);
    assert_func(lazy1.Get(3) == 4);
}