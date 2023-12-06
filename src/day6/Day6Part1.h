#pragma once

#include <string>
#include <unordered_map>

class Day6Part1
{
public:
	int solve();
private:
	std::unordered_map<int, int> parse(const std::string& path) const;
};
