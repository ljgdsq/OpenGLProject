#include "../GLEnvHeader.h"

class GLEnvInfo
{
private:
    GLEnvInfo(){}
public:
   
    int GetMaxVertexAttribCount() {
        int count;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &count);
        return count;
    }


};