#include "exceptions.hpp"

#include <sstream>

std::string FormatIndexError(size_t index, size_t size)
{
    std::ostringstream ss;
    ss << "Ошибка : индекс " << index << " вышел за границы " << size;
    return ss.str();
}