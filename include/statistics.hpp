#pragma once
#include "stream.hpp"

template <typename T>
class Statistics
{
   private:
    size_t count = 0;
    T sum = 0;
    T min = 0;
    T max = 0;

   public:
    void Add(T value)
    {
        if (count == 0)
        {
            min = value;
            max = value;
        }
        count++;
        sum += value;
        if (value < min){
            min = value;
        }
        if (value > max){
            max = value;
        }
    }

    size_t GetCount() const
    {
        return count;
    }

    T GetSum() const
    {
        return sum;
    }

    T GetMin() const
    {
        return min;
    }

    T GetMax() const
    {
        return max;
    }

    double GetAverage() const
    {
        if (count == 0){
            return 0;
        }
        return static_cast<double>(sum) / count;
    }

    void Reset()
    {
        count = 0;
        sum = 0;
        min = 0;
        max = 0;
    }
};