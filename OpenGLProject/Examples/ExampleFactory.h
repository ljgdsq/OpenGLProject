#pragma once
#include <map>
#include <vector>
#include <string>
#include "../Render/Renderer.h"
class ExampleFactory
{
    ExampleFactory() = delete;
    static std::map<std::string, Renderer*> examples;
    static std::vector<std::string> exampleIndexs;
public:
    static void AddExample(std::string name,Renderer*render);
    static Renderer* GetExample(std::string name);
    static Renderer* GetLastExample();
};
#define ADD_EXAMPLE(TypeName) \
ExampleFactory::AddExample(#TypeName,new TypeName());
