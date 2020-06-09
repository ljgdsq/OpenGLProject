#pragma once
#include <map>
#include <vector>
#include <string>
#include "../Render/Renderer.h"
class ExampleBase
{
    ExampleBase() = delete;
    static std::map<std::string, Renderer*> examples;
    static std::vector<std::string> exampleIndexs;
public:
    static void AddExample(std::string name,Renderer*render);
    static Renderer* GetExample(std::string name);
    static Renderer* GetLastExample();
};
#define ADD_EXAMPLE(TypeName) \
ExampleBase::AddExample(#TypeName,new TypeName());
