#pragma once
#include "concepts.hpp"
#include "size.hpp"
#include "exceptions.hpp"
#include <functional>

template <template <typename> class Container, typename T>
    requires SequenceContainer<Container<T>>
class LazySequence
{
   private:
    Container<T> cache;
    std::function<T(const Container<T>&)> generator;
    bool isInfinite;

   public:
    LazySequence() : isInfinite(false) {}

    Size GetLength() const
    {
        if (isInfinite){
            return Size::Infinite();
        }
        else{
            return Size(cache.GetLength());
        }
    }
};