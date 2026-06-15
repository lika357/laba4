#pragma once
#include "igenerator.hpp"
#include "sequence.hpp"

template <typename T>
class FibGenerator : public IGenerator<T>
{
   public:
    T GetNext(const Sequence<T>& cache) override
    {
        size_t len = cache.GetLength();
        return cache.Get(len - 1) + cache.Get(len - 2);
    }
};

template <typename T>
class SquareGenerator : public IGenerator<T>
{
   public:
    T GetNext(const Sequence<T>& cache) override
    {
        size_t next = cache.GetLength() + 1;
        return next * next;
    }
};

template <typename T>
class DoubleGenerator : public IGenerator<T>
{
   public:
    T GetNext(const Sequence<T>& cache) override
    {
        return cache.GetLast() * 2;
    }
};

template <typename T>
class FactorialGenerator : public IGenerator<T>
{
   public:
    T GetNext(const Sequence<T>& cache) override
    {
        size_t len = cache.GetLength();
        return cache.GetLast() * (len + 1);
    }
};

template <typename T>
class CustomGenerator : public IGenerator<T>
{
   private:
    T start;    
    T step;     
    T limit;    
    bool first = true;  

   public:
    CustomGenerator(T startVal, T stepVal, T limitVal)
        : start(startVal), step(stepVal), limit(limitVal)
    {
    }

    T GetNext(const Sequence<T>& cache) override
    {
        if (first)
        {
            first = false;
            return start;
        }
        T last = cache.GetLast();
        T next = last + step;
        if (next > limit)
        {
            next = start;
        }
        return next;
    }
};