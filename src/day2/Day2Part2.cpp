#include "Day2Part2.h"
#include <vector>
#include <string>
#include "../utils/Utils.h"
#include <regex>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <numeric>

int Day2Part2::solve()
{
	const std::unordered_map<std::string, int> reference{
		{ "red", 12 },
		{ "green", 13 },
		{ "blue", 14 }
	};
	const std::vector<std::string> lines = *Utils::read_lines("input/day2part2_input.txt").get();
	const std::regex rgx("(\\d+) (red|green|blue)");
	std::smatch matches;
	std::vector<std::unordered_map<std::string, int>> colorCount(lines.size());
	for (int i = 0; i < lines.size(); i++)
	{
		const auto& line = lines[i];
		auto lineIter = line.cbegin();
		while (std::regex_search(lineIter, line.end(), matches, rgx))
		{
			int& current = colorCount[i][matches[2]];
			current = std::max(current, stoi(matches[1].str()));
			lineIter = matches[0].second;
		}
	}

	long result = std::reduce(
		colorCount.begin(),
		colorCount.end(),
		0l,
		[](long acc, const std::unordered_map<std::string, int>& game)
		{
			long power = std::reduce(game.begin(), game.end(), 1l, [](long acc, const std::pair<std::string, int>& p) { return acc * p.second; });
			return acc + power;
		}
	);

	// answer 56322
	std::cout << result;

	return result;
}
