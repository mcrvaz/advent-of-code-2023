#include "Day3Part2.h"
#include <vector>
#include <string>
#include "../utils/Utils.h"
#include <regex>
#include <numeric>
#include <iostream>

int Day3Part2::solve()
{
	const std::vector<std::string> lines = *Utils::read_lines("input/day3part2_input.txt").get();

	long result{};
	for (int i = 0; i < lines.size(); i++)
	{
		const auto& line = lines[i];
		for (int j = 0; j < line.size(); j++)
		{
			char character = line[j];
			if (character == '*')
			{
				const auto& adjacent = GetAdjacentNumbers(lines, i, j);
				if (adjacent.size() == 2)
					result += adjacent[0] * adjacent[1];
			}
		}
	}

	// answer 81296995
	std::cout << result;

	return result;
}

std::vector<int> Day3Part2::GetAdjacentNumbers(
	const std::vector<std::string>& lines,
	int i,
	int j
)
{
	const std::pair<int, int> up{ i + 1, j };
	const std::pair<int, int> upRight{ i + 1, j + 1 };
	const std::pair<int, int> right{ i, j + 1 };
	const std::pair<int, int> downRight{ i - 1, j + 1 };
	const std::pair<int, int> down{ i - 1, j };
	const std::pair<int, int> downLeft{ i - 1, j - 1 };
	const std::pair<int, int> left{ i, j - 1 };
	const std::pair<int, int> upLeft{ i + 1, j - 1 };

	std::vector<std::pair<int, int>> adjacentPartialNumbersIndexes{};
	bool upValid = IsValidIndex(lines, up) && IsNumber(lines[up.first][up.second]);
	if (upValid)
		adjacentPartialNumbersIndexes.push_back(up);
	else
	{
		bool upLeftValid = IsValidIndex(lines, upLeft) && IsNumber(lines[upLeft.first][upLeft.second]);
		if (upLeftValid)
			adjacentPartialNumbersIndexes.push_back(upLeft);

		bool upRightValid = IsValidIndex(lines, upRight) && IsNumber(lines[upRight.first][upRight.second]);
		if (upRightValid)
			adjacentPartialNumbersIndexes.push_back(upRight);
	}

	bool rightValid = IsValidIndex(lines, right) && IsNumber(lines[right.first][right.second]);
	if (rightValid)
		adjacentPartialNumbersIndexes.push_back(right);

	bool leftValid = IsValidIndex(lines, left) && IsNumber(lines[left.first][left.second]);
	if (leftValid)
		adjacentPartialNumbersIndexes.push_back(left);

	bool downValid = IsValidIndex(lines, down) && IsNumber(lines[down.first][down.second]);
	if (downValid)
		adjacentPartialNumbersIndexes.push_back(down);
	else
	{
		bool downLeftValid = IsValidIndex(lines, downLeft) && IsNumber(lines[downLeft.first][downLeft.second]);
		if (downLeftValid)
			adjacentPartialNumbersIndexes.push_back(downLeft);

		bool downRightValid = IsValidIndex(lines, downRight) && IsNumber(lines[downRight.first][downRight.second]);
		if (downRightValid)
			adjacentPartialNumbersIndexes.push_back(downRight);

	}

	std::vector<int> result{};
	for (const auto& partialNumberIdx : adjacentPartialNumbersIndexes)
	{
		int firstDigit{};
		std::pair<int, int> idx{ partialNumberIdx };
		while (IsValidIndex(lines, idx) && IsNumber(lines[idx.first][idx.second]))
		{
			firstDigit = LiteralToInt(lines[idx.first][idx.second]);
			idx.second--;
		}

		int num{ firstDigit };
		idx.second++;
		idx.second++;
		while (IsValidIndex(lines, idx) && IsNumber(lines[idx.first][idx.second]))
		{
			num = (num * 10) + LiteralToInt(lines[idx.first][idx.second]);
			idx.second++;
		}
		result.push_back(num);
	}
	return result;
}

int Day3Part2::LiteralToInt(char c)
{
	return c - '0';
}

bool Day3Part2::IsValidIndex(const std::vector<std::string>& lines, std::pair<int, int> idx)
{
	auto [i, j] = idx;
	return (i >= 0 && i < lines.size()) && (j >= 0 && j < lines[i].size());
}

bool Day3Part2::IsNumber(char c)
{
	return c >= '0' && c <= '9';
}
