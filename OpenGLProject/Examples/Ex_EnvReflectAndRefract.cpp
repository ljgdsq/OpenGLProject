#include "Ex_EnvReflectAndRefract.h"
#include "../Render/Skybox.h"
#include "../Shape/Cube.h"

RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_EnvReflectAndRefract)

void Ex_EnvReflectAndRefract::InitData()
{
    skybox = new Skybox();
    cube = new Cube("wood.png");
}


void Ex_EnvReflectAndRefract::Draw()
{
    cube->Draw();
    skybox->Draw();
}