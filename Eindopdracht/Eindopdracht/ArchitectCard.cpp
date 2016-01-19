#include "ArchitectCard.h"
#include "Game.h"

ArchitectCard::ArchitectCard() : CharacterCard("Architect", CharacterType::ARCHITECT)
{
	this->set_discription("Draws 2 extra building cards, Can build up to 3 buildings in one turn.");
}

void ArchitectCard::execute(Game game) {
	game.currentPlayer->write_Client("\u001B[2J");
	game.currentPlayer->write_Client("You will recieve the following 2 extra building cards:\r\n\r\n");
	
	shared_ptr<BasicCard> card;
	for (int i = 0; i < 2; i++) {
		if (game.buildingsDeck.size() == 0) {
			game.currentPlayer->write_Client("The deck with buildingcards is empty! \r\n");
			break;
		}
		card = game.DrawSingleCard();
		game.currentPlayer->write_Client(card->print());
		game.currentPlayer->buildingCards.add_Card(card);
	}

	game.currentPlayer->write_Client("Press any key to continue...\r\n");
	game.currentPlayer->readline();

	for (int i = 0; i < 2; i++) {
		game.ConstructBuildings();
	}
}

ArchitectCard::~ArchitectCard()
{
}
