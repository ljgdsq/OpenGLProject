#pragma once

template<class T>
class Singleton
{
public:
  static  T* GetInstance();
};

template<class T>
inline T* Singleton<T>::GetInstance()
{
    static T instance;
    return &instance;
}
