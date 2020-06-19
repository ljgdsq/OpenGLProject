#pragma once
#include "../AbstractInputController.h"
class GLFWInputController:public AbstractInputController
{
    
public:
  virtual  void ProcessKeyBoard(void* window)override;
  virtual  void ProcessMouseMove(void* window)override;
  virtual  void ProcessMouseScroll(void* window)override;

  enum KeyEvent
  {
      KEY_DOWN_ONCE,
      KEY_RELEASE_ONCE,
      KEY_CLICK,
      KEY_CONTINUE_TOUCH
  };
  

  //void RegisterKeyEvent(KeyEvent type,)
};

