#pragma once
#include "exceptions.hpp"
#include "linked_list.hpp"
#include "sequence.hpp"

template <class T>
class ListSequence : public Sequence<T>
{
   private:
    LinkedList<T> items;

   public:
    using value_type = T;
    using reference = T&;
    typename LinkedList<T>::iterator begin()
    {
        return items.begin();
    }
    typename LinkedList<T>::iterator end()
    {
        return items.end();
    }
    ListSequence() : items{}
    {
    }
    template <size_t N>
    ListSequence(T (&arr)[N]) : items{arr}
    {
    }
    ListSequence(const ListSequence<T>& other) : items{other.items}
    {
    }
    T GetFirst() const override
    {
        if (items.GetLength() == 0)
        {
            throw IndexOutOfRange{0, items.GetLength()};
        }
        return items.GetFirst();
    }
    T GetLast() const override
    {
        if (items.GetLength() == 0)
        {
            throw IndexOutOfRange{0, items.GetLength()};
        }
        return items.GetLast();
    }
    T Get(size_t index) const override
    {
        if (index >= items.GetLength())
        {
            throw IndexOutOfRange{index, items.GetLength()};
        }
        return items.Get(index);
    }
    size_t GetLength() const override
    {
        return items.GetLength();
    }
    Sequence<T>* Append(T item) override
    {
        items.Append(item);
        return this;
    }
    Sequence<T>* Prepend(T item) override
    {
        items.Prepend(item);
        return this;
    }
    Sequence<T>* InsertAt(T item, size_t index) override
    {
        items.InsertAt(item, index);
        return this;
    }
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) const override
    {
        if (startIndex > endIndex || endIndex >= items.GetLength())
        {
            throw InvalidArgument{};
        }
        ListSequence<T>* result = new ListSequence<T>();
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
    void Resize(size_t newSize) override
    {
        if (newSize == items.GetLength()) return;

        while (items.GetLength() > newSize)
        {
            LinkedList<T> temp;
            for (size_t i = 0; i < items.GetLength() - 1; i++)
            {
                temp.Append(items.Get(i));
            }
            items = temp;
        }
        while (items.GetLength() < newSize)
        {
            items.Append(T{});
        }
    }
    T& operator[](size_t index)
    {
        return items.GetRef(index);
    }

    const T& operator[](size_t index) const
    {
        return items.GetRef(index);
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
        items.PopFront();
    }

    T& Back()
    {
        return items.GetLastRef();
    }

    T& Front()
    {
        return items.GetFirstRef();
    }
};