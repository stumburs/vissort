#include "Gui.hpp"
#include "raylib.h"
#include <algorithm>
#include <cmath>

Gui::Gui(Sorter &sorter) : sorter(sorter)
{
}

void Gui::Render()
{
    BeginDrawing();
    {
        ClearBackground({40, 44, 52, 255});

        this->RenderData(this->sorter.GetData());

        DrawFPS(20, 20);
    }
    EndDrawing();
}

// Render sorter data to screen.
// Size is dynamically adjusted based off window resolution.
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
