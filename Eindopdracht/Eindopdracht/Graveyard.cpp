#include "Graveyard.h"
#include "Game.h"

Graveyard::Graveyard() : BuildingCard("Graveyard", 5)
{
	set_special(true);
}

void Graveyard::execute(Game game) {
	game.observers["Graveyard"].second->write_Client("The warlord just destroyed the following card: \r\n");
	game.observers["Graveyard"].second->write_Client(game.tempCard->print());
	game.observers["Graveyard"].second->write_Client("Would you like to obtain the card for 1 gold?\r\n");
	game.observers["Graveyard"].second->write_Client("Type 'yes' or 'no'\r\n");
	bool valid = false;
	while (!valid) {
		string temp{ game.observers["Graveyard"].second->readline() };

		if (temp == "yes") {
			if (game.observers["Graveyard"].second->get_Coins() >= 1) {
				game.observers["Graveyard"].second->buildingCards.add_Card(game.tempCard);
				game.buildingsDeck.remove_Card(game.tempCard);
				game.observers["Graveyard"].second->set_Coins(-1);
				valid = true;
			}
			else {
				game.observers["Graveyard"].second->write_Client("You don't have enough coins to take over this card!\r\n");
				valid = false;
			}
		} else if (temp == "no") {
			valid = true;
		} else {
			game.observers["Graveyard"].second->write_Client("Invalid input. Type 'yes' or 'no'!\r\n");
			valid = false;
		}
	}
	delete game.tempCard.get();
}

Graveyard::~Graveyard()
{
}
