#pragma once

class Utils
{
	template<typename T>
	std::unique_ptr<std::vector<T>> read_input(const std::string& fileName);

	std::unique_ptr<std::vector<std::string>> read_lines(const std::string& fileName);

	std::vector<std::string> split(const std::string& s, const std::string& delimiter);

	std::string& rtrim(std::string& s);

	std::string& ltrim(std::string& s);

	std::string& trim(std::string& s);
};

