#include "MagiciansSchool.h"
#include "Game.h"

MagiciansSchool::MagiciansSchool() : BuildingCard("Magicians School", 6)
{
	set_special(true);
}

void MagiciansSchool::execute(Game game) {

}

MagiciansSchool::~MagiciansSchool()
{
}
