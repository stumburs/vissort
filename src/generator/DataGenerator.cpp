#include "DataGenerator.hpp"
#include "GenAscending.hpp"
#include "GenDescending.hpp"

DataGenerator::DataGenerator()
{
    srand(time(NULL));
    generator["Ascending"] = std::make_unique<GenAscending>();
    generator["Descending"] = std::make_unique<GenDescending>();
}