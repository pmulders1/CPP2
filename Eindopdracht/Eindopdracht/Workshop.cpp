#include "Workshop.h"
#include "Game.h"

Workshop::Workshop() : BuildingCard("Workshop", 5)
{
	set_special(true);
}

void Workshop::execute(Game game) {

}

Workshop::~Workshop()
{
}
