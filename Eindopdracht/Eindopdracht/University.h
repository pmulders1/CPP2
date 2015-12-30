#pragma once
#include "BuildingCard.h"
class University : public BuildingCard
{
public:
	University();
	virtual void execute(Game game);
	~University();
};

