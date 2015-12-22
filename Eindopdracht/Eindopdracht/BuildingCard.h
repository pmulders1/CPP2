#pragma once
#include "BasicCard.h"

class BuildingCard : public BasicCard
{
public:
	BuildingCard(string name, int points, CharacterType type = CharacterType::NONE);
	virtual void execute();
	~BuildingCard();

	void set_points(int amount) { this->points = amount; }
	int get_points() { return this->points; }

private:
	int points;
};

