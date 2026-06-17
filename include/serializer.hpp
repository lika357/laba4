#pragma once
#include <string>

template <typename T>
class Serializer
{
   public:
    virtual ~Serializer() = default;
    virtual std::string Serialize(const T& value) = 0;
    virtual T Deserialize(const std::string& data) = 0;
};

class IntSerializer : public Serializer<int>
{
   public:
    std::string Serialize(const int& value) override
    {
        return std::to_string(value);
    }
    int Deserialize(const std::string& data) override
    {
        return std::stoi(data);
    }
};

class DoubleSerializer : public Serializer<double>
{
   public:
    std::string Serialize(const double& value) override
    {
        return std::to_string(value);
    }
    double Deserialize(const std::string& data) override
    {
        return std::stod(data);
    }
};

class CharSerializer : public Serializer<char>
{
   public:
    std::string Serialize(const char& value) override
    {
        return std::string(1, value);
    }
    char Deserialize(const std::string& data) override
    {
        return data[0];
    }
};

class StringSerializer : public Serializer<std::string>
{
   public:
    std::string Serialize(const std::string& value) override
    {
        return value;
    }
    std::string Deserialize(const std::string& data) override
    {
        return data;
    }
};