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

    size_t GetMaterializedCount() const
    {
        return cache.GetLength();
    }

    LazySequence<T>* GetSubsequence(size_t startIndex, size_t endIndex)
    {
        if (startIndex > endIndex)
        {
            throw InvalidArgument();
        }
        if (!isInfinite && endIndex >= cache.GetLength())
        {
            throw IndexOutOfRange(endIndex, cache.GetLength());
        }
        materializeUpTo(endIndex);

        LazySequence<T>* result = new LazySequence<T>();
        for (size_t i = startIndex; i <= endIndex; i++)
        {
            result->cache.Append(cache[i]);
        }
        return result;
    }
    LazySequence<T>* Append(T item)
    {
        if (isInfinite)
        {
            throw InvalidArgument();
        }
        cache.Append(item);
        return this;
    }
    LazySequence<T>* Prepend(T item)
    {
        cache.Prepend(item);
        return this;
    }
    LazySequence<T>* InsertAt(T item, size_t index)
    {
        if (index > cache.GetLength())
        {
            throw IndexOutOfRange(index, cache.GetLength());
        }
        cache.InsertAt(item, index);
        return this;
    }
    LazySequence<T>* Concat(LazySequence<T>* other)
    {
        if (other == nullptr)
        {
            throw NullPointer();
        }
        if (isInfinite)
        {
            throw InvalidArgument();
        }
        for (size_t i = 0; i < other->cache.GetLength(); i++)
        {
            cache.Append(other->cache[i]);
        }
        return this;
    }
    template <typename U>
    LazySequence<U>* Map(U (*func)(T), size_t count)
    {
        if (func == nullptr)
        {
            throw NullPointer();
        }
        LazySequence<U>* result = new LazySequence<U>();
        for (size_t i = 0; i < count; i++)
        {
            result->cache.Append(func(this->Get(i)));
        }
        return result;
    }
    LazySequence<T>* Where(bool (*pred)(T), size_t count)
    {
        if (pred == nullptr)
        {
            throw NullPointer();
        }
        LazySequence<T>* result = new LazySequence<T>();
        for (size_t i = 0; i < count; i++)
        {
            T item = this->Get(i);
            if (pred(item))
            {
                result->cache.Append(item);
            }
        }
        return result;
    }
    template <typename U>
    U Reduce(U (*func)(U, T), U initial, size_t count)
    {
        if (func == nullptr)
        {
            throw NullPointer();
        }
        U result = initial;
        for (size_t i = 0; i < count; i++)
        {
            result = func(result, this->Get(i));
        }
        return result;
    }
};