#include "WarlordCard.h"



WarlordCard::WarlordCard() : CharacterCard("Warlord", CharacterType::WARLORD)
{
	this->set_discription("Destroy any building, Recieves gold from military buildings.");
}

void WarlordCard::execute(){

}

WarlordCard::~WarlordCard()
{
}
