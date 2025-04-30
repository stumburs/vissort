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
    for (size_t i = 1; i <= data_size; i++)
    {
        data.emplace_back(Element{.value = i, .color = ColorFromHSV(i / static_cast<float>(data_size) * 360.0f, 0.3f, 1.0f)});
    }
}

const std::vector<Element> &Sorter::GetData()
{
    return this->data;
}
