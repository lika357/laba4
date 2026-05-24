#pragma once
#include <exception>
#include <string>

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

class IndexOutOfRange : public Exceptions
{
   public:
    IndexOutOfRange(size_t index = 0, size_t size = 0)
        : Exceptions{"Ошибка : индекс " + std::to_string(index) + " вышел за границы " +
                     std::to_string(size)}
    {
    }
};

class InvalidArgument : public Exceptions
{
   public:
    InvalidArgument() : Exceptions{"Ошибка : передан неверный аргумент "}
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