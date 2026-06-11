#pragma once
#include "array_sequence.hpp"

inline int fibGenerator(const ArraySequence<int>& cache)
{
    size_t len = cache.GetLength();
    return cache[len - 1] + cache[len - 2];
}

inline int squareGenerator(const ArraySequence<int>& cache)
{
    size_t next = cache.GetLength() + 1;
    return next * next;
}

inline int doubleGenerator(const ArraySequence<int>& cache)
{
    return cache.GetLast() * 2;
}

inline int factorialGenerator(const ArraySequence<int>& cache)
{
    size_t len = cache.GetLength();
    return cache.GetLast() * (len + 1);
}