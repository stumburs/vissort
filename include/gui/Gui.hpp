#pragma once
#include <vector>
#include "Element.hpp"
#include "Sorter.hpp"
#include "DataGenerator.hpp"

class Gui
{
public:
    Gui(Sorter &sorter, DataGenerator &data_generator);
    void Render();

private:
    void RenderData(const std::vector<Element> &vec);
    void RenderMenu();

    Sorter &sorter;
    DataGenerator &data_generator;
};