#include "BubbleSort.hpp"

void BubbleSort::Init(Data &data)
{
    this->data = &data;
    this->i = 0;
    this->j = 0;
    this->done = false;
}

bool BubbleSort::Step()
{
    if (this->done || !this->data)
    {
        return false;
    }

    if ((*data)[j].value > (*data)[j + 1].value)
    {
        std::swap((*data)[j], (*data)[j + 1]);
    }

    j++;
    if (j >= data->size() - i - 1)
    {
        j = 0;
        i++;
    }

    if (i >= data->size() - 1)
    {
        done = true;
        return false;
    }

    return true;
}
