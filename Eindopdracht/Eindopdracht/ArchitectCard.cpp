#include "ArchitectCard.h"



ArchitectCard::ArchitectCard() : CharacterCard("Architect", CharacterType::ARCHITECT)
{
	this->set_Discription("Draws 2 extra building cards, Can build up to 3 buildings in one turn.");
}

void ArchitectCard::execute() {

}

ArchitectCard::~ArchitectCard()
{
}
