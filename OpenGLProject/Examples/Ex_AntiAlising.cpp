#include "Ex_AntiAlising.h"
#include "../Shape/Cube.h"
#include "../Base/ProjetConfig.hpp"
RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_AntiAlising)

void Ex_AntiAlising::InitData()
{
    winSize = ProjectConfig::GetInstance()->GetWindowSize();
    int samples = 4;
    cube = new class Cube();
    cube->SetColor(glm::vec3(0.1,1.0f,0.1f));

    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, winSize.x, winSize.y, GL_TRUE);

    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples,GL_DEPTH24_STENCIL8, winSize.x, winSize.y);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        LogUtil::GetInstance()->Error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    int width = winSize.x;
    int height = winSize.y;
    //glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampledFBO);
    //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void Ex_AntiAlising::Draw()
{
    cube->Draw();
}