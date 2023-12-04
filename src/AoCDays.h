// This file is auto generated.

#pragma once

#include "day1/Day1Part1.h"
#include "day1/Day1Part2.h"
#include "day2/Day2Part1.h"
#include "day2/Day2Part2.h"
#include "day3/Day3Part1.h"
#include "day3/Day3Part2.h"
#include "day4/Day4Part1.h"
#include "day4/Day4Part2.h"

namespace AoC
{
	static void Execute(int day, int part)
	{
		if (day == 1 && part == 1)
			Day1Part1().solve();
		else if (day == 1 && part == 2)
			Day1Part2().solve();
		else if (day == 2 && part == 1)
			Day2Part1().solve();
		else if (day == 2 && part == 2)
			Day2Part2().solve();
		else if (day == 3 && part == 1)
			Day3Part1().solve();
		else if (day == 3 && part == 2)
			Day3Part2().solve();
		else if (day == 4 && part == 1)
			Day4Part1().solve();
		else if (day == 4 && part == 2)
			Day4Part2().solve();
	}
};
