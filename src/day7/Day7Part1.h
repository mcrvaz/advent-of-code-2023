#pragma once

#include <string>
#include <unordered_map>

class Day7Part1
{
public:
	enum class HandType
	{
		// Five of a kind, where all five cards have the same label : AAAAA
		FiveKind = 6,
		// Four of a kind, where four cards have the same label and one card has a different label: AA8AA
		FourKind = 5,
		// Full house, where three cards have the same label, and the remaining two cards share a different label : 23332
		FullHouse = 4,
		// Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
		ThreeKind = 3,
		// Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
		TwoPair = 2,
		// One pair, where two cards share one label, and the other three cards have a different label from the pair and each other : A23A4
		OnePair = 1,
		// High card, where all cards' labels are distinct: 23456
		HighCard = 0
	};

	class Hand {
	public:
		static inline const std::vector<char> cards
		{
			'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'
		};
		static const int HAND_SIZE = 5;

		Hand(const std::string& hand, int bid);

		HandType GetHandType() const;
		int Bid() const { return m_bid; };

		bool operator<(const Hand& rhs) const;
	private:
		std::string m_hand;
		int m_bid;
		HandType m_type;
		std::unordered_map<char, int> m_cardCount{};
	};

	int64_t solve();
private:
	std::vector<Hand> parse(const std::string& path);
};
