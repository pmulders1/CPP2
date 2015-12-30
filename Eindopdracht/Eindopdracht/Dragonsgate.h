#pragma once
#include "BuildingCard.h"
class Dragonsgate : public BuildingCard
{
public:
	Dragonsgate();
	virtual void execute(Game game);
	~Dragonsgate();
};

