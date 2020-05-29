#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera 
{

public:
    // camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // euler Angles
    float yaw;
    float pitch;

    // camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
    bool inverseY;
public:
 
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
        front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        this->position = position;
        this->worldUp = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->inverseY = false;
        UpdateCamera();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
        front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
    {
        this->position = glm::vec3(posX, posY, posZ);
        this->worldUp = glm::vec3(upX, upY, upZ);
        this->yaw = yaw;
        this->pitch = pitch;
        this->inverseY = false;
        UpdateCamera();
    }
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }


    void ProcessKeyboard(Camera_Movement direction,float deltaTime)
    {
        float velocity = movementSpeed * deltaTime;
        if (direction==Camera_Movement::FORWARD)
        {
            position += front * velocity;
        }

        if (direction==Camera_Movement::BACKWARD)
        {
            position -= front * velocity;
        }

        if (direction==Camera_Movement::LEFT)
        {
            position -= right * velocity;
        }

        if (direction == Camera_Movement::RIGHT)
        {
            position += right * velocity;
        }

        if (direction == Camera_Movement::UP)
        {
            position += worldUp * velocity;
        }

        if (direction == Camera_Movement::DOWN)
        {
            position -= worldUp * velocity;
        }
    }

    void ProcessMouseMove(float x,float y,bool constrainPitch=true)
    {
        x *= mouseSensitivity;
        y *= mouseSensitivity;
        yaw += x;
        if (inverseY)
        {
            pitch += y;
        }
        else {
            pitch -= y;
        }

        if (constrainPitch)
        {
            if (pitch>89.0f)
            {
                pitch = 89.0f;
            }

            if (pitch<-89.0f)
            {
                pitch = 89.0f;
            }
        }
       // LogUtil::GetInstance()->Info(toString("pitch:")+toString(pitch) + " yaw:" + toString(yaw));
        UpdateCamera();
    }

    void ProcessMouseScroll(float yoffset)
    {
        zoom -= yoffset;
        if (zoom < 1.0f)
            zoom = 1.0f;
        if (zoom > 45.0f)
            zoom = 45.0f;
    }

private:
    void UpdateCamera()
    {
        glm::vec3 front_;
        front_.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front_.y = sin(glm::radians(pitch));
        front_.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(front_);

        right = glm::normalize(glm::cross(front, worldUp));  
        up = glm::normalize(glm::cross(right, front));
    }

};