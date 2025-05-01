#include "Sorter.hpp"
#include <cstdlib>
#include <memory>

void Sorter::SetAlgorithm(std::unique_ptr<ISortAlgorithm> algo)
{
    this->algorithm = std::move(algo);
}

// Initializes sortable data.
void Sorter::InitData(size_t data_size)
{
    data.clear();
    data.reserve(data_size);

    // Temporary solution
    for (std::size_t i = 0; i < data_size; ++i)
    {
        data.emplace_back(rand() % 100, GRAY);
    }
}

void Sorter::StartSort()
{
    if (this->algorithm)
    {
        this->algorithm->Init(data);
    }
}

bool Sorter::Step()
{
    return this->algorithm ? this->algorithm->Step() : false;
}

Data &Sorter::GetData()
{
    return this->data;
}
