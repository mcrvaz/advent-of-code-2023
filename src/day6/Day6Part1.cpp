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
	const std::vector<std::string> lines = *Utils::read_lines("input/day6part1_input.txt").get();
	auto timesStr = Utils::split(Utils::split(lines[0], ":")[1], " ");
	auto distanceStr = Utils::split(Utils::split(lines[1], ":")[1], " ");
	std::unordered_map<int, int> races{};
	for (int i = 0; i < timesStr.size(); i++)
		races[stoi(timesStr[i])] = stoi(distanceStr[i]);

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

		auto a = 1;
		auto b = time;
		auto c = distance;

		auto determinant = (b * b) - (4 * a * c);
		if (determinant == 0)
		{
			waysToVictory.push_back(1);
		}
		else if (determinant > 0)
		{
			auto root1 = (-b + std::sqrt(determinant)) / 2 * a;
			auto root2 = (-b - std::sqrt(determinant)) / 2 * a;
			auto r1 = std::ceil(root1);
			auto r2 = std::floor(root2);
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

	std::cout << result;

	return result;
}
