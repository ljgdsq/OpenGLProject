#include "Ex_FrameBuffer.h"
#include "../Shape/Cube.h"
#include "../Shape/Plane.h"
#include "../Base/ProjetConfig.hpp"
#include "../Render/ScreenRenderer.h"
RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_FrameBuffer)

void Ex_FrameBuffer::InitData()
{
    plane = new Plane("wood.png");
    cube1 = new Cube("container2.png");
   
    winSize = ProjectConfig::GetInstance()->GetWindowSize();
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, winSize.x, winSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
   
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, winSize.x, winSize.y);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
       LogUtil::GetInstance()->Error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

   
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    screen = new ScreenRenderer();
    screen->InitShader();
    screen->SetTexture(textureColorbuffer);
  
}

void Ex_FrameBuffer::Draw()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    plane->Draw();
    cube1->Draw();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    
    screen->Draw();


}