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
	void CreateTemplate(int day);

protected:
	std::filesystem::path CreateDefinitionFile(const std::filesystem::path& path, int day, int part) const;
	std::filesystem::path CreateImplementationFile(const std::filesystem::path& path, int day, int part) const;
	std::filesystem::path CreateSourceFile(
		const std::filesystem::path& path,
		const std::string_view templateName,
		const std::string_view extension,
		int day,
		int part
	) const;
	std::filesystem::path CreateTestFile(const std::filesystem::path& path, int day, int part) const;
	std::filesystem::path CreateInputFile(const std::filesystem::path& path, int day, int part, bool isExample) const;
	std::filesystem::path GetVcxprojPath() const;
	void RegisterRunnerFiles(const std::vector<std::filesystem::path>& files);
	void RegisterProjectFiles(const std::vector<std::filesystem::path>& files);
private:
	const std::filesystem::path m_root;
	const std::filesystem::path m_src;
	const std::filesystem::path m_input;
	const std::filesystem::path m_templates;
	Vcxproj m_vcxproj;
};
