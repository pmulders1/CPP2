//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.hpp"
using namespace std;

void Player::Reset() {
	this->buildingCards.clear();
	this->characterCards.clear();
	this->playerField.clear();
	this->coins = 0;
	this->points = 0;
	this->set_King(false);
	this->set_FirsToEight(false);
}
void Player::CalculateScore() {
	map<CharacterType, shared_ptr<BuildingCard>> buildings;
	int buildingTotal = 0;
	for (size_t j = 0; j < this->playerField.size(); j++)
	{
		shared_ptr<BuildingCard> card = dynamic_pointer_cast<BuildingCard>(this->playerField[j]);
		buildingTotal += card->get_points();
		buildings[card->get_type()] = card;
	}
	this->write_Client(to_string(buildingTotal) + " points for the buildings you've build.\r\n");
	this->set_Points(buildingTotal);

	if (buildings.size() == 5) {
		this->write_Client("3 points for building all buildingtypes.\r\n");
		this->set_Points(3);
	}

	if (this->get_FirsToEight()) {
		this->write_Client("4 points for being the first to build eight buildings.\r\n");
		this->set_Points(4);
	}

	if (!this->get_FirsToEight() && this->playerField.size() >= 8) {
		this->write_Client("2 points for building more than eight buildings.\r\n");
		this->set_Points(2);
	}
}
int Player::CalculateBuildingScore() {
	int buildingTotal = 0;
	for (size_t j = 0; j < this->playerField.size(); j++)
	{
		shared_ptr<BuildingCard> card = dynamic_pointer_cast<BuildingCard>(this->playerField[j]);
		buildingTotal += card->get_points();
	}
	return buildingTotal;
}
