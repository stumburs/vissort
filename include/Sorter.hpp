#pragma once
#include <vector>
#include "Element.hpp"
#include <cstddef>

class Sorter
{
public:
    Sorter();
    void InitData(size_t data_size);
    const std::vector<Element> &GetData();

private:
    std::vector<Element> data;
};