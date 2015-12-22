#include "Dungeon.h"

Dungeon::Dungeon() : BuildingCard("Dungeon", 3)
{
}

void Dungeon::execute() {
	std::cout << "CourtOfMiraclesCard" << std::endl;
}

Dungeon::~Dungeon()
{
}
