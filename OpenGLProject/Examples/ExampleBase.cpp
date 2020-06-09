#include "ExampleBase.h"


std::map<std::string, Renderer*> ExampleBase::examples;
std::vector<std::string> ExampleBase::exampleIndexs;
void ExampleBase::AddExample(std::string name, Renderer* render)
{
    examples.insert({name,render});
    exampleIndexs.push_back(name);
}

Renderer* ExampleBase::GetExample(std::string name)
{
    auto iter=examples.find(name);
    if (iter!=examples.end())
    {
        return static_cast<Renderer*>(iter->second);
    }
    return nullptr;
}

Renderer* ExampleBase::GetLastExample()
{   
    if (exampleIndexs.size()>0)
    {
        return  GetExample(exampleIndexs.back());
    }
    return nullptr;
    
}
