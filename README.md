# advent-of-code-2023
AoC 2023 in C++

# Requirements
**This project is only compatible with Visual Studio.**

# Framework Usage
This project contains utilities for generating templates and executing AoC puzzles.

## Create
You can run the program with the following arguments to create a template:
`create [-d, --day] <number>` 

Example:
`create -d 10` 

This creates the following files for Day 10:
```
- input
	- day10part1_example.txt
	- day10part2_example.txt
- src
	- day10
		- Day10Part1.cpp
		- Day10Part1.h
		- Day10Part2.cpp
		- Day10Part2.h
```
And register the files in the `.vcxproj` and `src/AoCDays.h` file, which is later used for executing the puzzles.

## Execute
You can run the program with the following arguments to execute a puzzle:
`execute [-d, --day] <number> [-p, --part] <number>` 

Example:
`execute -d 10 -p 2`

This runs the puzzle for Day 10 - Part 2.