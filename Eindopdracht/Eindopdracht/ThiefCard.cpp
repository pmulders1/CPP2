#include "ThiefCard.h"



ThiefCard::ThiefCard() : CharacterCard("Thief", CharacterType::THIEF)
{
	this->set_discription("Steal gold from another player.");
}

void ThiefCard::execute() {

}

ThiefCard::~ThiefCard()
{
}
