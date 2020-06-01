#include "World.h"

ITimer* World::GetTimer()
{
    return _timer;
}

AbstractInputController* World::GetInputController()
{
    return _inputController;
}

ResourceLoader* World::GetResourceLoader()
{
    return _resourceLoader;
}

Camera* World::GetMainCamera()
{
    return _mainCamera;
}

void World::InitWorld(ITimer* timer, AbstractInputController* inputController, ResourceLoader* resourceLoader, Camera* camera)
{
    this->_timer = timer;
    this->_inputController = inputController;
    this->_resourceLoader = resourceLoader;
    this->_mainCamera = camera;
}
