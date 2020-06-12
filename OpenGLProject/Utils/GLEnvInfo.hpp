#include "../GLEnvHeader.h"

class GLEnvInfo
{
private:
    GLEnvInfo(){}
public:
   
   static int GetMaxVertexAttribCount() {
        int count;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &count);
        return count;
    }

   static int GetMaxVertexUniformComponent()
    {
        int count;
        glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &count);
        return count;
    }

};