#pragma once
#include "IGenerateAlgorithm.hpp"

// Generates data in ascending order
class GenAscending : public IGenerateAlgorithm
{
public:
    void Generate(std::vector<Element> &data) override;
};