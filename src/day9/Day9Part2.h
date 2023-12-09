#pragma once

#include <string>
#include <vector>
#include <deque>

class Day9Part2
{
public:
	int64_t solve();
private:
	template<typename T>
	bool IsAllZero(const T& collection) const;
	void parse(const std::string& path, std::vector<std::deque<int64_t>>& inputOut) const;
};
