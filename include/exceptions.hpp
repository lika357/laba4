#pragma once

#include <exception>
#include <sstream>
#include <string>

std::string FormatIndexError(size_t index, size_t size);

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
    IndexOutOfRange(size_t index = 0, size_t size = 0) : Exceptions{FormatIndexError(index, size)}
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

class EndOfStream : public Exceptions
{
   public:
    EndOfStream() : Exceptions{"Ошибка : достигнут конец потока"}
    {
    }
};
class FileOpenError : public Exceptions
{
   public:
    FileOpenError() : Exceptions{"Ошибка : не удалось открыть файл"}
    {
    }
};
class FileWriteError : public Exceptions
{
   public:
    FileWriteError() : Exceptions{"Ошибка : не удалось записать в файл"}
    {
    }
};