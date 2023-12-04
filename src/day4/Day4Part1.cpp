#include "Day4Part1.h"
#include <vector>
#include <string>
#include "../utils/Utils.h"
#include <algorithm>
#include <set>
#include <iterator>
#include <iostream>
#include <ranges>

double Day4Part1::solve()
{
	const std::vector<std::string> lines = *Utils::read_lines("input/day4part1_input.txt").get();
	double result{};
	for (const auto& line : lines)
	{
		std::vector<std::string> allValues = Utils::split(line, ":");
		std::vector<std::string> splitValues = Utils::split(allValues[1], "|");
		std::vector<std::string> winningValuesStr = Utils::split(splitValues[0], " ");
		std::vector<std::string> selectedValuesStr = Utils::split(splitValues[1], " ");

		auto winningValuesRange = winningValuesStr
			| std::views::filter([](const std::string& x) { return !Utils::is_empty_or_ws(x); })
			| std::views::transform([](const std::string& x) { return stoi(x); });

		std::set<int> winningValues{};
		for (const int i : winningValuesRange)
			winningValues.insert(i);

		auto selectedValuesRange = selectedValuesStr
			| std::views::filter([](const std::string& x) { return !Utils::is_empty_or_ws(x); })
			| std::views::transform([](const std::string& x) { return stoi(x); });
		std::set<int> selectedValues{};
		for (const int i : selectedValuesRange)
			selectedValues.insert(i);

		std::vector<int> intersection{};
		std::ranges::set_intersection(
			selectedValues,
			winningValues,
			std::back_inserter(intersection)
		);

		size_t winningNumbersCount = intersection.size();
		if (winningNumbersCount > 0)
		{
			double points = std::pow(2, winningNumbersCount - 1);
			result += points;
		}
	}

	// answer 25571
	std::cout << result;

	return result;
}
