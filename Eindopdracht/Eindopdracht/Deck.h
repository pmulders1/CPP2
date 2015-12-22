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

	shared_ptr<BasicCard> operator [](int index) { return deck[index]; }

	vector<shared_ptr<BasicCard>> deck;
	~Deck();
};

