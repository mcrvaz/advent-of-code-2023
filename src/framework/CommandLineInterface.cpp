#include "CommandLineInterface.h"
#include <CLI11.hpp>
#include <iostream>
#include <string>

MyCLI::Parser::Parser(int argc, char** argv) : m_argc{ argc }, m_argv{ argv }
{
}

MyCLI::Options MyCLI::Parser::Parse()
{
	CLI::App app{ "Advent of Code 2023" };

	OperationType op{};

	CLI::App* execute = app.add_subcommand("execute", "A great subcommand");
	CLI::App* create = app.add_subcommand("create", "Do you really want to stop?");
	app.require_subcommand(1);

	int day{};
	create->add_option("-d,--day", day, "Day to create")
		->required()
		->check(CLI::Range(1, 25));

	execute->add_option("-d,--day", day, "Day to execute")
		->required()
		->check(CLI::Range(1, 25));

	int part{};
	execute->add_option("-p,--part", part, "Part to execute")
		->required()
		->check(CLI::Range(1, 2));

	app.parse(m_argc, m_argv);

	CLI::App* subcommand = app.get_subcommand(0);
	if (subcommand == execute)
		op = OperationType::execute;
	else if (subcommand == create)
		op = OperationType::create;

	return Options{ op, day, part };
}

void MyCLI::Options::Print()
{
	std::cout << "OpType " << static_cast<int>(OpType) << " Day " << Day << " Part " << Part << '\n';
}

