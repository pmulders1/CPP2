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

	// Set/Get coins
	void set_Coins(int amount) { this->coins += amount;	}
	int get_Coins() { return this->coins; }

	void set_King(bool val) { this->isKing = val; }
	bool get_King() { return this->isKing; }

	// Decks
	Deck buildingCards;
	Deck characterCards;
	Deck playerField;
	
private:
	std::string name;
	int coins = 0;
	bool isKing;
	shared_ptr<Socket> client;
};

#endif /* Player_hpp */
