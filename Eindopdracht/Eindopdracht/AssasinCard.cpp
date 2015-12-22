#include "AssasinCard.h"

AssasinCard::AssasinCard() : CharacterCard("Assasin", CharacterType::ASSASSIN)
{
	this->set_Discription("Kill any other character.");
}

void AssasinCard::execute() {

}

AssasinCard::~AssasinCard()
{
}
