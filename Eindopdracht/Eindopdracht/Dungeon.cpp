#include "Dungeon.h"
#include "Game.h"

Dungeon::Dungeon() : BuildingCard("Dungeon", 3)
{
	set_special(true);
}

void Dungeon::execute(Game game) {
	std::cout << "CourtOfMiraclesCard" << std::endl;
}

Dungeon::~Dungeon()
{
}
