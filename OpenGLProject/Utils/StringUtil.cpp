#include "StringUtil.h"

template<class T>
std::string toString(T value)
{
    std::stringstream ssm;
    ssm << value;
    return ssm.str();
}


template<>
std::string toString(const char* value)
{
    return std::string(value);
}

template<>
std::string toString(std::string value)
{
    return value;
}
template<>
std::string toString(glm::vec3 value)
{
    std::stringstream ssm;
    ssm << "vec3{x=";
    ssm << value.x;
    ssm << ",y=";
    ssm << value.y;
    ssm << ",z=";
    ssm << value.z;
    ssm << "}";
    return ssm.str();
}
