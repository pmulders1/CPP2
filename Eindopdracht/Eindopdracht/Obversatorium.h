#pragma once
#include "BuildingCard.h"
class Obversatorium : public BuildingCard
{
public:
	Obversatorium();
	virtual void execute(Game game);
	~Obversatorium();
};

