#include "MagicianCard.h"
#include "Game.h"

MagicianCard::MagicianCard() : CharacterCard("Magician", CharacterType::MAGICIAN)
{
	this->set_discription("Trade all your buildcards with all buildcards of anoher player OR return x amount of card to the building deck and recieve x amount of new cards");
}

void MagicianCard::execute(Game game) {
	game.currentPlayer->write_Client("\u001B[2J");
	game.currentPlayer->write_Client("Make a choice:\r\n\r\n");

	game.currentPlayer->write_Client("1. Trade all of your buildingscards with the buildingscards of another player.\r\n");
	game.currentPlayer->write_Client("2. Trade any amount of buildingscards with the buildingcard deck.\r\n");

	bool valid = false;
	while (!valid) {
		string temp{ game.currentPlayer->readline() };

		try {
			int cardnr = atoi(temp.c_str());
			if (cardnr < 1 || cardnr > 2) {
				throw exception();
			}
			if (cardnr == 1) {
				game.currentPlayer->write_Client("Choose a player to trade with:\r\n\r\n");
				for (size_t i = 0; i < game.players.size(); i++)
				{
					if (game.currentPlayer != game.players[i]) {
						game.currentPlayer->write_Client(to_string(i + 1) + ". " + game.players[i]->get_name() + "\r\n");
					}
				}

				bool valid2 = false;
				while (!valid2) {
					string temp2{ game.currentPlayer->readline() };

					try {
						int cardnr2 = atoi(temp2.c_str()) - 1;
						if (cardnr2 < 0 || cardnr2 > game.players.size() || game.currentPlayer == game.players[cardnr2]) {
							throw exception();
						}
						
						// Kaarten swappen
						Deck temp = game.currentPlayer->buildingCards;
						game.currentPlayer->buildingCards.clear();
						game.currentPlayer->buildingCards = game.players[cardnr2]->buildingCards;

						game.players[cardnr2]->buildingCards.clear();
						game.players[cardnr2]->buildingCards = temp;
						game.players[cardnr2]->write_Client("All your cards have been stolen by the Magician");

						valid2 = true;

					}
					catch (exception e) {
						game.currentPlayer->write_Client("Invalid input. Select a player by number!\r\n");
						valid2 = false;
					}
				}

			} else {
				
				
				int amountOfCards = 0;
				bool valid2 = false;
				while (!valid2) {
					game.currentPlayer->write_Client("\u001B[2J");
					game.currentPlayer->write_Client("Choose cards to trade with the bank:\r\n\r\n");
					for (size_t i = 0; i < game.currentPlayer->buildingCards.size(); i++)
					{
						game.currentPlayer->write_Client(to_string(i + 1) + ". " + game.currentPlayer->buildingCards[i]->print());
					}

					game.currentPlayer->write_Client("\r\nType 'stop' to stop trading.\r\n");


					string temp{ game.currentPlayer->readline() };

					try {
						if (temp == "stop" || game.currentPlayer->buildingCards.size() == 0) {
							valid2 = true;
							game.currentPlayer->write_Client("\u001B[2J");
							game.currentPlayer->write_Client("New cards added to hand:\r\n\r\n");

							for (int i = 0; i < amountOfCards; i++)
							{
								shared_ptr<BasicCard> card = game.DrawSingleCard();
								game.currentPlayer->write_Client(to_string(i + 1) + ". " +card->print());
								game.currentPlayer->buildingCards.add_Card(card);
							}

							game.currentPlayer->write_Client("\r\nPress any key to continue...\r\n");
							game.currentPlayer->readline();
						}
						else {
							int cardnr = atoi(temp.c_str());
							if (cardnr < 1 || cardnr > game.currentPlayer->buildingCards.size()) {
								throw exception();
							}
							amountOfCards++;
							game.currentPlayer->buildingCards.remove_Card(cardnr - 1);
						}
					}
					catch (exception e) {
						game.currentPlayer->write_Client("Invalid input. Select a player by number!\r\n");
						valid2 = false;
					}
				}
			}
			valid = true;
		}
		catch (exception e) {
			game.currentPlayer->write_Client("Invalid input. Select a character by number!\r\n");
			valid = false;
		}
	}
}

MagicianCard::~MagicianCard()
{
}
