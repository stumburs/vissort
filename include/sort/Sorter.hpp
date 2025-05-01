#pragma once
#include <vector>
#include "Data.hpp"
#include <cstddef>

class Sorter
{
public:
    Sorter();
    void InitData(size_t data_size);
    Data &GetData();

private:
    Data data;
};