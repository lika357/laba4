#pragma once
#include "sequence.hpp"

template <typename T>
class IGenerator
{
   public:
    virtual ~IGenerator() = default;
    virtual T GetNext(const Sequence<T>& cache) = 0;
};