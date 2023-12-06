#include "Day5Part2.h"
#include "../utils/Utils.h"
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <set>
#include <algorithm>
#include <ranges>

int64_t Day5Part2::solve()
{
	std::vector<Range> seeds{};
	std::vector<std::set<ConversionMapEntry>> maps{};
	parse("input/day5part2_example.txt", seeds, maps);

	std::vector<Range> locations{};
	std::vector<Range> inputs{ seeds };
	while (!inputs.empty())
	{
		const Range seedRange = inputs.front();
		inputs.erase(inputs.begin());

		Range currentRange{ seedRange };
		for (const auto& map : maps)
		{
			for (const auto& mapEntry : map)
			{
				if (mapEntry.Source.Contains(currentRange))
				{

					break;
				}

				Range overlap{};
				if (currentRange.Overlap(mapEntry.Source, overlap))
				{
					currentRange = mapEntry.Apply(overlap);
					break;
				}
			}
		}
		locations.push_back(currentRange);
	}

	auto locationsIter = std::views::transform(locations, [](const Range& r) { return r.Start; });
	int64_t result = *(std::ranges::min_element(locationsIter));

	std::cout << result;

	return result;
}

void Day5Part2::parse(
	const std::string& path,
	std::vector<Range>& seedsOut,
	std::vector<std::set<ConversionMapEntry>>& mapsOut
) const
{
	std::ifstream file(path);
	assert(file.is_open());

	std::string line;
	std::getline(file, line);
	std::stringstream ss(line);
	std::string word;

	ss >> word;
	while (!ss.eof())
	{
		ss >> word;
		const int64_t Start{ stoll(word) };
		ss >> word;
		const int64_t Length{ stoll(word) };
		seedsOut.push_back(Range::FromLength(Start, Length));
	}

	std::set<ConversionMapEntry> currentMap{};
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
		const int64_t DestinationStart{ stoll(word) };
		ss >> word;
		const int64_t SourceStart{ stoll(word) };
		ss >> word;
		const int64_t RangeLength{ stoll(word) };
		currentMap.insert(
			ConversionMapEntry
			{
				Range::FromLength(DestinationStart, RangeLength),
				Range::FromLength(SourceStart, RangeLength)
			}
		);
	}
	mapsOut.push_back(currentMap);
}

Day5Part2::Range::Range(int64_t start, int64_t end) : Start{ start }, End{ end }
{
}

Day5Part2::Range Day5Part2::Range::FromLength(int64_t start, int64_t length)
{
	return Range{ start, start + length };
}

bool Day5Part2::Range::Overlap(const Day5Part2::Range& other, Day5Part2::Range& overlapOut) const
{
	if (Start <= other.End && End >= other.Start) {
		overlapOut = Range(std::max(Start, other.Start), std::min(End, other.End));
		return true;
	}
	return false;
}

bool Day5Part2::Range::Contains(const Range& other) const
{
	return Start >= other.Start && End >= other.End;
}

Day5Part2::Range Day5Part2::ConversionMapEntry::Apply(const Range& range) const
{
	const int64_t start = Destination.Start + range.Start - Source.Start;
	const int64_t end = Destination.Start + range.End - Source.Start;
	return Range(start, end);
}
