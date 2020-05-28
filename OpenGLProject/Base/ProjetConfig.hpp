#include "Singleton.h"
#include <string>
#include "BaseStruct.hpp"
class ProjectConfig :public Singleton<ProjectConfig> {
public:
    void SetExecutePath(std::string exePath) {
        auto pos = exePath.find_last_of("/");
        if (pos != std::string::npos)
        {
            executePath = exePath.substr(0, pos);
        }
        else
        {
            pos = exePath.find_last_of("\\");
            if (pos != std::string::npos)
            {
                executePath = exePath.substr(0, pos);
            }
        }
    }

    std::string GetExecutePath() {
        return executePath;
    }

    void SetWindowSize(Size size) {
        windowSize = size;
    }

    Size GetWindowSize() {
        return windowSize;
    }
 
private:
    std::string  executePath;
    Size windowSize;
};