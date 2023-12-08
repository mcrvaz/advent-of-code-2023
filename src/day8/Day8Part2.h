#pragma once

#include<string>
#include<unordered_map>

class Day8Part2
{
public:
	int64_t solve();

private:
	static bool EndsWithChar(const std::string& s, char c);

	int GetStepsToEndOfPath(
		const std::string& directions,
		const std::unordered_map<std::string, std::pair<std::string, std::string>>& map,
		const std::string& start
	) const;

	void parse(
		const std::string& path,
		std::string& directionsOut,
		std::unordered_map<std::string, std::pair<std::string, std::string>>& mapOut
	) const;
};
