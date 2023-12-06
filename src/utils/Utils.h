#pragma once

#include <memory>
#include <vector>
#include <string>

class Utils
{
public:
	static std::unique_ptr<std::vector<std::string>> read_lines(const std::string& fileName);

	static std::vector<std::string> split(const std::string& s, const std::string& delimiter);

	static std::string& rtrim(std::string& s);

	static std::string& ltrim(std::string& s);

	static std::string& trim(std::string& s);

	static std::string reverse(const std::string& s);

	static bool is_empty_or_ws(const std::string& s);
};

