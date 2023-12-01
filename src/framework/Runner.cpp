#include "Runner.h"
#include "../AoCDays.h"

void Runner::Run(int day, int part)
{
	AoC::Execute(day, part);
}

void Runner::RunAll()
{
	for (int i = 1; i <= 25; i++)
	{
		for (int j = 1; j <= 2; j++)
			AoC::Execute(i, j);
	}
}
