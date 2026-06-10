#pragma once
#include "array_sequence.hpp"
#include "exceptions.hpp"
#include "size.hpp"

template <typename T>
class LazySequence
{
   private:
    ArraySequence<T> cache;
    T (*generator)(const ArraySequence<T>&);
    bool isInfinite;
    void materializeUpTo(size_t index)
    {
        if (index < cache.GetLength())
        {
            return;
        }

        if (!isInfinite)
        {
            throw IndexOutOfRange(index, cache.GetLength());
        }

        for (size_t i = cache.GetLength(); i <= index; i++)
        {
            T next = generator(cache);
            cache.Append(next);
        }
    }

   public:
    LazySequence() : generator(nullptr), isInfinite(false)
    {
    }

    LazySequence(T* items, size_t count) : generator(nullptr), isInfinite(false)
    {
        if (items == nullptr)
        {
            throw NullPointer();
        }
        for (size_t i = 0; i < count; i++)
        {
            cache.Append(items[i]);
        }
    }

    LazySequence(Sequence<T>* seq) : generator(nullptr), isInfinite(false)
    {
        if (seq == nullptr)
        {
            throw NullPointer();
        }
        for (size_t i = 0; i < seq->GetLength(); i++)
        {
            cache.Append(seq->Get(i));
        }
    }

    LazySequence(T (*gen)(const ArraySequence<T>&), T* initialItems, size_t initialCount)
        : generator(gen), isInfinite(true)
    {
        if (initialItems == nullptr)
        {
            throw NullPointer();
        }
        if (initialCount == 0)
        {
            throw InvalidArgument();
        }
        for (size_t i = 0; i < initialCount; i++)
        {
            cache.Append(initialItems[i]);
        }
    }

    LazySequence(const LazySequence<T>& other)
        : cache(other.cache), generator(other.generator), isInfinite(other.isInfinite)
    {
    }
    T& operator[](size_t index)
    {
        if (index >= cache.GetLength())
        {
            materializeUpTo(index);
        }
        return cache[index];
    }

    Size GetLength() const
    {
        if (isInfinite)
        {
            return Size::Infinite();
        }
        else
        {
            return Size(cache.GetLength());
        }
    }
    T Get(size_t index)
    {
        if (index >= cache.GetLength()) materializeUpTo(index);
        return cache[index];
    }
    T GetFirst()
    {
        if (cache.GetLength() == 0)
        {
            throw InvalidArgument();
        }
        return cache[0];
    }
    T GetLast()
    {
        if (isInfinite)
        {
            throw InvalidArgument();
        }
        if (cache.GetLength() == 0)
        {
            throw InvalidArgument();
        }
        return cache[cache.GetLength() - 1];
    }
};