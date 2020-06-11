#include "Ex_Skybox.h"
#include <vector>
#include "stb_image.h"
#include "../Utils/ScreenViewUtil.h"
#include "../Utils/FileUtil.h"
#include "../Base/ProjetConfig.hpp"
#include "../Base/Camera.hpp"
#include "../Render/Skybox.h"
#include "../Shape/Cube.h"

RENDERER_BASE_CONSTRUCTOR_IMPL(Ex_Skybox)

void Ex_Skybox::InitData()
{
    skybox = new Skybox();
    cube = new Cube("wood.png");
}


void Ex_Skybox::Draw()
{
    cube->Draw();
    skybox->Draw();

}