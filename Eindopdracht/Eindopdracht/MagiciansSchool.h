#pragma once
#include "BuildingCard.h"
class MagiciansSchool : public BuildingCard
{
public:
	MagiciansSchool();
	virtual void execute(Game game);
	~MagiciansSchool();
};

