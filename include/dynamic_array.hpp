#pragma once
#include <cstddef>
#include <cstring>

#include "exceptions.hpp"

template <typename T>
class DynamicArray
{
   private:
    T* data{nullptr};
    size_t size{0};

   public:
    DynamicArray()
    {
    }

    DynamicArray(size_t count) : data{new T[count]}, size{count}
    {
    }

    template <size_t N>
    DynamicArray(T (&items)[N]) : DynamicArray{N}
    {
        std::memcpy(data, items, N * sizeof(T));
    }
    DynamicArray(const DynamicArray<T>& other) : DynamicArray{other.size}
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    ~DynamicArray()
    {
        delete[] data;
    }
    DynamicArray<T>& operator=(const DynamicArray<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] data;
        size = other.size;
        data = new T[size];
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }
    T& operator[](size_t index)
    {
        if (index >= size)
        {
            throw IndexOutOfRange{index, size};
        }
        return data[index];
    }

    const T& operator[](size_t index) const
    {
        if (index >= size)
        {
            throw IndexOutOfRange{index, size};
        }
        return data[index];
    }
    T Get(size_t index) const
    {
        if (index >= size)
        {
            throw IndexOutOfRange{index, size};
        }
        return data[index];
    }
    size_t GetSize() const
    {
        return size;
    }
    void Set(size_t index, T value)
    {
        if (index >= size)
        {
            throw IndexOutOfRange{index, size};
        }
        data[index] = value;
    }
    void Resize(size_t newSize)
    {
        T* newData = new T[newSize];
        size_t copyLen;
        if (newSize < size)
        {
            copyLen = newSize;
        }
        else
        {
            copyLen = size;
        }
        for (size_t i = 0; i < copyLen; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }
};