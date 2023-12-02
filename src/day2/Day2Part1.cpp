#include "Day2Part1.h"
#include <vector>
#include <string>
#include "../utils/Utils.h"
#include <regex>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <numeric>

int Day2Part1::solve()
{
	const std::unordered_map<std::string, int> reference{
		{ "red", 12 },
		{ "green", 13 },
		{ "blue", 14 }
	};
	const std::vector<std::string> lines = *Utils::read_lines("input/day2part1_input.txt").get();
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

	std::vector<int> validGames{};
	for (int i = 0; i < lines.size(); i++)
	{
		bool isValid = std::all_of(
			reference.begin(),
			reference.end(),
			[&colorCount, i](std::pair<std::string, int> x)
			{
				return colorCount.at(i).at(x.first) <= x.second;
			}
		);

		if (isValid)
			validGames.push_back(i);
	}

	int result = std::reduce(
		validGames.begin(),
		validGames.end(),
		0,
		[](int acc, int gameId) { return acc + gameId + 1; }
	);

	// answer 2447
	std::cout << result;

	return result;
}
