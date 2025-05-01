#include "GenDescending.hpp"

void GenDescending::Generate(std::vector<Element> &data)
{
    data.clear();
    for (size_t i = 1; i <= data.capacity(); i++)
    {
        Element e;
        e.value = data.capacity() - i + 1;
        e.color = ColorFromHSV(i / static_cast<float>(data.capacity()) * 360.0f, 0.3f, 1.0f);
        data.push_back(e);
    }
}