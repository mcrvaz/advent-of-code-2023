#pragma once

#include <string>
#include <vector>

class Day9Part1
{
public:
	int64_t solve();
	void parse(const std::string& path, std::vector<std::vector<int64_t>>& inputOut) const;
};
