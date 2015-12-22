#include "ThiefCard.h"



ThiefCard::ThiefCard() : CharacterCard("Thief", CharacterType::THIEF)
{
	this->set_Discription("Steal gold from another player.");
}

void ThiefCard::execute() {

}

ThiefCard::~ThiefCard()
{
}
