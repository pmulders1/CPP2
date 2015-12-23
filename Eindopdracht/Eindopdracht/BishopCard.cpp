#include "BishopCard.h"



BishopCard::BishopCard() : CharacterCard("Bishop", CharacterType::BISHOP)
{
	this->set_discription("Is protected against the Warlord, Recieves gold from church buildings.");
}

void BishopCard::execute() {

}

BishopCard::~BishopCard()
{
}
