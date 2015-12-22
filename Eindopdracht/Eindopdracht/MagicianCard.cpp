#include "MagicianCard.h"



MagicianCard::MagicianCard() : CharacterCard("Magician", CharacterType::MAGICIAN)
{
	this->set_Discription("Trade all your buildcards with all buildcards of anoher player OR return x amount of card to the building deck and recieve x amount of new cards");
}

void MagicianCard::execute() {

}

MagicianCard::~MagicianCard()
{
}
