#include "DataGenerator.h"
#include <ctime>

DataGenerator::DataGenerator()
{
	srand(time(NULL));
}

void DataGenerator::Initialize(std::vector<Element>& data, std::size_t size)
{
	data.clear();
	for (int i = 1; i < size + 1; i++)
	{
		Element elem{};
		elem.value = i;
		elem.color = ColorFromHSV((float)i / size * 360.0f, 0.3f, 1.0f);
		data.push_back(elem);
	}
}

void DataGenerator::Randomize(std::vector<Element>& data)
{
	for (std::size_t i = 0; i < data.size(); i++)
		std::swap(data[i], data[rand() % data.size()]);
}

void DataGenerator::Sin(std::vector<Element>& data)
{
	std::size_t size = data.size();
	data.clear();
	for (std::size_t i = 0; i < size; i++)
	{
		Element elem{};
		float sin_value = sinf((float)i / size * PI * 2);
		sin_value = (sin_value + 1.0f) / 2.0f;
		elem.value = sin_value * GetScreenHeight();
		elem.color = ColorFromHSV((float)i / size * 360.0f, 0.3f, 1.0f);
		data.push_back(elem);
	}
}

void DataGenerator::Fuzzy(std::vector<Element>& data)
{
	std::size_t size = data.size();
	data.clear();

	for (int i = 1; i < size + 1; i++)
	{
		Element elem{};
		elem.value = i + static_cast<float>(std::rand()) / RAND_MAX * size - size / 2.0f;
		elem.color = ColorFromHSV((float)i / size * 360.0f, 0.3f, 1.0f);
		data.push_back(elem);
	}
}

void DataGenerator::Reverse(std::vector<Element>& data)
{
	std::size_t size = data.size();
	data.clear();
	for (int i = 1; i < size + 1; i++)
	{
		Element elem{};
		elem.value = size - i;
		elem.color = ColorFromHSV((float)i / size * 360.0f, 0.3f, 1.0f);
		data.push_back(elem);
	}
}

void DataGenerator::Shuffle(std::vector<Element>& data)
{
	if (active_shuffle == DataGenerator::ShufflingTypes::SinShuffle)
		Sin(data);
	if (active_shuffle == DataGenerator::ShufflingTypes::FuzzyShuffle)
		Fuzzy(data);
	if (active_shuffle == DataGenerator::ShufflingTypes::ReverseShuffle)
		Reverse(data);
}

void DataGenerator::SetActiveShuffle(ShufflingTypes type)
{
	active_shuffle = type;
}

std::string DataGenerator::ShufflingTypesToString(ShufflingTypes type)
{
	std::string text;
	switch (type)
	{
	case ShufflingTypes::SinShuffle:
		text = "Sin Wave";
		break;
	case ShufflingTypes::FuzzyShuffle:
		text = "Fuzzy Asc";
		break;
	case ShufflingTypes::ReverseShuffle:
		text = "Reverse";
		break;
	default:
		text = "Unknown type";
		break;
	}

	return text;
}

