#pragma once
#include "Data.hpp"
#include <vector>

class IGenerateAlgorithm
{
public:
    virtual ~IGenerateAlgorithm() = default;
    virtual void Generate(Data &data) = 0;
};
