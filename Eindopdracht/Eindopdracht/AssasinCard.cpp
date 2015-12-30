#include "AssasinCard.h"
#include "Game.h"
#include <iostream>
AssasinCard::AssasinCard() : CharacterCard("Assasin", CharacterType::ASSASSIN)
{
	this->set_discription("Kill any other character.");
}

void AssasinCard::execute(Game game) {
	game.currentPlayer->write_Client("\u001B[2J");
	game.currentPlayer->write_Client("Choose a character to chop his head off:\r\n\r\n");

	for (int i = 2; i <= CharacterType::WARLORD; i++)
	{
		string type = ToString(static_cast<CharacterType>(i));
		game.currentPlayer->write_Client(to_string(i - 1) + ". Kill the " + type + "\r\n");
	}
	game.currentPlayer->write_Client("\r\n");

	bool valid = false;
	while (!valid) {
		string temp{ game.currentPlayer->readline() };

		try {
			int cardnr = atoi(temp.c_str());
			if (cardnr < 1 || cardnr > 7) {
				throw exception();
			}

			dynamic_pointer_cast<CharacterCard>(game.allCharacters[static_cast<CharacterType>(cardnr + 1)])->set_alive(false);

			valid = true;
		}
		catch (exception e) {
			game.currentPlayer->write_Client("Invalid input. Select a character by number!\r\n");
			valid = false;
		}
	}
}

AssasinCard::~AssasinCard()
{
}
