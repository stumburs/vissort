#include "DataGenerator.hpp"
#include "GenAscending.hpp"

DataGenerator::DataGenerator()
{
    srand(time(NULL));
    generator["Ascending"] = std::make_unique<GenAscending>();
}