#pragma once
#include "Singleton.h"
class World:public Singleton<World>
{
private:

    class ITimer* _timer;
    class AbstractInputController* _inputController;
    class ResourceLoader* _resourceLoader;
    class Camera* _mainCamera;

public:
    class ITimer* GetTimer();
    class AbstractInputController* GetInputController();
    class ResourceLoader* GetResourceLoader();
    class Camera* GetMainCamera();

    void InitWorld(class ITimer*timer, class AbstractInputController* inputController,class ResourceLoader* resourceLoader,class  Camera* camera);
};

