#pragma once
#include <vector>
#include "BasicCard.h"
#include <memory>
#include <algorithm>
class Deck
{
public:
	Deck();
	void shuffle() { random_shuffle(deck.begin(), deck.end()); }
	void add_Card(shared_ptr<BasicCard> card) { this->deck.push_back(card); }
	void remove_Card(int index) { this->deck.erase(this->deck.begin() + index); }
	void remove_Card(shared_ptr<BasicCard> card) { 
		this->deck.erase(find(this->deck.begin(), this->deck.end(), card));
	}

	size_t size() { return this->deck.size(); }
	void clear() { deck.clear(); }

	shared_ptr<BasicCard> operator [](int index) { return deck[index]; }
	shared_ptr<BasicCard> operator [](CharacterType type) { 
		for (size_t i = 0; i < deck.size(); i++)
		{
			if (deck[i]->get_type() == type) {
				return deck[i];
			}
		}
		return nullptr;
	}

	vector<shared_ptr<BasicCard>> deck;
	~Deck();
};

