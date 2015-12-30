#include "BishopCard.h"
#include "Game.h"

BishopCard::BishopCard() : CharacterCard("Bishop", CharacterType::BISHOP)
{
	this->set_discription("Is protected against the Warlord, Recieves gold from church buildings.");
}

void BishopCard::execute(Game game) {
	int amount = 0;
	for (size_t i = 0; i < game.currentPlayer->playerField.size(); i++)
	{
		if (game.currentPlayer->playerField[i]->get_type() == CharacterType::BISHOP) {
			amount++;
		}
	}
	game.currentPlayer->set_Coins(amount);
	game.currentPlayer->write_Client("\u001B[2J");
	game.currentPlayer->write_Client("You got " + to_string(amount) + " gold for every 'Bishop' buildings\r\n");
	game.currentPlayer->write_Client("Your new total gold amount is: " + to_string(game.currentPlayer->get_Coins()) + "\r\n");
	game.currentPlayer->write_Client("Press any key to continue...\r\n");
	game.currentPlayer->readline();
}

BishopCard::~BishopCard()
{
}
