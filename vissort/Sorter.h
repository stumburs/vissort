#pragma once
#include "Element.h"
#include <vector>
#include <string>
#include <functional>
#include <stack>
#include <mutex>
#include "DataGenerator.h"

class Sorter
{
public:
	Sorter(DataGenerator& data_generator);
	std::vector<Element>& GetData();

	// Sorting algorithms
	void BubbleSort();

	int Partition(int low, int high);
	void QuickSort(int low, int high);

	int GetNextGap(int gap);
	void CombSort();

	void ShellSort();

	void CocktailSort();

	void GnomeSort();

	void CycleSort();

	enum SortingAlgorithms
	{
		BubbleSortEnum = 0,
		QuickSortEnum,
		CombSortEnum,
		ShellSortEnum,
		CocktailSortEnum,
		GnomeSortEnum,
		CycleSortEnum,
		END
	};

	SortingAlgorithms GetActiveAlgorithm();
	void SetActiveAlgorithm(SortingAlgorithms active_algorithm);
	std::string SortingEnumToString(SortingAlgorithms algorithm);
	bool GetSortingActive();
	void SetSortingActive(bool active);
	void StartThread();
	void SetSortingDelay(double delay);

private:
	DataGenerator& data_generator;
	std::vector<Element> data;
	SortingAlgorithms active_algorithm = SortingAlgorithms::BubbleSortEnum;
	bool sorting_active = false;
	std::mutex quicksort_thread_mutex;
	std::stack<int> quick_sort_thread_depth;
	double sorting_delay = 0.001;
};

