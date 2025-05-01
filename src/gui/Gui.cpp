#include "Gui.hpp"
#include "raylib.h"
#include <algorithm>
#include <cmath>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Gui::Gui(Sorter &sorter, DataGenerator &data_generator) : sorter(sorter), data_generator(data_generator)
{
}

void Gui::Render()
{
    BeginDrawing();
    {
        ClearBackground({40, 44, 52, 255});

        this->RenderData(this->sorter.GetData());

        this->RenderMenu();

        DrawFPS(20, 20);
    }
    EndDrawing();
}

// Render sorter data to screen.
// Size is dynamically adjusted based off window resolution
// spanning maximum available space.
void Gui::RenderData(const std::vector<Element> &data)
{
    if (data.empty())
        return;

    auto max = std::max_element(data.begin(), data.end(), [](const Element &a, const Element &b)
                                { return a.value < b.value; });

    auto scale_x = GetScreenWidth() / static_cast<float>(data.size());
    auto scale_y = GetScreenHeight() / static_cast<float>(max->value);

    for (size_t i = 0; i < data.size(); i++)
    {
        const Element &e = data.at(i);
        DrawRectangle(
            scale_x * i,
            GetScreenHeight() - e.value * scale_y,
            std::ceil(scale_x),
            e.value * scale_y + 1,
            e.color);
    }
}

void Gui::RenderMenu()
{
    if (GuiButton({100, 100, 40, 40}, nullptr))
    {
        std::printf("Ascending\n");
        data_generator.generator["Ascending"]->Generate(sorter.GetData());
    }
}
