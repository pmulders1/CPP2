#include "CourtOfMiraclesCard.h"
#include "Game.h"
#include <iostream>

CourtOfMiraclesCard::CourtOfMiraclesCard() : BuildingCard("Court of Miracles", 2)
{
	set_special(true);
}

void CourtOfMiraclesCard::execute(Game game) {
	std::cout << "CourtOfMiraclesCard" << std::endl;
}


CourtOfMiraclesCard::~CourtOfMiraclesCard()
{
}
