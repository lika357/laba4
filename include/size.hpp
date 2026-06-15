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

    Size operator+(const Size& other) const
    {
        if (infinite || other.infinite)
        {
            return Infinite();
        }
        return Size(value + other.value);
    }

    bool operator<(const Size& other) const
    {
        if (other.infinite)
        {
            return !infinite;
        }
        if (infinite)
        {
            return false;
        }
        return value < other.value;
    }

    bool operator==(const Size& other) const
    {
        if (infinite && other.infinite)
        {
            return true;
        }
        if (!infinite && !other.infinite)
        {
            return value == other.value;
        }
        return false;
    }

    bool operator!=(const Size& other) const
    {
        return !(*this == other);
    }
};