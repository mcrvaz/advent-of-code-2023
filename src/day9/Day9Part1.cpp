#include "Day9Part1.h"
#include "../utils/Utils.h"
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <fstream>
#include <iostream>
#include <algorithm>

int64_t Day9Part1::solve()
{
	auto IsAllZero = [](const std::vector<int64_t>& collection) {
		return std::all_of(
			collection.begin(),
			collection.end(),
			[](int64_t x) { return x == 0; }
		);
		};

	std::vector<std::vector<int64_t>> input;
	parse("input/day9part1_input.txt", input);
	int64_t result{};
	for (const std::vector<int64_t>& history : input)
	{
		std::vector<std::vector<int64_t>> differences{ history };
		std::vector<int64_t> current{ differences[0] };
		bool allZero{ IsAllZero(current) };
		while (!allZero)
		{
			std::vector<int64_t> next{};
			for (size_t i = 0; i < current.size() - 1; i++)
			{
				int64_t diff = current[i + 1] - current[i];
				next.push_back(diff);
			}
			current = next;
			differences.push_back(current);
			allZero = IsAllZero(current);
		}

		for (size_t i = differences.size() - 1; i >= 1; i--)
		{
			std::vector<int64_t>& upperRow = differences[i - 1];
			std::vector<int64_t>& lowerRow = differences[i];
			int64_t upper = *upperRow.rbegin();
			int64_t lower = *lowerRow.rbegin();
			int64_t extrapolation = upper + lower;
			upperRow.push_back(extrapolation);
			if (i == 1)
				result += extrapolation;
		}
	}

	std::cout << result;

	return result;
}

void Day9Part1::parse(
	const std::string& path,
	std::vector<std::vector<int64_t>>& inputOut
) const
{
	std::ifstream file(path);
	assert(file.is_open());

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string word;
		std::vector<int64_t> current{};
		while (ss >> word)
			current.push_back(stoll(word));
		inputOut.push_back(current);
	}
}