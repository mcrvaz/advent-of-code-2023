#pragma once

#include <unordered_map>
#include <string>

class Day1Part2
{
public:
	int solve();
private:
	int stoi(const std::string& num, const std::unordered_map<std::string, int>& textDigits) const;
};
