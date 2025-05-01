#pragma once
#include "ISortAlgorithm.hpp"

class BubbleSort : public ISortAlgorithm
{
public:
    void Init(Data &data) override;
    bool Step() override;
    std::pair<std::size_t, std::size_t> GetActiveIndices() const override { return {j, j + 1}; }

private:
    Data *data = nullptr;
    std::size_t i = 0;
    std::size_t j = 0;
    bool done = false;
};