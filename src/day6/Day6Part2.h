#pragma once

#include <string>
#include <unordered_map>

class Day6Part2
{
public:
	int64_t solve();
private:
	std::pair<int64_t, int64_t> parse(const std::string& path) const;
};
