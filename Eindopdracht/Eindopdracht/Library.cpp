#include "Library.h"
#include "Game.h"

Library::Library() : BuildingCard("Library", 6)
{
	set_special(true);
}

void Library::execute(Game game) {

}

Library::~Library()
{
}
