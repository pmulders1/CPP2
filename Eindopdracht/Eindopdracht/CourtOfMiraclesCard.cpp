#include "CourtOfMiraclesCard.h"
#include <iostream>

CourtOfMiraclesCard::CourtOfMiraclesCard() : BuildingCard("Court of Miracles", 2)
{
}

void CourtOfMiraclesCard::execute() {
	std::cout << "CourtOfMiraclesCard" << std::endl;
}


CourtOfMiraclesCard::~CourtOfMiraclesCard()
{
}
