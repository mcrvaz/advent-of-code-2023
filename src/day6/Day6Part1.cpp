#include "Day6Part1.h"
#include "../utils/Utils.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <numeric>

int Day6Part1::solve()
{
	std::unordered_map<int, int> races{ parse("input/day6part1_input.txt") };
	std::vector<int> waysToVictory{};
	for (const auto& [time, distance] : races)
	{
		// D = V*T
		// V = Th * Tt
		// D = Th * (Tt - Th)
		// Th * Tt - Th^2 - D = 0
		// quadratic formula ax2 + bx + c = 0
		// determinant = b^2 - 4ac;
		// root1 = (-b + sqrt(b^2 - 4ac)) / 2a
		// root2 = (-b - sqrt(b^2 - 4ac)) / 2a
		// a = 1, x = Th, b = Tt, c = D

		int a = 1;
		int b = time;
		int c = distance;
		int determinant = (b * b) - (4 * a * c);
		if (determinant == 0)
		{
			waysToVictory.push_back(1);
		}
		else if (determinant > 0)
		{
			double root1 = (-b + std::sqrt(determinant)) / 2 * a;
			double root2 = (-b - std::sqrt(determinant)) / 2 * a;
			double r1 = std::ceil(root1);
			double r2 = std::floor(root2);
			waysToVictory.push_back(std::abs(r2 - r1 + 1));
		}
		else
		{
			throw std::runtime_error("No real roots for the current race.");
		}
	}

	int result = std::reduce(
		waysToVictory.begin(),
		waysToVictory.end(),
		1,
		[](int acc, int v) { return acc * v; }
	);

	// answer 170000
	std::cout << result;

	return result;
}

std::unordered_map<int, int> Day6Part1::parse(const std::string& path) const
{
	const std::vector<std::string> lines = *Utils::read_lines(path).get();
	std::vector<std::string> timesStr = Utils::split(Utils::split(lines[0], ":")[1], " ");
	std::vector<std::string> distanceStr = Utils::split(Utils::split(lines[1], ":")[1], " ");
	std::unordered_map<int, int> races{};
	for (int i = 0; i < timesStr.size(); i++)
		races[stoi(timesStr[i])] = stoi(distanceStr[i]);
	return races;
}