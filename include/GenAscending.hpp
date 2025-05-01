#pragma once
#include "IGenerateAlgorithm.hpp"

class GenAscending : public IGenerateAlgorithm
{
public:
    void Generate(std::vector<Element> &data) override;
};