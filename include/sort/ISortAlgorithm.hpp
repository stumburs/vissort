#pragma once
#include "Data.hpp"

class ISortAlgorithm
{
public:
    virtual ~ISortAlgorithm() = default;

    virtual void Init(Data &data) = 0;

    // Runs a sorting step.
    // Returns true if successful.
    // Returns false if sorting is complete.
    virtual bool Step() = 0;

    // Experimental: Expose indices being compared
    virtual std::pair<std::size_t, std::size_t> GetActiveIndices() const { return {0, 0}; }
};