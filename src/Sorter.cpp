#include "Sorter.hpp"

Sorter::Sorter()
{
    this->InitData(100);
}

// Initializes sortable data.
// TODO: Implement different kinds of starting data.
void Sorter::InitData(size_t data_size)
{
    data.clear();
    data.reserve(data_size);
}

std::vector<Element> &Sorter::GetData()
{
    return this->data;
}
