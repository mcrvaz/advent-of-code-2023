#include "Day6Part2.h"
#include "../utils/Utils.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <numeric>

int64_t Day6Part2::solve()
{
	const auto& [time, distance] { parse("input/day6part2_input.txt") };
	// D = V*T
	// V = Th * Tt
	// D = Th * (Tt - Th)
	// Th * Tt - Th^2 - D = 0
	// quadratic formula ax2 + bx + c = 0
	// determinant = b^2 - 4ac;
	// root1 = (-b + sqrt(b^2 - 4ac)) / 2a
	// root2 = (-b - sqrt(b^2 - 4ac)) / 2a
	// a = 1, x = Th, b = Tt, c = D

	int64_t result{};
	int64_t a = 1;
	int64_t b = time;
	int64_t c = distance;
	int64_t determinant = (b * b) - (4 * a * c);
	if (determinant == 0)
	{
		result = 1;
	}
	else if (determinant > 0)
	{
		double root1 = (-b + std::sqrt(determinant)) / 2 * a;
		double root2 = (-b - std::sqrt(determinant)) / 2 * a;
		double r1 = std::ceil(root1);
		double r2 = std::floor(root2);
		result = static_cast<int64_t>(std::abs(r2 - r1 + 1));
	}
	else
	{
		throw std::runtime_error("No real roots for the current race.");
	}

	// answer 20537782
	std::cout << result;

	return result;
}

std::pair<int64_t, int64_t> Day6Part2::parse(const std::string& path) const
{
	const std::vector<std::string> lines = *Utils::read_lines(path).get();
	auto timesStr = Utils::split(Utils::split(lines[0], ":")[1], " ");
	auto distanceStr = Utils::split(Utils::split(lines[1], ":")[1], " ");
	int64_t time = stoll(std::accumulate(
		timesStr.begin(),
		timesStr.end(),
		std::string{}
	));
	int64_t distance = stoll(std::accumulate(
		distanceStr.begin(),
		distanceStr.end(),
		std::string{}
	));
	return { time, distance };
}