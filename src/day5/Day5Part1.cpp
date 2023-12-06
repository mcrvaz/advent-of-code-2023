#include "Day5Part1.h"
#include "../utils/Utils.h"
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream> 
#include <iostream>

int64_t Day5Part1::solve()
{
	std::vector<int64_t> seeds{};
	std::vector<std::vector<ConversionMapEntry>> maps{};
	parse("input/day5part1_input.txt", seeds, maps);

	std::vector<int64_t> locations{};
	for (int64_t seed : seeds)
	{
		int64_t input = seed;
		for (const auto& map : maps)
		{
			for (const auto& mapEntry : map)
			{
				int64_t destination{};
				if (mapEntry.GetDestination(input, destination))
				{
					input = destination;
					break;
				}
			}
		}
		locations.push_back(input);
	}
	int64_t result = *std::min_element(locations.begin(), locations.end());

	// result 165788812
	std::cout << result;

	return result;
}

void Day5Part1::parse(
	const std::string& path,
	std::vector<int64_t>& seedsOut,
	std::vector<std::vector<ConversionMapEntry>>& mapsOut
) const
{
	std::ifstream file(path);
	assert(file.is_open());

	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);
	std::string word;
	ss >> word;
	while (ss >> word)
		seedsOut.push_back(stoll(word));

	std::vector<ConversionMapEntry> currentMap{};
	while (std::getline(file, line)) {
		if (line.empty())
			continue;

		if (line.find(":") != std::string::npos)
		{
			if (!currentMap.empty())
				mapsOut.push_back(currentMap);

			currentMap = {};
			continue;
		}

		ss = std::stringstream(line);
		ss >> word;
		int64_t DestinationStart{ stoll(word) };
		ss >> word;
		int64_t SourceStart{ stoll(word) };
		ss >> word;
		int64_t RangeLength{ stoll(word) };
		currentMap.push_back(ConversionMapEntry{ DestinationStart, SourceStart, RangeLength });
	}
	mapsOut.push_back(currentMap);
}

bool Day5Part1::ConversionMapEntry::GetDestination(int64_t source, int64_t& destinationOut) const
{
	destinationOut = source;
	if (source < SourceStart || source > SourceStart + RangeLength)
		return false;

	int64_t diff = source - SourceStart;
	if (diff > RangeLength)
		return false;

	destinationOut = DestinationStart + diff;
	return true;
}
