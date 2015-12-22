#pragma once
#include "BuildingCard.h"
class Graveyard : public BuildingCard
{
public:
	Graveyard();
	virtual void execute();
	~Graveyard();
};

