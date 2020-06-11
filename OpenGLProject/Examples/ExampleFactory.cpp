#include "ExampleFactory.h"


std::map<std::string, Renderer*> ExampleFactory::examples;
std::vector<std::string> ExampleFactory::exampleIndexs;
void ExampleFactory::AddExample(std::string name, Renderer* render)
{
    examples.insert({name,render});
    exampleIndexs.push_back(name);
}

Renderer* ExampleFactory::GetExample(std::string name)
{
    auto iter=examples.find(name);
    if (iter!=examples.end())
    {
        return static_cast<Renderer*>(iter->second);
    }
    return nullptr;
}

Renderer* ExampleFactory::GetLastExample()
{   
    if (exampleIndexs.size()>0)
    {
        return  GetExample(exampleIndexs.back());
    }
    return nullptr;
    
}
