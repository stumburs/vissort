#include "GenAscending.hpp"

void GenAscending::Generate(Data &data)
{
    data.clear();
    for (size_t i = 1; i <= data.capacity(); i++)
    {
        Element e;
        e.value = i;
        e.color = ColorFromHSV(i / static_cast<float>(data.capacity()) * 360.0f, 0.3f, 1.0f);
        data.push_back(e);
    }
}