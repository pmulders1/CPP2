#include "KingCard.h"



KingCard::KingCard() : CharacterCard("King", CharacterType::KING)
{
	this->set_Discription("Start next round, Recieves gold from monuments.");
}

void KingCard::execute() {

}

KingCard::~KingCard()
{
}