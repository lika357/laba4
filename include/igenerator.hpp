#pragma once
#include "sequence.hpp"

template <typename T>
class IGenerator
{
   protected:
    Sequence<T>* cache;

   public:
    virtual ~IGenerator() = default;

    void SetCache(Sequence<T>* c)
    {
        cache = c;
    }

    virtual T GetNext() = 0;

    virtual bool HasNext() const
    {
        return true;
    }
};