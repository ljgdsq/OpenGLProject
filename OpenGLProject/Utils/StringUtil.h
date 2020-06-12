#pragma once
#include <string>
#include <sstream>
#include <glm/glm.hpp>


std::string toString(int value);
std::string toString(float value);
std::string toString(double value);
std::string toString(bool value);
std::string toString(glm::vec3 value);
std::string toString(std::string value);
std::string toString(const char* value);