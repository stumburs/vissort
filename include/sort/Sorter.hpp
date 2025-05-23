#pragma once
#include <vector>
#include "Data.hpp"
#include <cstddef>
#include "ISortAlgorithm.hpp"
#include <memory>

class Sorter
{
public:
    void SetAlgorithm(std::unique_ptr<ISortAlgorithm> algo);
    void InitData(size_t data_size);
    void StartSort();
    bool Step();
    Data &GetData();
    std::pair<size_t, size_t> GetActiveIndices() const;

private:
    Data data;
    std::unique_ptr<ISortAlgorithm> algorithm;
};