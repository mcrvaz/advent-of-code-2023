#pragma once

#include <vector>
#include <string>

class Day4Part2
{
public:
	int solve();
private:
	int GetWinningNumbersCount(
		const std::vector<std::string>& winningValuesStr, 
		const std::vector<std::string>& selectedValuesStr
	) const;
};
