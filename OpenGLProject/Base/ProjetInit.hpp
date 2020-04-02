#include "Singleton.h"

#include <string>
class ProjectConfig {
public:
    static std::string executePath;
};

std::string ProjectConfig::executePath;