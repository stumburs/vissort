#pragma once
#include "IGenerateAlgorithm.hpp"

// Generates data in descending order
class GenDescending : public IGenerateAlgorithm
{
public:
    void Generate(Data &data) override;
};