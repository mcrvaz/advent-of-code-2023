#include "Day7Part1.h"
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

using Hand = Day7Part1::Hand;

int64_t Day7Part1::solve()
{
	std::vector<Hand> hands{ parse("input/day7part1_input.txt") };
	std::sort(hands.begin(), hands.end());

	int64_t winnings{};
	size_t size{ hands.size() };
	for (size_t i = 0; i < size; i++)
	{
		const Hand& hand = hands[i];
		const size_t rank = i + 1;
		winnings += rank * hand.Bid();
	}

	// answer 252656917
	std::cout << winnings;

	return winnings;
}

bool Day7Part1::Hand::operator<(const Hand& rhs) const
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

std::vector<Hand> Day7Part1::parse(const std::string& path)
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

Day7Part1::Hand::Hand(const std::string& hand, int bid) : m_hand{ hand }, m_bid{ bid }
{
	for (char c : hand)
		m_cardCount[c]++;

	m_type = GetHandType();
}

Day7Part1::HandType Day7Part1::Hand::GetHandType() const
{
	if (m_cardCount.size() == 1)
		return HandType::FiveKind;

	if (m_cardCount.size() == 2)
	{
		const auto& [card, count] = *m_cardCount.begin();
		if (count == 4 || count == 1)
			return HandType::FourKind;
		else
			return HandType::FullHouse;
	}

	if (m_cardCount.size() == 3)
	{
		for (const auto& [card, count] : m_cardCount)
		{
			if (count == 3)
				return HandType::ThreeKind;
			if (count == 2)
				return HandType::TwoPair;
		}
	}

	if (m_cardCount.size() == 4)
		return HandType::OnePair;

	return HandType::HighCard;
}
