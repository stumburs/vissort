#include "GUI.h"
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <thread>
#include <iostream>
#include <sstream>
#include "Generators.h"

GUI::GUI(Sorter& sorter, Generators& generators) : sorter(sorter), generators(generators)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 600, "vissort");
	SetWindowSize(GetMonitorWidth(0) / 2, GetMonitorHeight(0) / 2);
	SetTargetFPS(60);

	GuiSetStyle(DEFAULT, TEXT_SIZE, 20);

	// Background
	GuiSetStyle(DEFAULT, BASE_COLOR_NORMAL, ColorToInt({ 76, 82, 99, 255 }));
	GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, ColorToInt({ 92, 99, 112, 255 }));
	GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, ColorToInt({ 108, 116, 125, 255 }));
	GuiSetStyle(DEFAULT, BACKGROUND_COLOR, ColorToInt({ 76, 82, 99, 255 }));

	// Text
	GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt({ 171, 178, 191, 255 }));
	GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt({ 229, 192, 123, 255 }));
	GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, ColorToInt({ 229, 192, 123, 255 }));

	// Border
	GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt({ 171, 178, 191, 255 }));
	GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, ColorToInt({ 209, 154, 102, 255 }));
	GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, ColorToInt({ 209, 154, 102, 255 }));
}

void GUI::Render()
{
	// Draw
	BeginDrawing();
	{
		ClearBackground({ 40, 44, 52, 255 });

		DrawData(sorter.GetData());

		DrawMenu();
	}
	EndDrawing();
}

void GUI::DrawData(const std::vector<Element>& vec)
{
	if (vec.empty())
		return;
	// Find largest element in vec
	int max = vec.begin()->value;

	for (const auto& elem : vec)
	{
		if (elem.value > max)
			max = elem.value;
	}

	float scale_x = GetScreenWidth() / (float)vec.size();
	float scale_y = GetScreenHeight() / (float)max;
	for (int i = 0; i < vec.size(); i++)
	{
		DrawRectangle(
			scale_x * i,
			GetScreenHeight() - vec[i].value * scale_y,
			ceilf(scale_x),
			vec[i].value * scale_y + 1,
			vec[i].color
		);
	}
}

void GUI::DrawMenu()
{
	bool sorting_active = sorter.GetSortingActive();

	if (GuiButton({ 20, 20, 40, 40 }, NULL)) // Toggle settings menu
		settings_open = !settings_open;

	// Change gear icon depending on hover
	if (CheckCollisionPointRec(GetMousePosition(), { 20, 20, 40, 40 }))
		GuiDrawIcon(GuiIconName::ICON_GEAR, 24, 24, 2, { 229, 192, 123, 255 });
	else
		GuiDrawIcon(GuiIconName::ICON_GEAR, 24, 24, 2, { 171, 178, 191, 255 });

	if (settings_open)
	{
		// Column 1
		// Hide UI while sorting
		if (!sorting_active)
		{
			if (!shuffle_dropdown_edit)
			{
				new_vec_size = (int)GuiSlider({ 20, 120, 200, 40 }, "", "", new_vec_size, 4, GetScreenWidth());
				DrawText(TextFormat("%d", new_vec_size), (20 + 200 / 2) - MeasureText(TextFormat("%d", new_vec_size), 20) / 2, 130, 20, GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL)));

				if (GuiButton({ 20, 170, 120, 40 }, "Apply") && !sorting_active)
				{
					sorter.InitData(new_vec_size);

					// Convert int to specific string
					auto begin = generators.generators.begin();
					std::advance(begin, shuffle_selected);

					// Janky workaround for std::map sorting keys alphabetically
					if (begin->first == "Randomize")
					{
						begin = std::next(begin);
					}
					
					generators.generators[begin->first]->Generate(sorter.GetData());
				}

				if (GuiButton({ 20, 220, 120, 40 }, "Randomize") && !sorting_active)
				{
					generators.generators["Randomize"]->Generate(sorter.GetData());
				}
			}
			// Data generator dropdown
			if (GuiDropdownBox({ 20, 70, 200, 40 }, GenerateGeneratorDropdownOptions().c_str(), &shuffle_selected, shuffle_dropdown_edit))
			{
				shuffle_dropdown_edit = !shuffle_dropdown_edit;
			}

			// Column 2
			//
			if (!sorting_dropdown_edit) // Dropdown closed
			{
				new_sorting_delay = GuiSlider({ 230, 120, 200, 40 }, "", "ms", new_sorting_delay, 0.0001, 0.1);
				DrawText(TextFormat("%.4lf", new_sorting_delay * 1000), (230 + 200 / 2) - MeasureText(TextFormat("%.4lf", new_sorting_delay * 1000), 20) / 2, 130, 20, GetColor(GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL)));
				sorter.SetSortingDelay(new_sorting_delay);
			}
			// Sorting dropdown
			if (GuiDropdownBox({ 230, 70, 200, 40 }, GenerateSortingAlgorithmDropdownOptions().c_str(), &sorting_selected, sorting_dropdown_edit))
			{
				sorting_dropdown_edit = !sorting_dropdown_edit;
				sorter.SetActiveAlgorithm(Sorter::SortingAlgorithms(sorting_selected));
			}
		}
		if (sorting_active)
		{
			GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt({ 224, 108, 117, 255 }));
			GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt({ 224, 108, 117, 255 }));
			GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt({ 190, 80, 70, 255 }));
			GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, ColorToInt({ 190, 80, 70, 255 }));
		}
		std::string sorting_text = sorting_active ? "Stop" : "Start";
		if (GuiButton({ 70, 20, 120, 40 }, sorting_text.c_str()))
		{
			if (!sorting_active)
			{
				sorter.StartThread();
				std::cout << "Thread started!\n";
			}
			else
			{
				sorter.SetSortingActive(false);
			}
		}
		GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt({ 171, 178, 191, 255 }));
		GuiSetStyle(DEFAULT, TEXT_COLOR_FOCUSED, ColorToInt({ 229, 192, 123, 255 }));
		GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt({ 171, 178, 191, 255 }));
		GuiSetStyle(DEFAULT, BORDER_COLOR_FOCUSED, ColorToInt({ 209, 154, 102, 255 }));
	}
}

std::string GUI::GenerateSortingAlgorithmDropdownOptions()
{
	std::stringstream ss;
	for (int i = 0; i < (int)Sorter::SortingAlgorithms::END; i++)
	{
		ss << sorter.SortingEnumToString(Sorter::SortingAlgorithms(i));

		// Add separators before the last entry
		if (i < (int)Sorter::SortingAlgorithms::END - 1)
			ss << ';';
	}
	return ss.str();
}

std::string GUI::GenerateGeneratorDropdownOptions()
{
	std::stringstream ss;
	bool first = true;
	for (const auto& m : generators.generators)
	{
		// Don't display Randomize in the dropdown.
		// There is probably a better solution, but it's
		// convenient to implement it as IGenerateAlgorithm
		if (m.first == "Randomize")
		{
			continue;
		}

		if (!first)
		{
			ss << ';';
		}

		ss << m.first;
		first = false;
	}
	return ss.str();
}
