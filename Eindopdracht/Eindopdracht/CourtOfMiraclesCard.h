#pragma once
#include "BuildingCard.h"
class CourtOfMiraclesCard : public BuildingCard
{
public:
	CourtOfMiraclesCard();
	virtual void execute(Game game);
	~CourtOfMiraclesCard();
};

