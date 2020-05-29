#pragma once
#include <string>
#include <sstream>


template<class T>
std::string toString(T value)
{
    std::stringstream ssm;
    ssm << value;
    return ssm.str();
}

template<>
std::string toString(const char*value)
{
    return std::string(value);
}

template<>
std::string toString(std::string value)
{
    return value;
}