#include "University.h"
#include "Game.h"

University::University() : BuildingCard("University", 6)
{
	set_special(true);
}

void University::execute(Game game) {

}

University::~University()
{
}
