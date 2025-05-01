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
    void RenderData(const Data &data);
    void RenderMenu();

    Sorter &sorter;
    DataGenerator &data_generator;
};