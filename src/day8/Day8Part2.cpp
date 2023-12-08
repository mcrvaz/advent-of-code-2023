#include "Day8Part2.h"
#include "../utils/Utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <regex>
#include <unordered_map>
#include <ranges>
#include <algorithm>
#include <numeric>

int64_t Day8Part2::solve()
{
	std::string directions{};
	std::unordered_map<std::string, std::pair<std::string, std::string>> map{};
	parse("input/day8part2_input.txt", directions, map);
	auto iter = map
		| std::views::filter([](const auto& pair) { return EndsWithChar(pair.first, 'A'); })
		| std::views::transform([](const auto& pair) { return pair.first; });
	std::vector<std::string> currentKeys{ std::begin(iter), std::end(iter) };

	std::vector<int> steps{};
	for (const auto& currentKey : currentKeys)
		steps.push_back(GetStepsToEndOfPath(directions, map, currentKey));

	int64_t result = std::accumulate(
		steps.begin(),
		steps.end(),
		int64_t{ 1 },
		[](int64_t acc, int x) { return std::lcm(acc, x); }
	);

	// answer 8811050362409
	std::cout << result;

	return result;
}

int Day8Part2::GetStepsToEndOfPath(
	const std::string& directions,
	const std::unordered_map<std::string, std::pair<std::string, std::string>>& map,
	const std::string& startKey
) const
{
	int steps{};
	std::string currentKey{ startKey };
	while (!EndsWithChar(currentKey, 'Z'))
	{
		const std::pair<std::string, std::string>& currentOptions = map.at(currentKey);
		char nextDir = directions[steps % directions.size()];
		currentKey = nextDir == 'L' ? currentOptions.first : currentOptions.second;
		steps++;
	}
	return steps;
}

void Day8Part2::parse(
	const std::string& path,
	std::string& directionsOut,
	std::unordered_map<std::string, std::pair<std::string, std::string>>& mapOut
) const
{
	const std::vector<std::string> lines = *Utils::read_lines(path).get();

	std::stringstream ss(lines[0]);
	ss >> directionsOut;

	const std::regex rgx("(\\w{3}) = \\((\\w{3}), (\\w{3})\\)");
	std::smatch matches;
	for (const auto& line : lines)
	{
		if (!std::regex_search(line.begin(), line.end(), matches, rgx))
			continue;
		mapOut[matches[1]] = { matches[2], matches[3] };
	}
}

bool Day8Part2::EndsWithChar(const std::string& s, char c)
{
	return *s.rbegin() == c;
}
