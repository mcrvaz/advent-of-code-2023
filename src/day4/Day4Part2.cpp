#include "Day4Part2.h"
#include "../utils/Utils.h"
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <iterator>
#include <iostream>
#include <ranges>
#include <numeric>

int Day4Part2::solve()
{
	const std::vector<std::string> lines = *Utils::read_lines("input/day4part2_input.txt").get();

	std::vector<int> cardCount(lines.size() + 1);
	for (const auto& line : lines)
	{
		const std::vector<std::string> allValues = Utils::split(line, ":");
		const std::vector<std::string> cardNumberSplit = Utils::split(allValues[0], " ");
		int cardNumber = stoi(Utils::split(allValues[0], " ")[cardNumberSplit.size() - 1]);

		const std::vector<std::string> splitValues = Utils::split(allValues[1], "|");
		const std::vector<std::string> winningValuesStr = Utils::split(splitValues[0], " ");
		const std::vector<std::string> selectedValuesStr = Utils::split(splitValues[1], " ");

		int duplicates = cardCount[cardNumber] + 1;
		int winningNumbersCount = GetWinningNumbersCount(winningValuesStr, selectedValuesStr);
		for (int i = 0; i < duplicates; i++)
		{
			for (int j = cardNumber + 1; j <= cardNumber + winningNumbersCount; j++)
				cardCount[j]++;
		}
	}

	int result = std::reduce(
		cardCount.begin(),
		cardCount.end(),
		0,
		[](int acc, int v) { return acc + v; }
	);
	result += static_cast<int>(lines.size());

	// answer 8805731
	std::cout << result;

	return result;
}

int Day4Part2::GetWinningNumbersCount(
	const std::vector<std::string>& winningValuesStr,
	const std::vector<std::string>& selectedValuesStr
) const
{
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

	return static_cast<int>(intersection.size());
}