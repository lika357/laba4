#pragma once
#include <cstddef>

class Size
{
   private:
    bool infinite;
    size_t value;

   public:
    Size(size_t val) : infinite(false), value(val)
    {
    }

    static Size Infinite()
    {
        Size s(0);
        s.infinite = true;
        return s;
    }

    bool IsInfinite() const
    {
        return infinite;
    }

    size_t GetValue() const
    {
        return value;
    }
};