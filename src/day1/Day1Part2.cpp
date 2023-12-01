#include "Day1Part2.h"
#include "../utils/Utils.h"
#include <regex>
#include <iostream>
#include <map>
#include <format>
#include <ranges>;

int Day1Part2::solve()
{
	const std::vector<std::string> lines = *Utils::read_lines("input/day1_input.txt").get();
	const std::map<std::string, int> textDigits{
		{ "one", 1 },
		{ "two", 2 },
		{ "three", 3 },
		{ "four", 4 },
		{ "five", 5 },
		{ "six", 6 },
		{ "seven", 7 },
		{ "eight", 8 },
		{ "nine", 9 },
	};

	std::string rgxStr{ "(\\d" };
	std::string reverseRgxStr{ rgxStr };
	for (const auto& digit : textDigits)
	{
		rgxStr += std::format("|{}", digit.first);
		reverseRgxStr += std::format("|{}", Utils::reverse(digit.first));
	}
	rgxStr += ")";
	reverseRgxStr += ")";

	const std::regex rgx(rgxStr);
	const std::regex reverseRgx(reverseRgxStr);
	std::smatch matches;
	int sum{};
	for (const auto& line : lines)
	{
		std::vector<std::string> nums{ };
		if (std::regex_search(line, matches, rgx))
			nums.push_back(matches[1]);

		std::string reverseLine{ Utils::reverse(line) };
		if (std::regex_search(reverseLine, matches, reverseRgx))
			nums.push_back(Utils::reverse(matches[1].str()));

		int d1 = stoi(nums.front(), textDigits);
		int d2 = stoi(nums.back(), textDigits);
		int num = (d1 * 10) + d2;
		sum += num;
	}

	return sum;
}
	//// answer 55343
	//std::cout << sum;

int Day1Part2::stoi(const std::string& num, const std::map<std::string, int>& textDigits) const
{
	if (textDigits.contains(num))
		return textDigits.at(num);
	return std::stoi(num);
}
