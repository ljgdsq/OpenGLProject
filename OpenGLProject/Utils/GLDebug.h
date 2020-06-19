#pragma once
#include "../Macro.h"
#include "glad/glad.h"

class GLDebug
{
private:
    NO_INSTANCE(GLDebug)
public:
    static GLenum glCheckError_(const char* file, int line);
};
#define glCheckError() GLDebug::glCheckError_(__FILE__, __LINE__); 
