#pragma once
#include "../AbstractInputController.h"
class GLFWInputController:public AbstractInputController
{
    
public:
  virtual  void ProcessKeyBoard(void* window)override;
  virtual  void ProcessMouseMove(void* window)override;
  virtual  void ProcessMouseScroll(void* window)override;

};

