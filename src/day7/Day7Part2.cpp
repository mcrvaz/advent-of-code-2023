#include "Day7Part2.h"
#include "../utils/Utils.h"
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <unordered_map>
#include <set>
#include <iterator>
#include <algorithm>

using Hand = Day7Part2::Hand;

int64_t Day7Part2::solve()
{
	std::vector<Hand> hands{ parse("input/day7part2_input.txt") };
	std::sort(hands.begin(), hands.end());

	int64_t winnings{};
	size_t size{ hands.size() };
	for (size_t i = 0; i < size; i++)
	{
		const Hand& hand = hands[i];
		const size_t rank = i + 1;
		winnings += rank * hand.Bid();
	}

	// answer 253499763
	std::cout << winnings;

	return winnings;
}

bool Day7Part2::Hand::operator<(const Hand& rhs) const
{
	if (m_type == rhs.m_type)
	{
		for (int i = 0; i < Hand::HAND_SIZE; i++)
		{
			auto lhsIndex = std::distance(
				cards.begin(),
				std::find(cards.begin(), cards.end(), m_hand[i])
			);
			auto rhsIndex = std::distance(
				cards.begin(),
				std::find(cards.begin(), cards.end(), rhs.m_hand[i])
			);
			if (lhsIndex == rhsIndex)
				continue;
			return lhsIndex < rhsIndex;
		}
		return false;
	}

	return m_type < rhs.m_type;
}

std::vector<Hand> Day7Part2::parse(const std::string& path)
{
	std::ifstream file(path);
	assert(file.is_open());

	std::vector<Hand> hands;
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string word;
		ss >> word;
		std::string hand{ word };
		ss >> word;
		int bid = stoi(word);
		hands.push_back(Hand(hand, bid));
	}
	return hands;
}

Day7Part2::Hand::Hand(const std::string& hand, int bid) : m_hand{ hand }, m_bid{ bid }
{
	for (char c : hand)
		m_cardCount[c]++;

	m_type = GetHandType();
}

Day7Part2::HandType Day7Part2::Hand::GetHandType() const
{
	std::unordered_map<char, int> cardCount{ m_cardCount };
	if (cardCount.contains('J'))
	{
		const int jCount = cardCount.at('J');
		if (jCount == HAND_SIZE)
			return HandType::FiveKind;

		cardCount.erase('J');

		std::pair<char, int> max = *std::max_element(
			cardCount.begin(),
			cardCount.end(),
			[](const auto& p1, const auto& p2) { return p1.second < p2.second; }
		);
		cardCount[max.first] += jCount;
	}

	if (cardCount.size() == 1)
		return HandType::FiveKind;

	if (cardCount.size() == 2)
	{
		const auto& [card, count] = *cardCount.begin();
		if (count == 4 || count == 1)
			return HandType::FourKind;
		else
			return HandType::FullHouse;
	}

	if (cardCount.size() == 3)
	{
		for (const auto& [card, count] : cardCount)
		{
			if (count == 3)
				return HandType::ThreeKind;
			if (count == 2)
				return HandType::TwoPair;
		}
	}

	if (cardCount.size() == 4)
		return HandType::OnePair;

	return HandType::HighCard;
}
