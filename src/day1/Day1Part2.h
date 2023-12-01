#pragma once

#include <map>
#include <string>

class Day1Part2
{
public:
	int solve();
private:
	int stoi(const std::string& num, const std::map<std::string, int>& textDigits) const;
};
