#include "Day10Part1.h"
#include "../utils/Utils.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <deque>
#include <numeric>
#include <algorithm>
#include <ranges>

namespace std {
	template <> struct hash<std::pair<int, int>> {
		inline size_t operator()(const std::pair<int, int>& v) const {
			std::hash<int> int_hasher;
			return int_hasher(v.first) ^ int_hasher(v.second);
		}
	};

	static std::pair<int, int> operator +(const std::pair<int, int>& x, const std::pair<int, int>& y) {
		return std::make_pair(x.first + y.first, x.second + y.second);
	}
	static std::pair<int, int> operator *(const std::pair<int, int>& x, int y) {
		return std::make_pair(x.first * y, x.second * y);
	}
}

const std::pair<int, int> Day10Part1::UP{ -1, 0 };
const std::pair<int, int> Day10Part1::DOWN{ 1, 0 };
const std::pair<int, int> Day10Part1::RIGHT{ 0, 1 };
const std::pair<int, int> Day10Part1::LEFT{ 0, -1 };
const std::unordered_map<char, std::vector<std::pair<int, int>>> Day10Part1::VALID_MOVEMENTS
{
	{ 'S', { Day10Part1::UP, Day10Part1::DOWN, Day10Part1::RIGHT, Day10Part1::LEFT } },
	{ '.', {} },
	{ '|', { Day10Part1::UP, Day10Part1::DOWN } },
	{ '-', { Day10Part1::RIGHT, Day10Part1::LEFT } },
	{ 'L', { Day10Part1::UP, Day10Part1::RIGHT } },
	{ 'J', { Day10Part1::UP, Day10Part1::LEFT } },
	{ '7', { Day10Part1::DOWN, Day10Part1::LEFT } },
	{ 'F', { Day10Part1::DOWN, Day10Part1::RIGHT } },
};

int Day10Part1::solve()
{
	const std::vector<std::string> lines = *Utils::read_lines("input/day10part1_input.txt").get();
	const std::pair<int, int> start = GetStartingPosition(lines);
	std::unordered_set<std::pair<int, int>> visited;
	BFS(lines, start, visited);
	int result = static_cast<int>(visited.size()) / 2;

	// result 6613
	std::cout << "Result " << result << '\n';

	return result;
}

void Day10Part1::BFS(
	const std::vector<std::string>& grid,
	const std::pair<int, int>& start,
	std::unordered_set<std::pair<int, int>>& visited
) const
{
	std::deque<std::pair<int, int>> q{ start };
	visited.insert(start);
	while (!q.empty())
	{
		const std::pair<int, int> parentIndex = q.front();
		q.pop_front();
		const char parent = grid.at(parentIndex.first).at(parentIndex.second);
		const auto& parentValidMovements = Day10Part1::VALID_MOVEMENTS.at(parent);
		for (const std::pair<int, int>& mov : parentValidMovements)
		{
			const std::pair<int, int> childIndex = parentIndex + mov;
			if (visited.contains(childIndex))
				continue;

			bool isValidIndex = childIndex.first >= 0 && childIndex.first < grid.size()
				&& childIndex.second >= 0 && childIndex.second < grid[childIndex.first].size();
			if (!isValidIndex)
				continue;

			const char child = grid.at(childIndex.first).at(childIndex.second);
			const auto& childValidMovements = Day10Part1::VALID_MOVEMENTS.at(child);
			bool isConnectedToParent = std::any_of(
				childValidMovements.begin(),
				childValidMovements.end(),
				[&parentValidMovements](const auto& movement)
				{
					return std::find(
						parentValidMovements.begin(),
						parentValidMovements.end(),
						movement * -1
					) != parentValidMovements.end();
				}
			);
			if (!isConnectedToParent)
				continue;

			visited.insert(childIndex);
			q.push_back(childIndex);
		}
	}
}

std::pair<int, int> Day10Part1::GetStartingPosition(const std::vector<std::string>& lines)
{
	for (int i = 0; i < lines.size(); i++)
	{
		const auto& line = lines[i];
		for (int j = 0; j < line.size(); j++)
		{
			if (line[j] == 'S')
				return { i, j };
		}
	}
	throw std::runtime_error("No starting point found");
}