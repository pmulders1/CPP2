#pragma once
#include "BuildingCard.h"
class Dungeon : public BuildingCard
{
public:
	Dungeon();
	virtual void execute(Game game);
	~Dungeon();
};

