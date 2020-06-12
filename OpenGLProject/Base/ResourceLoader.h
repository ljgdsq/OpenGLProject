#pragma once
#include "Singleton.h"
#include "../Base/Image.h"
#include "../Base/Model.h"
class ResourceLoader:public Singleton<ResourceLoader>
{
public:
    Image* LoadImage(const char* name,bool flipY=false);
    GL3D::Model* LoadModel(const char* name);
};

