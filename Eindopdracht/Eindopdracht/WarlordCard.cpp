#include "WarlordCard.h"
#include "Game.h"

WarlordCard::WarlordCard() : CharacterCard("Warlord", CharacterType::WARLORD)
{
	this->set_discription("Destroy any building, Recieves gold from military buildings.");
}

void WarlordCard::execute(Game game){

}

WarlordCard::~WarlordCard()
{
}
