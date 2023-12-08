#pragma once

#include<string>
#include<unordered_map>

class Day8Part1
{
public:
	int solve();

private:
	void parse(
		const std::string& path,
		std::string& directionsOut,
		std::unordered_map<std::string, std::pair<std::string, std::string>>& mapOut
	) const;
};
