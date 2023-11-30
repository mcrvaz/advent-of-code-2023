#include <iostream>
#include "framework/CommandLineInterface.h"

int main(int argc, char** argv)
{
	auto parser = MyCLI::Parser(argc, argv);
	auto options = parser.Parse();
	options.Print();
}
