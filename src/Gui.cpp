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

        this->DrawData(this->sorter.GetData());

        DrawFPS(20, 20);
    }
    EndDrawing();
}

void Gui::DrawData(const std::vector<Element> &vec)
{
    if (vec.empty())
        return;

    auto max = std::max_element(vec.begin(), vec.end(), [](const Element &a, const Element &b)
                                { return a.value < b.value; });

    auto scale_x = GetScreenWidth() / static_cast<float>(vec.size());
    auto scale_y = GetScreenHeight() / static_cast<float>(max->value);

    for (size_t i = 0; i < vec.size(); i++)
    {
        const Element &e = vec.at(i);
        DrawRectangle(
            scale_x * i,
            GetScreenHeight() - e.value * scale_y,
            std::ceil(scale_x),
            e.value * scale_y + 1,
            e.color);
    }
}
