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

	std::vector<Range> input{ seeds };
	std::vector<Range> output{};
	for (const auto& map : maps)
	{
		output = GetMappedRange(map, input);
		input = output;
	}

	auto outputIter = std::views::transform(output, [](const Range& r) { return r.Start; });
	int64_t result = *(std::ranges::min_element(outputIter));

	std::cout << result;

	return result;
}

std::vector<Day5Part2::Range> Day5Part2::GetMappedRange(
	const std::set<ConversionMapEntry>& map,
	std::vector<Day5Part2::Range>& input
)
{
	std::vector<Range> output{};
	while (!input.empty())
	{
		Range currentRange{ input.front() };
		input.erase(input.begin());
		for (const auto& mapEntry : map)
		{
			Range overlap{};
			const Range source{ mapEntry.Source };
			if (currentRange.Overlap(source, overlap))
			{
				// example [74,88] and [64,77]
				if (currentRange.Start >= source.Start && currentRange.End > source.End)
				{
					input.push_back(Range(source.End + 1, currentRange.End));
					output.push_back(mapEntry.Apply(overlap));
				}
				// example [47,57] and [56,93]
				else if (currentRange.Start < source.Start && currentRange.End <= source.End)
				{
					input.push_back(Range(currentRange.Start, source.Start - 1));
					output.push_back(mapEntry.Apply(overlap));
				}
				// example [54,97] and [56,93]
				else if (currentRange.Start < source.Start && currentRange.End > source.End)
				{
					if (currentRange.Start < source.Start)
					{
						input.push_back(Range(currentRange.Start, source.Start - 1));
						input.push_back(Range(source.Start, currentRange.End));
					}
					else
					{
						input.push_back(Range(currentRange.Start, source.End));
						input.push_back(Range(source.End + 1, currentRange.End));
					}
					output.push_back(mapEntry.Apply(overlap));
				}
				// example [58,62] and [56,93] - fully contained
				else
				{
					output.push_back(mapEntry.Apply(currentRange));
				}

				break;
			}
		}

		// no mappings found, continue with current input
		if (output.empty())
			output.push_back(currentRange);
	}
	return output;
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
	return Range{ start, start + length - 1 };
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
	return Start <= other.Start && End >= other.End;
}

Day5Part2::Range Day5Part2::ConversionMapEntry::Apply(const Range& range) const
{
	// G = (((S - Smin)*(Dmax - Dmin))/(Smax - Smin)) + Dmin
	auto RangeLerp = [this](int64_t v)
		{
			return (((v - Source.Start) * (Destination.End - Destination.Start)) / (Source.End - Source.Start)) + Destination.Start;
		};

	const int64_t start = RangeLerp(range.Start);
	const int64_t end = RangeLerp(range.End);
	return Range(start, end);
}
