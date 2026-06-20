#pragma once
#include <cstddef>
#include <cstdio>
#include <string>

#include "exceptions.hpp"
#include "lazy_sequence.hpp"
#include "serializer.hpp"

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
    Serializer<T>* serializer;
    bool ownSerializer;
    size_t position = 0;

   public:
    FileReadStream(const std::string& filename) : ownSerializer(true)
    {
        file = fopen(filename.c_str(), "r");
        if (!file)
        {
            throw FileOpenError();
        }
        serializer = new IntSerializer();
    }
    FileReadStream(const std::string& filename, Serializer<T>* ser)
        : serializer(ser), ownSerializer(false)
    {
        file = fopen(filename.c_str(), "r");
        if (!file)
        {
            throw FileOpenError();
        }
    }

    ~FileReadStream()
    {
        if (file)
        {
            fclose(file);
        }
        if (ownSerializer)
        {
            delete serializer;
        }
    }

    T Read() override
    {
        char buffer[256];
        if (fscanf(file, "%255s", buffer) == 1)
        {
            position++;
            return serializer->Deserialize(buffer);
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
    Serializer<T>* serializer;
    bool ownSerializer;
    size_t position = 0;

   public:
    FileWriteStream(const std::string& filename) : ownSerializer(true)
    {
        file = fopen(filename.c_str(), "w");
        if (!file)
        {
            throw FileOpenError();
        }
        serializer = new IntSerializer();
    }

    FileWriteStream(const std::string& filename, Serializer<T>* ser)
        : serializer(ser), ownSerializer(false)
    {
        file = fopen(filename.c_str(), "w");
        if (!file)
        {
            throw FileOpenError();
        }
    }

    ~FileWriteStream()
    {
        if (file)
        {
            fclose(file);
        }
        if (ownSerializer)
        {
            delete serializer;
        }
    }
    void Write(const T& value) override
    {
        std::string text = serializer->Serialize(value);
        int result = fprintf(file, "%s ", text.c_str());
        if (result < 0)
        {
            throw FileWriteError();
        }
        position++;
    }

    size_t GetPosition() const override
    {
        return position;
    }
};