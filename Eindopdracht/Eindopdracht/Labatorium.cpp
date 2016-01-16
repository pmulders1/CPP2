#include "Labatorium.h"
#include "Game.h"

Labatorium::Labatorium() : BuildingCard("Labatorium", 5)
{
	set_special(true);
}

void Labatorium::execute(Game game) {

}

Labatorium::~Labatorium()
{
}
