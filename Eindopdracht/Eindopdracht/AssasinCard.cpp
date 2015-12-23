#include "AssasinCard.h"
#include <iostream>
AssasinCard::AssasinCard() : CharacterCard("Assasin", CharacterType::ASSASSIN)
{
	this->set_discription("Kill any other character.");
}

void AssasinCard::execute() {
	cout << "Hi" << endl;
}

AssasinCard::~AssasinCard()
{
}
