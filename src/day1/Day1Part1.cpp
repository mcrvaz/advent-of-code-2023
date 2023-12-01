#include "Day1Part1.h"
#include <regex>
#include "../utils/Utils.h"
#include <iostream>

int Day1Part1::solve()
{
	const std::vector<std::string> lines = *Utils::read_lines("input/day1part1_input.txt").get();
	const std::regex rgx("(\\d)");
	std::smatch matches;
	int sum{};
	for (const auto& line : lines)
	{
		std::vector<std::string> nums{ };
		auto lineIter = line.cbegin();
		while (std::regex_search(lineIter, line.end(), matches, rgx))
		{
			nums.push_back(matches[1]);
			lineIter = matches[0].second;
		}

		int d1 = stoi(nums.front());
		int d2 = stoi(nums.back());
		int num = (d1 * 10) + d2;
		sum += num;
	}

	// answer 54239
	std::cout << sum;

	return sum;
}
