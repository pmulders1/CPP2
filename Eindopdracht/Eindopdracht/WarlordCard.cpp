#include "WarlordCard.h"
#include "Game.h"

WarlordCard::WarlordCard() : CharacterCard("Warlord", CharacterType::WARLORD)
{
	this->set_discription("Destroy any building, Recieves gold from military buildings.");
}

void WarlordCard::execute(Game game){
	game.currentPlayer->write_Client("\u001B[2J");
	game.currentPlayer->write_Client("Choose a player to deconstruct a building from:\r\n\r\n");
	int amount = 0;
	for (size_t i = 0; i < game.players.size(); i++)
	{
		if (game.currentPlayer != game.players[i] && game.players[i]->playerField.size() < 8 && game.players[i]->characterCards[CharacterType::BISHOP] == nullptr) {
			game.currentPlayer->write_Client(to_string(i + 1) + ". " + game.players[i]->get_name() + "\r\n");
			amount++;
		}
	}
	bool valid = false;
	if (amount == 0) {
		valid = true;
	}

	
	
	while (!valid) {
		string temp2{ game.currentPlayer->readline() };

		try {
			int cardnr2 = atoi(temp2.c_str()) - 1;
			if (cardnr2 < 0 || cardnr2 > game.players.size() || game.currentPlayer == game.players[cardnr2] || game.players[cardnr2]->characterCards[CharacterType::BISHOP] != nullptr || game.players[cardnr2]->playerField.size() >= 8) {
				throw exception();
			}

			game.currentPlayer->write_Client("Choose a building to deconstruct:\r\n\r\n");
			// Kaarten swappen
			for (size_t i = 0; i < game.players[cardnr2]->playerField.size(); i++)
			{
				game.currentPlayer->write_Client(to_string(i + 1) + ". " + game.players[cardnr2]->playerField[i]->print());
			}
			bool valid2 = false;
			if (game.players[cardnr2]->playerField.size() == 0) {
				game.currentPlayer->write_Client("No cards on player's field.");
				valid2 = true;
			}

			
			while (!valid2) {
				string temp2{ game.currentPlayer->readline() };

				try {
					int cardnr3 = atoi(temp2.c_str());
					if (cardnr3 < 1 || cardnr3 > game.players[cardnr2]->playerField.size()) {
						throw exception();
					}

					shared_ptr<BuildingCard> card = dynamic_pointer_cast<BuildingCard>(game.players[cardnr2]->playerField[cardnr3 - 1]);
					if (card->get_points() - 1 > game.currentPlayer->get_Coins()) {
						game.currentPlayer->write_Client("Not enough gold to pay for deconstruction.\r\n");
						throw exception();
					}
					
					game.currentPlayer->set_Coins(-(card->get_points() - 1));
					game.players[cardnr2]->playerField.remove_Card(cardnr3 - 1);
					game.buildingsDeck.add_Card(card);
					game.buildingsDeck.shuffle();
					game.players[cardnr2]->write_Client(card->get_name() + " (" + to_string(card->get_points()) + ") has been deconstructed by the 'Warlord'.");

					valid2 = true;

				}
				catch (exception e) {
					game.currentPlayer->write_Client("Invalid input. Select a card by number!\r\n");
					valid2 = false;
				}
			}

			valid = true;

		}
		catch (exception e) {
			game.currentPlayer->write_Client("Invalid input. Select a player by number!\r\n");
			valid = false;
		}
	}

	amount = 0;
	for (size_t i = 0; i < game.currentPlayer->playerField.size(); i++)
	{
		if (game.currentPlayer->playerField[i]->get_type() == CharacterType::WARLORD) {
			amount++;
		}
	}
	game.currentPlayer->set_Coins(amount);
	game.currentPlayer->write_Client("You got " + to_string(amount) + " gold for every 'Warlord' buildings\r\n");
	game.currentPlayer->write_Client("Your new total gold amount is: " + to_string(game.currentPlayer->get_Coins()) + "\r\n");
	game.currentPlayer->write_Client("Press any key to continue...\r\n");
	game.currentPlayer->readline();
}

WarlordCard::~WarlordCard()
{
}
