#pragma once
#include <cstddef>
#include <fstream>
#include <string>
#include "lazy_sequence.hpp"

template <typename T>
class Stream
{
public:
    virtual ~Stream() = default;
    virtual T Read() = 0;
    virtual bool IsEnd() const = 0;
    virtual size_t GetPosition() const = 0;
};

template <typename T>
class SequenceStream : public Stream<T>
{
private:
    LazySequence<T>& source;
    size_t position = 0;

public:
    SequenceStream(LazySequence<T>& seq) : source(seq)
    {
    }

    T Read() override
    {
        T value = source.Get(position);
        position++;
        return value;
    }

    bool IsEnd() const override
    {
        return false;
    }

    size_t GetPosition() const override
    {
        return position;
    }
};

template <typename T>
class FileStream : public Stream<T>
{
private:
    std::ifstream file;
    size_t position = 0;

public:
    FileStream(const std::string& filename)
    {
        file.open(filename);
    }

    T Read() override
    {
        T value;
        if (file >> value)
        {
            position++;
            return value;
        }
        throw std::runtime_error("End of file");
    }

    bool IsEnd() const override
    {
        return file.eof();
    }

    size_t GetPosition() const override
    {
        return position;
    }
};

template <typename T>
class FileWriteStream
{
private:
    std::ofstream file;
    size_t position = 0;

public:
    FileWriteStream(const std::string& filename)
    {
        file.open(filename);
    }

    void Write(const T& value)
    {
        file << value << " ";
        position++;
    }

    size_t GetPosition() const
    {
        return position;
    }
};