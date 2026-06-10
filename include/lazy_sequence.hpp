#pragma once
#include "array_sequence.hpp"
#include "size.hpp"
#include "exceptions.hpp"

template <typename T>
class LazySequence
{
   private:
    ArraySequence<T> cache;                        
    T (*generator)(const ArraySequence<T>&);        
    bool isInfinite;                                 

   public:
  
    LazySequence() : generator(nullptr), isInfinite(false) {}

    Size GetLength() const
    {
        if (isInfinite)
            return Size::Infinite();
        else
            return Size(cache.GetLength());
    }
};