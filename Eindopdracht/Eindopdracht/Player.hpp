//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include "BasicCard.h"
#include <vector>
#include <memory>

using namespace std;
class Player {
public:
	Player() {}
	Player(const string& name) : name {name} {}
	
	std::string get_name() const { return name; }
	void set_name(const string& new_name) { name = new_name; }
	
	int get_points() const { return points; }
	void set_points(const int points) { this->points = points; }

	int get_coins() const { return coins; }
	void set_coins(const int coins) { this->coins = coins; }

	bool get_isKing() const { return isKing; }
	void set_isKing(const bool isKing) { this->isKing = isKing; }

	void set_buildingCard(shared_ptr<BasicCard> card) { buildingCards.push_back(move(card)); }
	void set_characterCard(shared_ptr<BasicCard> card) { characterCards.push_back(move(card)); }

private:
	vector<shared_ptr<BasicCard>> buildingCards;
	vector<shared_ptr<BasicCard>> characterCards;
	string name;
	int points = 0;
	int coins = 0;
	bool isKing = false;
	bool isPlaying = false;
};

#endif /* Player_hpp */
