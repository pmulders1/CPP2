#include "ThiefCard.h"
#include "Game.h"

ThiefCard::ThiefCard() : CharacterCard("Thief", CharacterType::THIEF)
{
	this->set_discription("Steal gold from another player.");
}

void ThiefCard::execute(Game game) {
	game.currentPlayer->write_Client("\u001B[2J");
	game.currentPlayer->write_Client("Choose a character to steal from:\r\n\r\n");

	int index = 1;
	for (int i = 2; i <= CharacterType::WARLORD; i++)
	{
		if (dynamic_pointer_cast<CharacterCard>(game.allCharacters[static_cast<CharacterType>(i)])->get_alive()) {
			string type = ToString(static_cast<CharacterType>(i));
			game.currentPlayer->write_Client(to_string(index) + ". Steal from " + type + "\r\n");
			index++;
		}
	}
	game.currentPlayer->write_Client("\r\n");

	bool valid = false;
	while (!valid) {
		string temp{ game.currentPlayer->readline() };

		try {
			int cardnr = atoi(temp.c_str());
			if (cardnr < 1 || cardnr > index) {
				throw exception();
			}

			dynamic_pointer_cast<CharacterCard>(game.allCharacters[static_cast<CharacterType>(cardnr + 1)])->set_beenStolen(true);

			valid = true;
		}
		catch (exception e) {
			game.currentPlayer->write_Client("Invalid input. Select a character by number!\r\n");
			valid = false;
		}
	}
}

ThiefCard::~ThiefCard()
{
}
