#pragma once
#include "dynamic_array.hpp"
#include "exceptions.hpp"
#include "sequence.hpp"

template <class T>
class ArraySequence : public Sequence<T>
{
   private:
    DynamicArray<T> items;

   public:
    using value_type = T;
    using reference = T&;
    ArraySequence() : items{}
    {
    }
    template <size_t N>
    ArraySequence(T (&arr)[N]) : items{arr}
    {
    }
    ArraySequence(const ArraySequence<T>& other) : items{other.items}
    {
    }
    T GetFirst() const override
    {
        if (items.GetSize() == 0)
        {
            throw IndexOutOfRange{0, items.GetSize()};
        }
        return items.Get(0);
    }
    T GetLast() const override
    {
        if (items.GetSize() == 0)
        {
            throw IndexOutOfRange{0, items.GetSize()};
        }
        return items.Get(items.GetSize() - 1);
    }
    T Get(size_t index) const override
    {
        if (index >= items.GetSize())
        {
            throw IndexOutOfRange{index, items.GetSize()};
        }
        return items.Get(index);
    }
    size_t GetLength() const override
    {
        return items.GetSize();
    }
    Sequence<T>* Append(T item) override
    {
        items.Resize(items.GetSize() + 1);
        items.Set(items.GetSize() - 1, item);
        return this;
    }
    Sequence<T>* Prepend(T item) override
    {
        size_t oldSize = items.GetSize();
        items.Resize(oldSize + 1);
        for (size_t i = oldSize; i > 0; i--)
        {
            items.Set(i, items.Get(i - 1));
        }
        items.Set(0, item);
        return this;
    }
    Sequence<T>* InsertAt(T item, size_t index) override
    {
        if (index > items.GetSize())
        {
            throw IndexOutOfRange{index, items.GetSize()};
        }
        size_t oldSize = items.GetSize();
        items.Resize(oldSize + 1);
        for (size_t i = oldSize; i > index; i--)
        {
            items.Set(i, items.Get(i - 1));
        }
        items.Set(index, item);
        return this;
    }
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override
    {
        if (startIndex > endIndex || endIndex >= items.GetSize())
        {
            throw InvalidArgument{};
        }
        ArraySequence<T>* result = new ArraySequence<T>();
        for (size_t i = startIndex; i <= endIndex; i++)
        {
            result->Append(items.Get(i));
        }
        return result;
    }
    Sequence<T>* Concat(Sequence<T>* other) override
    {
        if (other == nullptr)
        {
            throw NullPointer{};
        }
        for (size_t i = 0; i < other->GetLength(); i++)
        {
            Append(other->Get(i));
        }
        return this;
    }
    T& operator[](size_t index)
    {
        if (index >= items.GetSize())
        {
            throw IndexOutOfRange{index, items.GetSize()};
        }
        return items[index];
    }

    const T& operator[](size_t index) const
    {
        if (index >= items.GetSize())
        {
            throw IndexOutOfRange{index, items.GetSize()};
        }
        return items[index];
    }
    void Resize(size_t newSize) override
    {
        items.Resize(newSize);
    }
    ArraySequence<T>& operator=(const ArraySequence<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }
        items = other.items;
        return *this;
    }
    void PushBack(const T& item)
    {
        this->Append(item);
    }

    void PushFront(const T& item)
    {
        this->Prepend(item);
    }

    void PopBack()
    {
        if (this->GetLength() == 0)
        {
            throw InvalidArgument{};
        }
        this->Resize(this->GetLength() - 1);
    }
    void PopFront()
    {
        if (this->GetLength() == 0)
        {
            throw InvalidArgument{};
        }
        for (size_t i = 0; i < this->GetLength() - 1; i++)
        {
            (*this)[i] = (*this)[i + 1];
        }
        this->Resize(this->GetLength() - 1);
    }
    T& Back()
    {
        if (this->GetLength() == 0)
        {
            throw InvalidArgument{};
        }
        return (*this)[this->GetLength() - 1];
    }

    T& Front()
    {
        if (this->GetLength() == 0)
        {
            throw InvalidArgument{};
        }
        return (*this)[0];
    }
};