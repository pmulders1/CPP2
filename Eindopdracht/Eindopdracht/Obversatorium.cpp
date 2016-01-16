#include "Obversatorium.h"
#include "Game.h"

Obversatorium::Obversatorium() : BuildingCard("Obversatorium", 5)
{
	set_special(true);
}

void Obversatorium::execute(Game game) {

}

Obversatorium::~Obversatorium()
{
}
