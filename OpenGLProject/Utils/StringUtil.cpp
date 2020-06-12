#include "StringUtil.h"

#define PUT_STRINGSTREAM(value)   \
    std::stringstream ssm;       \
 ssm << value;                \
 return ssm.str();


std::string toString(const char* value)
{
    PUT_STRINGSTREAM(value)
}


std::string toString(std::string value)
{
    return value;
}
std::string toString(int value)
{
    PUT_STRINGSTREAM(value)
}
std::string toString(float value)
{
    PUT_STRINGSTREAM(value)
}
std::string toString(double value)
{
    PUT_STRINGSTREAM(value)
}
std::string toString(bool value)
{
    PUT_STRINGSTREAM(value)
}

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
