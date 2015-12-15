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

class Player {
public:
	Player() {}
	Player(const std::string& name) : name {name} {}
	
	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }
	
	int get_points() const { return points; }
	void set_points(const int points) { this->points = points; }

	int get_coins() const { return coins; }
	void set_coins(const int coins) { this->coins = coins; }

private:
	std::string name;
	int points;
	int coins;
};

#endif /* Player_hpp */
