#pragma once

#include <string_view>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>
#include "Vcxproj.h"

class FileGenerator
{
public:
	static inline const std::string CL_COMPILE = "ClCompile";
	static inline const std::string CL_INCLUDE = "ClInclude";
	static inline const std::string TEXT = "Text";

	explicit FileGenerator(const std::filesystem::path root);

	/// <summary>
	/// Creates the template for the provided day.
	/// This includes:
	///	- .cpp, .h files.
	/// - example and input txt files.
	/// - register the created files in the current Visual Studio project.
	/// - register the created files in the code runner.
	/// </summary>
	/// <param name="day">Puzzle day.</param>
	void CreateTemplate(int day);

protected:
	/// <summary>
	/// Creates .cpp file for the provided day and part.
	/// </summary>
	/// <param name="path">Path to the src folder.</param>
	/// <param name="day">Puzzle day.</param>
	/// <param name="part">Puzzle part.</param>
	/// <returns>Generated file path.</returns>
	std::filesystem::path CreateDefinitionFile(
		const std::filesystem::path& path,
		int day,
		int part
	) const;

	/// <summary>
	/// Creates .h file for the provided day and part.
	/// </summary>
	/// <param name="path">Path to the src folder.</param>
	/// <param name="day">Puzzle day.</param>
	/// <param name="part">Puzzle part.</param>
	/// <returns>Generated file path.</returns>
	std::filesystem::path CreateImplementationFile(
		const std::filesystem::path& path,
		int day,
		int part
	) const;

	/// <summary>
	/// Creates source file with the provided extensions for the provided day and part.
	/// </summary>
	/// <param name="path">Path to the src folder.</param>
	/// <param name="templateName">Template name to be used in the file creation.</param>
	/// <param name="extension">The file extension.</param>
	/// <param name="day">Puzzle day.</param>
	/// <param name="part">Puzzle day.</param>
	/// <returns>Generated file path.</returns>
	std::filesystem::path CreateSourceFile(
		const std::filesystem::path& path,
		const std::string_view templateName,
		const std::string_view extension,
		int day,
		int part
	) const;

	//std::filesystem::path CreateTestFile(const std::filesystem::path& path, int day, int part) const;

	/// <summary>
	/// Creates input files for the provided day and part.
	/// </summary>
	/// <param name="path">Input folder path.</param>
	/// <param name="day">Puzzle day.</param>
	/// <param name="part">Puzzle part.</param>
	/// <param name="isExample">True if it's the provided example, false if it's the actual puzzle input.</param>
	/// <returns>Generated file path.</returns>
	std::filesystem::path CreateInputFile(
		const std::filesystem::path& path,
		int day,
		int part,
		bool isExample
	) const;

	/// <summary>
	/// Gets the path to the .vcxproj file according to the provided root path.
	/// </summary>
	/// <returns>The .vcxproj file path.</returns>
	std::filesystem::path GetVcxprojPath() const;

	/// <summary>
	/// Register files in the auto generated AoCDays.h file.
	/// This auto generated file is used later to execute individual puzzles.
	/// </summary>
	/// <param name="files">Files to be registered.</param>
	void RegisterRunnerFiles(const std::vector<std::filesystem::path>& files) const;

	/// <summary>
	/// Register files to Visual Studio's .vcxproj file.
	/// </summary>
	/// <param name="registeredFiles">Files to be registered.</param>
	void RegisterProjectFiles(const std::vector<std::filesystem::path>& files);

private:
	const std::filesystem::path m_root;
	const std::filesystem::path m_src;
	const std::filesystem::path m_input;
	const std::filesystem::path m_templates;
	Vcxproj m_vcxproj;
};
