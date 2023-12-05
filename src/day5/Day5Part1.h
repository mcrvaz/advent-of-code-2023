#pragma once

#include <vector>
#include <string>

class Day5Part1
{
public:
	int64_t solve();
private:
	class ConversionMapEntry
	{
	public:
		int64_t DestinationStart;
		int64_t SourceStart;
		int64_t RangeLength;

		bool GetDestination(int64_t source, int64_t& destinationOut) const;
	};

	void parse(
		const std::string& path,
		std::vector<int64_t>& seedsOut,
		std::vector<std::vector<ConversionMapEntry>>& mapsOut
	) const;
};
