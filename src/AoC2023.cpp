#include <iostream>
#include "framework/CommandLineInterface.h"
#include "framework/FileGenerator.h"
#include "framework/Runner.h"
#include <inja.hpp>

int main(int argc, char** argv)
{
	MyCLI::Parser parser = MyCLI::Parser(argc, argv);
	MyCLI::Options options = parser.Parse();
	options.Print();

	switch (options.OpType)
	{
	case MyCLI::OperationType::execute:
		Runner::Run(options.Day, options.Part);
		break;
	case MyCLI::OperationType::create:
		auto fileGenerator = FileGenerator(std::filesystem::current_path());
		fileGenerator.CreateTemplate(options.Day);
		break;
	}

	return 0;
}
