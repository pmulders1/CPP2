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
#include "Socket.h"
#include "Deck.h"
#include "BuildingCard.h"
#include <map>

using namespace std;
class Player {
public:
	Player() {}
	Player(const std::string& name) : name {name} {}
	
	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }

	// Zelf gemaakte shit
	void set_Client(const shared_ptr<Socket> new_client) { client = new_client; }
	void write_Client(const string str) { *client << str; }
	string readline() { return client->readline(); }
	void Reset();
	void CalculateScore();
	int CalculateBuildingScore();

	// Set/Get coins
	void set_Coins(int amount) { this->coins += amount;	}
	int get_Coins() { return this->coins; }

	void set_King(bool val) { this->isKing = val; }
	bool get_King() { return this->isKing; }

	void set_FirsToEight(bool val) { this->firstToEight = val; }
	bool get_FirsToEight() { return this->firstToEight; }

	void set_Points(int amount) { this->points += amount; }
	int get_Points() { return this->points; }

	friend ostream& operator<<(ostream& strm, const Player& player) {
		strm << player.name << endl;
		strm << player.coins << endl;
		strm << player.points << endl;
		strm << player.isKing << endl;
		strm << player.firstToEight << endl;

		strm << "BuildingCards" << endl << player.buildingCards << "EndBuildingCards" << endl;
		strm << "CharacterCards" << endl << player.characterCards << "EndCharacterCards" << endl;
		strm << "PlayerField" << endl << player.playerField << "EndPlayerField" << endl;

		return strm;
	}

	// Decks
	Deck buildingCards;
	Deck characterCards;
	Deck playerField;
	
private:
	std::string name;
	int coins = 0;
	int points = 0;
	bool isKing = false;
	bool firstToEight = false;
	shared_ptr<Socket> client;
};

#endif /* Player_hpp */
