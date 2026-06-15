#pragma once
#include <exception>
#include <string>
#include <sstream>   

class Exceptions : public std::exception
{
   protected:
    std::string message;

   public:
    Exceptions(const std::string& msg) : message{msg}
    {
    }
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

inline std::string FormatIndexError(size_t index, size_t size)
{
    std::ostringstream ss;                                    
    ss << "Ошибка : индекс " << index                         
       << " вышел за границы " << size;                      
    return ss.str();                                           
}

class IndexOutOfRange : public Exceptions
{
   public:
    IndexOutOfRange(size_t index = 0, size_t size = 0)
        : Exceptions{FormatIndexError(index, size)}
    {
    }
};

class InvalidArgument : public Exceptions
{
   public:
    InvalidArgument() : Exceptions{"Ошибка : передан неверный аргумент"}
    {
    }
};

class NullPointer : public Exceptions
{
   public:
    NullPointer() : Exceptions{"Ошибка : передан пустой указатель"}
    {
    }
};