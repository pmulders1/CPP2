#include "KingCard.h"
#include "Game.h"

KingCard::KingCard() : CharacterCard("King", CharacterType::KING)
{
	this->set_discription("Start next round, Recieves gold from monuments.");
}

void KingCard::execute(Game game) {
	int amount = 0;
	for (size_t i = 0; i < game.currentPlayer->playerField.size(); i++)
	{
		if (game.currentPlayer->playerField[i]->get_type() == CharacterType::KING) {
			amount++;
		}
	}
	game.currentPlayer->set_Coins(amount);
	game.currentPlayer->write_Client("\u001B[2J");
	game.currentPlayer->write_Client("You got " + to_string(amount) + " gold for every 'King' buildings\r\n");
	game.currentPlayer->write_Client("Your new total gold amount is: " + to_string(game.currentPlayer->get_Coins()) + "\r\n");
	game.currentPlayer->write_Client("Press any key to continue...\r\n");
	game.currentPlayer->readline();
}

KingCard::~KingCard()
{
}
