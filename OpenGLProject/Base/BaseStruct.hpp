#pragma once
#include <glm/glm.hpp>
struct Size
{
    int x;
    int y;
    Size()
    {
        this->x = 0;
        this->y = 0;
    }
    Size(int x,int y)
    {
        this->x = x;
        this->y = y;
    }
};

struct Vec3
{
    float x;
    float y;
    float z;

    Vec3() {
        x = 0;
        y = 0;
        z = 0;
    }
    Vec3(float x,float y,float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

   Vec3& operator = (glm::vec3& output)
    {
        x = output.x;
        y = output.y;
        z = output.z;
        return *this;
    }

    Vec3 operator - (Vec3 output)
    {
        Vec3 ret;
        ret.x = x-output.x;
        ret.y = y-output.y;
        ret.z = z-output.z;
        return ret;
    }

};