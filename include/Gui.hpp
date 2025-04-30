#pragma once
#include <vector>
#include "Element.hpp"
#include "Sorter.hpp"

class Gui
{
public:
    Gui(Sorter &sorter);
    void Render();

private:
    void RenderData(const std::vector<Element> &vec);

    Sorter &sorter;
};