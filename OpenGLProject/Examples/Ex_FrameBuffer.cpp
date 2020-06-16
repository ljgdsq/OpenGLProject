#include "Ex_FrameBuffer.h"
#include "../Shape/Cube.h"
#include "../Shape/Plane.h"
#include "../Base/ProjetConfig.hpp"
#include "../Render/ScreenRenderer.h"
#include "../Render/RenderTexture.h"
RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_FrameBuffer)

void Ex_FrameBuffer::InitData()
{
    plane = new Plane("wood.png");
    cube1 = new Cube("container2.png");
   
    winSize = ProjectConfig::GetInstance()->GetWindowSize();
    renderTexture = new RenderTexture(winSize.x, winSize.y);
    screen = new ScreenRenderer();
    screen->InitShader();
    screen->SetTexture(renderTexture->texture);
  
}

void Ex_FrameBuffer::Draw()
{

    Graphics::SetRenderTarget(renderTexture);
    plane->Draw();
    cube1->Draw();
    Graphics::SetRenderTarget(nullptr);
    screen->Draw();

}