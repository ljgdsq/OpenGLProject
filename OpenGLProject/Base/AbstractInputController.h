#pragma once
class AbstractInputController
{
    //TODO 
public:
    virtual void ProcessKeyBoard(void* object) = 0;
    virtual void ProcessMouseMove(void* object) = 0;
    virtual void ProcessMouseScroll(void* object) = 0;
};

