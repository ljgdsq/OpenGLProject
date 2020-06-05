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
        x = 0;
        y = 0;
        z = 0;
    }

    void operator = (glm::vec3& output)
    {
        x = output.x;
        y = output.y;
        z = output.z;
    }
    Vec3 operator - (Vec3 output)
    {
        x -= output.x;
        y -= output.y;
        z -= output.z;
        return *this;
    }

};