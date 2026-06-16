#pragma once

#include "igenerator.hpp"
#include "sequence.hpp"

template <typename T>
class FibGenerator : public IGenerator<T>
{
   public:
    FibGenerator() : IGenerator<T>()
    {
    }

    T GetNext() override
    {
        size_t len = this->cache->GetLength();
        return this->cache->Get(len - 1) + this->cache->Get(len - 2);
    }
};

template <typename T>
class SquareGenerator : public IGenerator<T>
{
   public:
    SquareGenerator() : IGenerator<T>()
    {
    }

    T GetNext() override
    {
        size_t next = this->cache->GetLength() + 1;
        return next * next;
    }
};

template <typename T>
class DoubleGenerator : public IGenerator<T>
{
   public:
    DoubleGenerator() : IGenerator<T>()
    {
    }

    T GetNext() override
    {
        return this->cache->GetLast() * 2;
    }
};

template <typename T>
class FactorialGenerator : public IGenerator<T>
{
   public:
    FactorialGenerator() : IGenerator<T>()
    {
    }

    T GetNext() override
    {
        size_t len = this->cache->GetLength();
        return this->cache->GetLast() * (len + 1);
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
        : IGenerator<T>(), start(startVal), step(stepVal), limit(limitVal)
    {
    }

    T GetNext() override
    {
        if (first)
        {
            first = false;
            T last = this->cache->GetLast();
            return last + step;
        }
        T last = this->cache->GetLast();
        T next = last + step;
        return next;
    }

    bool HasNext() const override
    {
        if (this->cache->GetLength() == 0)
        {
            return true;
        }
        T last = this->cache->GetLast();
        return (last + step) <= limit;
    }
};