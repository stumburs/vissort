#pragma once
#include <map>
#include <memory>
#include <string>
#include "IGenerateAlgorithm.hpp"

class DataGenerator
{
public:
    DataGenerator();
    std::map<std::string, std::unique_ptr<IGenerateAlgorithm>> generator;
};