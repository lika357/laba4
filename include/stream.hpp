#pragma once
#include <cstddef>
#include <cstdio>
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
    FILE* file;
    size_t position = 0;

   public:
    FileStream(const std::string& filename)
    {
        file = fopen(filename.c_str(), "r");
    }
    ~FileStream()
    {
        if (file)
        {
            fclose(file);
        }
    }

    T Read() override
    {
        T value;
        if (fscanf(file, "%d", &value) == 1)
        {
            position++;
            return value;
        }
        throw std::runtime_error("End of file");
    }

    bool IsEnd() const override
    {
        return feof(file);
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
    FILE* file;
    size_t position = 0;

   public:
    FileWriteStream(const std::string& filename)
    {
        file = fopen(filename.c_str(), "w");
    }

    ~FileWriteStream()
    {
        if (file)
        {
            fclose(file);
        }
    }

    void Write(const T& value)
    {
        fprintf(file, "%d ", value);
        position++;
    }

    size_t GetPosition() const
    {
        return position;
    }
};