#include "Day10Part2.h"
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
#include <optional>

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

const std::pair<int, int> Day10Part2::UP{ -1, 0 };
const std::pair<int, int> Day10Part2::DOWN{ 1, 0 };
const std::pair<int, int> Day10Part2::RIGHT{ 0, 1 };
const std::pair<int, int> Day10Part2::LEFT{ 0, -1 };
const std::unordered_map<char, std::vector<std::pair<int, int>>> Day10Part2::VALID_MOVEMENTS
{
	{ 'S', { Day10Part2::UP, Day10Part2::DOWN, Day10Part2::RIGHT, Day10Part2::LEFT } },
	{ '.', {} },
	{ '|', { Day10Part2::UP, Day10Part2::DOWN } },
	{ '-', { Day10Part2::RIGHT, Day10Part2::LEFT } },
	{ 'L', { Day10Part2::UP, Day10Part2::RIGHT } },
	{ 'J', { Day10Part2::UP, Day10Part2::LEFT } },
	{ '7', { Day10Part2::DOWN, Day10Part2::LEFT } },
	{ 'F', { Day10Part2::DOWN, Day10Part2::RIGHT } },
};

int Day10Part2::solve()
{
	const std::vector<std::string> lines = *Utils::read_lines("input/day10part2_example.txt").get();

	// Pick's theorem
	// "i" is the number of integer points interior to the polygon
	// "b" is the number of points on its boundary
	// "A" is the area of the polygon
	// A = i + (b/2) - 1
	// We want to find "i"
	// i = A - (b/2) + 1
	const std::pair<int, int> start = GetStartingPosition(lines);
	std::unordered_set<std::pair<int, int>> visited;
	BFS(lines, start, visited);
	int pointsOnBoundary = static_cast<int>(visited.size());

	std::vector<std::pair<int, int>> polygon{};
	polygon.insert(polygon.end(), visited.begin(), visited.end());
	int area = GetPolygonArea(polygon);

	int result = area - (pointsOnBoundary / 2) + 1;
	std::cout << result;
	return result;
}

int Day10Part2::GetPolygonArea(std::vector<std::pair<int, int>> polygon) const
{
	// Shoelace formula
	// Sum of the 2x2 matrix determinants
	// A = 1/2 * |x0 x1| + |x1 x2| + |xn x1|
	//           |y0 y1|   |y1 y2|   |yn y1|
	auto MatrixDeterminant = [](const std::pair<int, int> p1, const std::pair<int, int> p2) {
		const auto& [x0, y0] = p1;
		const auto& [x1, y1] = p2;
		return (x0 * y1) - (x1 * y0);
		};

	int area{};
	polygon.push_back(polygon[0]);
	for (size_t i = 0; i < polygon.size() - 1; i++)
		area += MatrixDeterminant(polygon[i], polygon[i + 1]);

	return std::abs(area) / 2;
}

void Day10Part2::BFS(
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
		const auto& parentValidMovements = Day10Part2::VALID_MOVEMENTS.at(parent);
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
			const auto& childValidMovements = Day10Part2::VALID_MOVEMENTS.at(child);
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

std::pair<int, int> Day10Part2::GetStartingPosition(const std::vector<std::string>& lines) const
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