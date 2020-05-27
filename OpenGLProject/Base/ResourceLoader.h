#pragma once
#include "Singleton.h"
#include "../Core/Image.h"
class ResourceLoader:public Singleton<ResourceLoader>
{
public:
    Image* LoadImage(const char* name,bool flipY=false);
};

