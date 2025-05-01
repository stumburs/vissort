#include "Gui.hpp"
#include "raylib.h"
#include <algorithm>
#include <cmath>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "BubbleSort.hpp"

Gui::Gui(Sorter &sorter, DataGenerator &data_generator) : sorter(sorter), data_generator(data_generator)
{
}

void Gui::Render()
{

    if (IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_RIGHT_SHIFT))
    {
        sorter.Step();
    }

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
void Gui::RenderData(const Data &data)
{
    if (data.empty())
        return;

    auto max = std::max_element(data.begin(), data.end(), [](const Element &a, const Element &b)
                                { return a.value < b.value; });

    auto scale_x = GetScreenWidth() / static_cast<float>(data.size());
    auto scale_y = GetScreenHeight() / static_cast<float>(max->value);

    for (size_t i = 0; i < data.size(); i++)
    {
        auto comparing_indices = sorter.GetActiveIndices();
        const Element &e = data.at(i);
        DrawRectangle(
            scale_x * i,
            GetScreenHeight() - e.value * scale_y,
            std::ceil(scale_x),
            e.value * scale_y + 1,
#ifdef ENABLE_COMPARISON
            (comparing_indices.first == i || comparing_indices.second == i ? RED : e.color));
#else
            e.color);
#endif
    }
}

void Gui::RenderMenu()
{
    if (GuiButton({100, 100, 40, 40}, "buh"))
    {
        sorter.InitData(100);
        data_generator.generator["Descending"]->Generate(sorter.GetData());
        sorter.SetAlgorithm(std::make_unique<BubbleSort>());
        sorter.StartSort();
    }

    if (GuiButton({20, static_cast<float>(GetScreenHeight()) - 60, 80, 40}, "Step [_]"))
    {
        sorter.Step();
    }
}
