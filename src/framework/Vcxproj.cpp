#include "Vcxproj.h"
#include <pugixml.hpp>

using Path = std::filesystem::path;

Vcxproj::Vcxproj(const Path root) : m_root{ root }, m_vcxprojPath{ GetVcxprojPath() }
{
}

bool Vcxproj::Load()
{
	if (m_loaded)
		return true;

	m_doc = std::make_unique<pugi::xml_document>();
	const pugi::xml_parse_result result = m_doc->load_file(m_vcxprojPath.generic_wstring().c_str());
	m_loaded = result.status == pugi::xml_parse_status::status_ok;
	return m_loaded;
}

void Vcxproj::RegisterFiles(const std::vector<Path>& files, bool save)
{
	if (!m_loaded)
		throw std::runtime_error{ std::format("Trying to register files before loading {}.", EXTENSION) };

	if (files.empty())
		return;

	for (const auto& file : files)
		RegisterFile(file, false);

	if (!save)
		return;

	Save();
}

void Vcxproj::RegisterFile(const Path& file, bool save)
{
	if (!m_loaded)
		throw std::runtime_error{ std::format("Trying to register files before loading {}.", EXTENSION) };

	if (file.empty())
		return;

	bool isFileRegistered = IsFileRegistered(file);
	if (isFileRegistered)
		return;

	const Path relativePath = file.lexically_relative(m_root);
	const std::string relativePathStr = file.lexically_relative(m_root).string();
	const std::string extension = relativePath.extension().string();
	const std::string mapping{ GetMapping(extension) };

	pugi::xml_node parentNode = GetOrCreateAutoGeneratedNode();
	pugi::xml_node newNode = parentNode.append_child(mapping.c_str());
	newNode.append_attribute("Include").set_value(relativePathStr.c_str());

	if (!save)
		return;

	Save();
}

bool Vcxproj::Save()
{
	return m_doc->save_file(GetVcxprojPath().c_str());
}

bool Vcxproj::IsFileRegistered(const Path& file) const
{
	const Path relativePath = file.lexically_relative(m_root);
	const std::string relativePathStr = file.lexically_relative(m_root).string();
	const std::string xpathQuery = XML_ROOT + "/ItemGroup";
	for (const pugi::xpath_node& itemGroupNode : m_doc->select_nodes(xpathQuery.c_str()))
	{
		for (const pugi::xml_node& node : itemGroupNode.node().children())
		{
			const std::string_view nodeName = node.name();
			if (nodeName == relativePathStr)
				return true;
		}
	}
	return false;
}

pugi::xml_node Vcxproj::GetOrCreateAutoGeneratedNode()
{
	if (m_autoGeneratedNode.has_value())
		return m_autoGeneratedNode.value();

	const std::string xpathQuery = "/" + XML_ROOT + "/ItemGroup[Label='auto_generated']";
	pugi::xpath_node parentNode = m_doc->select_node(xpathQuery.c_str());
	if (parentNode)
	{
		m_autoGeneratedNode = parentNode.node();
		return m_autoGeneratedNode.value();
	}

	pugi::xml_node node = m_doc->select_node(XML_ROOT.c_str())
		.node()
		.append_child("ItemGroup");
	node.append_attribute("Label").set_value("auto_generated");
	m_autoGeneratedNode = node;
	return m_autoGeneratedNode.value();
}

std::filesystem::path Vcxproj::GetVcxprojPath() const
{
	for (const auto& dir : std::filesystem::directory_iterator(m_root))
	{
		if (dir.path().extension() == EXTENSION)
			return dir.path();
	}
	throw std::runtime_error{ std::format("{} not found!", EXTENSION) };
}

std::string_view Vcxproj::GetMapping(const std::string& extension) const
{
	for (const auto& [extensions, mappedValue] : extensionMapping)
	{
		if (extensions.contains(extension))
			return mappedValue;
	}
	throw std::runtime_error{ std::format("No mapping found for extension {}.", extension) };
}