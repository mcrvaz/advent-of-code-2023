#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <memory>
#include <sstream>
#include "utils.h"

std::unique_ptr<std::vector<std::string>> Utils::read_lines(const std::string& fileName)
{
	std::ifstream file(fileName);
	assert(file.is_open());

	auto nums = std::make_unique<std::vector<std::string>>();
	std::string line;
	while (getline(file, line)) {
		nums->push_back(line);
	}

	return nums;
}

std::vector<std::string> Utils::split(const std::string& s, const std::string& delimiter)
{
	const size_t delim_len{ delimiter.length() };
	size_t pos_start{ 0 };
	size_t pos_end;
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		if (!token.empty())
			res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

std::string& Utils::rtrim(std::string& s)
{
	const char* ws = " \t\n\r\f\v";
	s.erase(s.find_last_not_of(ws) + 1);
	return s;
}

std::string& Utils::ltrim(std::string& s)
{
	const char* ws = " \t\n\r\f\v";
	s.erase(0, s.find_first_not_of(ws));
	return s;
}

std::string& Utils::trim(std::string& s)
{
	return ltrim(rtrim(s));
}

std::string Utils::reverse(const std::string& s)
{
	std::string result{ s };
	std::reverse(result.begin(), result.end());
	return result;
}

bool Utils::is_empty_or_ws(const std::string& s)
{
	if (s.empty())
		return true;
	for (const char c : s)
	{
		if (!std::isspace(c))
			return false;
	}
	return true;
}
