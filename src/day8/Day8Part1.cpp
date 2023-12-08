#include "Day8Part1.h"
#include "../utils/Utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <regex>
#include <unordered_map>

int Day8Part1::solve()
{
	std::string directions{};
	std::unordered_map<std::string, std::pair<std::string, std::string>> map{};
	parse("input/day8part1_input.txt", directions, map);
	const std::string start = "AAA";
	const std::string end = "ZZZ";

	int steps{};
	std::string currentKey = start;
	while (currentKey != end)
	{
		std::pair<std::string, std::string> currentOptions = map[currentKey];
		char nextDir = directions[steps % directions.size()];
		currentKey = nextDir == 'L' ? currentOptions.first : currentOptions.second;
		steps++;
	}

	std::cout << steps;

	return steps;
}

void Day8Part1::parse(
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
