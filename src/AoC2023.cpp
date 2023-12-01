#include <iostream>
#include "framework/CommandLineInterface.h"
#include "framework/FileGenerator.h"
#include "AoCDays.h"
#include <inja.hpp>

#define DAY_PART(day, part) Day##day##Part##part##{}

#define TEST(day, day_index, part, part_index) \
	if (day_index == day && part_index == part) { \
			DAY_PART(day, part).solve();  \
	}\

#define LOOP(day_start, day_end, part_start, part_end)                  \
	for (int i = (day_start); i <= (day_end); i++) { \
		for (int j = (part_start); j <= (part_end); j++) { \
			DAY_PART(i, j).solve(); \
		} \
	} \

int main(int argc, char** argv)
{
	using Path = std::filesystem::path;

	inja::Environment env;
	Path root{ std::filesystem::current_path() };
	Path templatePath{ Path{ root }.append("src").append("framework").append("templates").append("days-header-template-h.txt") };
	Path outputPath{ Path{ root }.append("src").append("AoCDays.h") };
	const inja::Template temp = env.parse_template(templatePath.string());
	inja::json data;

	std::vector<std::pair<int, int>> dayParts{};
	for (int i = 1; i <= 25; i++)
	{
		for (int j = 1; j <= 2; j++)
			dayParts.push_back({ i, j });
	}
	data["dayParts"] = dayParts;
	env.write(temp, data, outputPath.string());

	//MyCLI::Parser parser = MyCLI::Parser(argc, argv);
	//MyCLI::Options options = parser.Parse();
	//options.Print();

	//switch (options.OpType)
	//{
	//case MyCLI::OperationType::execute:
	//	break;
	//case MyCLI::OperationType::create:
	//	auto fileGenerator = FileGenerator(std::filesystem::current_path());
	//	fileGenerator.CreateTemplate(options.Day);
	//	break;
	//}

	return 0;
}
