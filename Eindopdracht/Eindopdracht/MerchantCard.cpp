#include "MerchantCard.h"
#include "Game.h"

MerchantCard::MerchantCard() : CharacterCard("Merchant", CharacterType::MERCHANT)
{
	this->set_discription("Recieves one extra gold, Recieves gold from commercial buildings.");
}

void MerchantCard::execute(Game game) {
	game.currentPlayer->write_Client("\u001B[2J");
	game.currentPlayer->write_Client("You got 1 gold for being the merchant. \r\n");
	int amount = 1;
	for (size_t i = 0; i < game.currentPlayer->playerField.size(); i++)
	{
		if (game.currentPlayer->playerField[i]->get_type() == CharacterType::BISHOP) {
			amount++;
		}
	}
	game.currentPlayer->set_Coins(amount);
	game.currentPlayer->write_Client("You got " + to_string(amount) + " gold for every 'Merchant' buildings\r\n");
	game.currentPlayer->write_Client("Your new total gold amount is: " + to_string(game.currentPlayer->get_Coins()) + "\r\n");
	game.currentPlayer->write_Client("Press any key to continue...\r\n");
	game.currentPlayer->readline();
}

MerchantCard::~MerchantCard()
{
}
