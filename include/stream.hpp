#pragma once

#include <cstddef>
#include <cstdio>
#include <string>

#include "exceptions.hpp"
#include "lazy_sequence.hpp"

template <typename T>
class Stream
{
   public:
    virtual ~Stream() = default;
    virtual size_t GetPosition() const = 0;
};

template <typename T>
class ReadStream : public Stream<T>
{
   public:
    virtual T Read() = 0;
    virtual bool IsEnd() const = 0;
};

template <typename T>
class WriteStream : public Stream<T>
{
   public:
    virtual void Write(const T& value) = 0;
};

template <typename T>
class SequenceStream : public ReadStream<T>
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
class FileReadStream : public ReadStream<T>
{
   private:
    FILE* file;
    size_t position = 0;

   public:
    FileReadStream(const std::string& filename)
    {
        file = fopen(filename.c_str(), "r");
    }

    ~FileReadStream()
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
        throw EndOfStream();
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
class FileWriteStream : public WriteStream<T>
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

    void Write(const T& value) override
    {
        fprintf(file, "%d ", value);
        position++;
    }

    size_t GetPosition() const override
    {
        return position;
    }
};