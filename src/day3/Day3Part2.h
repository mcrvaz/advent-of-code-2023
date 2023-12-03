#pragma once

#include <vector>
#include <string>

class Day3Part2
{
public:
	int solve();

private:
	std::vector<int> GetAdjacentNumbers(
		const std::vector<std::string>& lines,
		int i,
		int j
	);
	int LiteralToInt(char c);
	bool IsValidIndex(const std::vector<std::string>& lines, std::pair<int, int> idx);
	bool IsNumber(char c);
};
