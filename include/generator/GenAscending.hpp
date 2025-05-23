#pragma once
#include "IGenerateAlgorithm.hpp"

// Generates data in ascending order
class GenAscending : public IGenerateAlgorithm
{
public:
    void Generate(Data &data) override;
};