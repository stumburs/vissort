#pragma once
#include "Element.hpp"
#include <vector>

class IGenerateAlgorithm
{
public:
    virtual ~IGenerateAlgorithm() = default;
    virtual void Generate(std::vector<Element> &data) = 0;
};
