#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>
#include <memory>
#include "utils.h"

using std::unique_ptr, std::string, std::vector;

template<typename T>
unique_ptr<vector<T>> Utils::read_input(const string& fileName)
{
	std::ifstream file(fileName);
	assert(file.is_open());

	auto nums = std::make_unique<vector<T>>();
	string line;
	while (getline(file, line)) {
		nums->push_back(stoi(line));
	}

	return nums;
}

unique_ptr<vector<string>> Utils::read_lines(const string& fileName)
{
	std::ifstream file(fileName);
	assert(file.is_open());

	auto nums = std::make_unique<vector<string>>();
	string line;
	while (getline(file, line)) {
		nums->push_back(line);
	}

	return nums;
}

vector<string> Utils::split(const string& s, const string& delimiter) {
	const size_t delim_len{ delimiter.length() };
	size_t pos_start{ 0 };
	size_t pos_end;
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

string& Utils::rtrim(string& s)
{
	const char* ws = " \t\n\r\f\v";
	s.erase(s.find_last_not_of(ws) + 1);
	return s;
}

string& Utils::ltrim(string& s)
{
	const char* ws = " \t\n\r\f\v";
	s.erase(0, s.find_first_not_of(ws));
	return s;
}

string& Utils::trim(string& s)
{
	return ltrim(rtrim(s));
}

string& Utils::to_lower(std::string& s)
{
	std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::tolower(c); });
	return s;
}

string Utils::to_lower(const std::string& s)
{
	std::string result{ s };
	to_lower(result);
	return result;
}

string Utils::reverse(const std::string& s)
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
