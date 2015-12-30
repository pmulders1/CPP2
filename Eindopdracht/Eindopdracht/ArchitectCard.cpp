#include "ArchitectCard.h"
#include "Game.h"

ArchitectCard::ArchitectCard() : CharacterCard("Architect", CharacterType::ARCHITECT)
{
	this->set_discription("Draws 2 extra building cards, Can build up to 3 buildings in one turn.");
}

void ArchitectCard::execute(Game game) {

}

ArchitectCard::~ArchitectCard()
{
}
