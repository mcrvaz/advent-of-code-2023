#include "FileGenerator.h"
#include "../utils/Utils.h"
#include <fstream>
#include <inja.hpp>
#include <pugixml.hpp>
#include <unordered_set>
#include <regex>

using Path = std::filesystem::path;

FileGenerator::FileGenerator(const Path root)
	: m_root{ root },
	m_src{ Path{ root }.append("src") },
	m_input{ Path{ root }.append("input") },
	m_templates{ Path{ root }.append("src/framework/templates") },
	m_vcxproj{ root }
{
}

void FileGenerator::CreateTemplate(int day)
{
	std::vector<Path> createdFiles{};
	const int PARTS = 2;
	for (int i = 1; i <= PARTS; i++)
	{
		Path path = CreateDefinitionFile(m_src, day, i);
		if (!path.empty())
			createdFiles.push_back(path);
		path = CreateImplementationFile(m_src, day, i);
		if (!path.empty())
			createdFiles.push_back(path);

		path = CreateInputFile(m_input, day, i, true);
		if (!path.empty())
			createdFiles.push_back(path);

		path = CreateInputFile(m_input, day, i, false);
		if (!path.empty())
			createdFiles.push_back(path);
	}
	RegisterProjectFiles(createdFiles);
}

Path FileGenerator::CreateDefinitionFile(const Path& path, int day, int part) const
{
	return CreateSourceFile(path, "day-src-template-cpp.txt", ".cpp", day, part);
}

Path FileGenerator::CreateImplementationFile(const Path& path, int day, int part) const
{
	return CreateSourceFile(path, "day-src-template-h.txt", ".h", day, part);
}

Path FileGenerator::CreateSourceFile(
	const Path& path,
	const std::string_view templateName,
	const std::string_view extension,
	int day,
	int part
) const
{
	Path directory{ path };
	directory.append(std::format("day{}", day));
	std::filesystem::create_directory(directory);

	const std::string fileName = std::format("Day{}Part{}{}", day, part, extension);
	Path filePath{ directory };
	filePath.append(fileName);
	if (std::filesystem::exists(filePath))
	{
		// TODO log some kind of warning
		return Path{};
	}

	inja::Environment env;
	Path templatePath{ m_templates };
	templatePath.append(templateName);
	const inja::Template temp = env.parse_template(templatePath.string());
	const inja::json data{ {"day", day }, {"part", part} };
	env.write(temp, data, filePath.string());
	return filePath;
}

Path FileGenerator::CreateInputFile(const Path& path, int day, int part, bool isExample) const
{
	const std::string suffix = isExample ? "example" : "input";
	const std::string fileName = std::format("day{}_{}.txt", day, suffix);
	Path filePath{ path };
	filePath.append(fileName);
	if (std::filesystem::exists(filePath))
	{
		// TODO log some kind of warning
		return Path{};
	}

	std::ofstream file(filePath, std::ofstream::out);
	return filePath;
}

Path FileGenerator::CreateTestFile(const Path& path, int day, int part) const
{
	return Path{};
}

void FileGenerator::RegisterRunnerFiles(const std::vector<std::filesystem::path>& files)
{
	if (files.empty())
		return;

	inja::Environment env;
	Path templatePath{ Path{ m_templates }.append("days-header-template-h.txt") };
	Path outputPath{ Path{ m_src }.append("AoCDays.h") };
	const inja::Template temp = env.parse_template(templatePath.string());
	inja::json data;

	const std::regex rgx("Day(\\w+)Part(\\w+)");
	std::smatch matches;
	std::vector<std::pair<int, int>> existingDayFiles;
	for (const auto& file : std::filesystem::recursive_directory_iterator(m_src))
	{
		if (!file.is_regular_file())
			continue;

		const std::string& pathStem = file.path().stem().string();
		if (!std::regex_search(pathStem, matches, rgx))
			continue;
		existingDayFiles.push_back({ std::stoi(matches[1].str()), std::stoi(matches[2].str()) });
	}

	std::vector<std::pair<int, int>> newFiles;
	for (const auto& file : files)
	{
		const std::string& pathStem = file.stem().string();
		if (!std::regex_search(pathStem, matches, rgx))
			continue;
		newFiles.push_back({ std::stoi(matches[1].str()), std::stoi(matches[2].str()) });
	}

	std::vector<std::pair<int, int>> allFiles{};
	allFiles.insert(std::end(existingDayFiles), std::begin(newFiles), std::end(newFiles));

	data["dayParts"] = std::move(allFiles);
	env.write(temp, data, outputPath.string());
}

void FileGenerator::RegisterProjectFiles(const std::vector<Path>& registeredFiles)
{
	if (registeredFiles.empty())
		return;

	m_vcxproj.Load();
	m_vcxproj.RegisterProjectFiles(registeredFiles, true);
}
