#pragma once

#include <memory>
#include <vector>
#include <string>

class Utils
{
public:
	template<typename T>
	static std::unique_ptr<std::vector<T>> read_input(const std::string& fileName);

	static std::unique_ptr<std::vector<std::string>> read_lines(const std::string& fileName);

	static std::vector<std::string> split(const std::string& s, const std::string& delimiter);

	static std::string& rtrim(std::string& s);

	static std::string& ltrim(std::string& s);

	static std::string& trim(std::string& s);

	static std::string& to_lower(std::string& s);

	static std::string to_lower(const std::string& s);

	static std::string reverse(const std::string& s);
};

