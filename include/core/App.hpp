#pragma once
#include "Gui.hpp"
#include "Sorter.hpp"
#include "DataGenerator.hpp"

class App
{
public:
    App();
    void Run();

private:
    DataGenerator data_generator;
    Sorter sorter;
    Gui gui;
};