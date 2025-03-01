#pragma once
#include "Gui.hpp"
#include "Sorter.hpp"

class App
{
public:
    App();
    void Run();

private:
    // Generators generators;
    Sorter sorter;
    Gui gui;
};