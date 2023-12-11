#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <optional>

class Day10Part2
{
public:
	static const std::pair<int, int> UP;
	static const std::pair<int, int> DOWN;
	static const std::pair<int, int> RIGHT;
	static const std::pair<int, int> LEFT;
	static const std::unordered_map<char, std::vector<std::pair<int, int>>> VALID_MOVEMENTS;

	int solve();
private:
	int GetPolygonArea(std::vector<std::pair<int, int>> polygon) const;
	void BFS(
		const std::vector<std::string>& grid,
		const std::pair<int, int>& index,
		std::unordered_set<std::pair<int, int>>& visited
	) const;
	std::pair<int, int> GetStartingPosition(const std::vector<std::string>& lines) const;
};
