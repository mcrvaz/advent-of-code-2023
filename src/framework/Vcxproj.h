#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string_view>
#include <filesystem>
#include <pugixml.hpp>

class Vcxproj
{
public:
	static inline const std::string CL_COMPILE = "ClCompile";
	static inline const std::string CL_INCLUDE = "ClInclude";
	static inline const std::string TEXT = "Text";
	static inline const std::string EXTENSION = ".vcxproj";
	static inline const std::string XML_ROOT = "Project";

	explicit Vcxproj(const std::filesystem::path root);

	std::filesystem::path GetVcxprojPath() const;

	bool Load();
	void RegisterFiles(const std::vector<std::filesystem::path>& files, bool save = false);
	void RegisterFile(const std::filesystem::path& file, bool save = false);
	bool IsFileRegistered(const std::filesystem::path& file) const;
	bool Save();

private:
	static inline const std::unordered_set<std::string> relevantNodes
	{
		{ CL_COMPILE },
		{ CL_INCLUDE },
		{ TEXT },
	};
	static inline const std::vector<std::pair<std::unordered_set<std::string>, std::string>> extensionMapping
	{
		{ { ".cpp" }, CL_COMPILE },
		{ { ".h", ".hpp" }, CL_INCLUDE },
		{ { ".txt" }, TEXT },
	};

	const std::filesystem::path m_root{};
	const std::filesystem::path m_vcxprojPath{};
	std::optional<pugi::xml_node>m_autoGeneratedNode{};
	std::unique_ptr<pugi::xml_document> m_doc{};
	bool m_loaded{};

	std::string_view GetMapping(const std::string& extension) const;
	pugi::xml_node GetOrCreateAutoGeneratedNode();
};
