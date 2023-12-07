#pragma once

#include <vector>
#include <string>
#include <set>
#include <optional>

class Day5Part2
{
public:
	int64_t solve();
private:
	struct Range
	{
		int64_t Start;
		int64_t End;

		Range() = default;
		Range(int64_t start, int64_t end);

		static Range FromLength(int64_t start, int64_t length);

		bool Overlap(const Range& other, Range& overlapOut) const;
		bool Contains(const Range& other) const;
	};

	class ConversionMapEntry
	{
	public:
		Range Destination;
		Range Source;

		Range Apply(const Range& range) const;

		bool operator<(const ConversionMapEntry& rhs) const
		{
			return Source.Start < rhs.Source.Start;
		}
	};

	void parse(
		const std::string& path,
		std::vector<Range>& seedsOut,
		std::vector<std::set<ConversionMapEntry>>& mapsOut
	) const;

	std::vector<Range> GetMappedRange(
		const std::set<ConversionMapEntry>& map,
		std::vector<Range>& input
	);
};
