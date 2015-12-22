#include "Game.h"



Game::Game()
{
	srand(time(0));
	charactersDeck.add_Card(shared_ptr<AssasinCard>{new AssasinCard()});
	charactersDeck.add_Card(shared_ptr<ThiefCard>{new ThiefCard()});
	charactersDeck.add_Card(shared_ptr<MagicianCard>{new MagicianCard()});
	charactersDeck.add_Card(shared_ptr<KingCard>{new KingCard()});
	charactersDeck.add_Card(shared_ptr<BishopCard>{new BishopCard()});
	charactersDeck.add_Card(shared_ptr<MerchantCard>{new MerchantCard()});
	charactersDeck.add_Card(shared_ptr<ArchitectCard>{new ArchitectCard()});
	charactersDeck.add_Card(shared_ptr<WarlordCard>{new WarlordCard()});
	
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Estate", 3, CharacterType::KING)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Castle", 4, CharacterType::KING)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Palace", 5, CharacterType::KING)});

	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Tavern", 1, CharacterType::MERCHANT)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Stores", 2, CharacterType::MERCHANT)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Market", 2, CharacterType::MERCHANT)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Warehouse", 3, CharacterType::MERCHANT)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Port", 4, CharacterType::MERCHANT)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Town Hall", 5, CharacterType::MERCHANT)});

	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Temple", 1, CharacterType::BISHOP)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Church", 2, CharacterType::BISHOP)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Monastery", 3, CharacterType::BISHOP)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Cathedral", 1, CharacterType::BISHOP)});

	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Watchtower", 1, CharacterType::WARLORD)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Prison", 2, CharacterType::WARLORD)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Tournament Field", 3, CharacterType::WARLORD)});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new BuildingCard("Stronghold", 5, CharacterType::WARLORD)});

	buildingsDeck.add_Card(shared_ptr<BasicCard>{new CourtOfMiraclesCard()});

	/*

	shared_ptr<BasicCard> courtofmiracles(new SpecialCard("Court of Miracles", 2));
	shared_ptr<BasicCard> dungeon(new SpecialCard("Dungeon", 3));
	shared_ptr<BasicCard> graveyard(new SpecialCard("Graveyard", 5));
	shared_ptr<BasicCard> labatorium(new SpecialCard("Labatorium", 5));
	shared_ptr<BasicCard> workshop(new SpecialCard("workshop", 5));
	shared_ptr<BasicCard> obversatorium(new SpecialCard("Obversatorium", 5));
	shared_ptr<BasicCard> library(new SpecialCard("library", 6));
	shared_ptr<BasicCard> magiciansschool(new SpecialCard("Magicians school", 6));
	shared_ptr<BasicCard> dragonsgate(new SpecialCard("Dragonsgate", 6));
	shared_ptr<BasicCard> university(new SpecialCard("University", 6));
	buildingsDeck.push_back(courtofmiracles);
	buildingsDeck.push_back(dungeon);
	buildingsDeck.push_back(graveyard);
	buildingsDeck.push_back(labatorium);
	buildingsDeck.push_back(workshop);
	buildingsDeck.push_back(obversatorium);
	buildingsDeck.push_back(library);
	buildingsDeck.push_back(magiciansschool);
	buildingsDeck.push_back(dragonsgate);
	buildingsDeck.push_back(university);*/
}

void Game::HandleCommand(shared_ptr<Player> player, string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);
	if (command == "join") {
		this->JoinPlayer(player);
	}
	else if (command == "start-game") {
		this->StartGame(player);
		//if (players.size() == 2) {
		//	this->CharacterSelection2P(player, client);
		//}
		//if (players.size() == 3) {
		//	this->CharacterSelection3P(player, client);
		//}

		//for (int i = 1; i <= CharacterType::WARLORD; i++)
		//{
		//	pair<int, int> indexes = this->FindPlayer((CharacterType)i);
		//	// Check of next character is alive otherwise skip turn.
		//	if ((indexes.first != -1 && indexes.second != -1) && players[indexes.first].first->characterCards[indexes.second].first) {
		//		this->ontabledeck.push_back(players[indexes.first].first->characterCards[indexes.second]);
		//		this->currentPlayer = indexes.first;
		//		this->PlayTurn((CharacterType)i);
		//	}
		//}

	}
	else if (command == "help") {
		this->Help(player);
	}
}

void Game::JoinPlayer(shared_ptr<Player> player) {
	this->players.push_back(player);

	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->write_Client(player->get_name() + " has joined the game\r\n");
	}
}

void Game::StartGame(shared_ptr<Player> player) {
	if (players.size() > 1 && !this->playing) {
		this->playing = true;

		// Shuffle decks
		buildingsDeck.shuffle();
		charactersDeck.shuffle();

		for (size_t i = 0; i < players.size(); i++)
		{
			players[i]->write_Client("Game has started. Good luck!\r\n");
			players[i]->set_Coins(2);

			for (int j = 0; j < 4; j++) {
				players[i]->buildingCards.add_Card(move(buildingsDeck[0]));
				buildingsDeck.remove_Card(0);
			}
		}
		players[0]->set_King(true);
		players[0]->write_Client("You are the King. You may start the game.\r\n");
	}
	else if (players.size() == 0) {
		player->write_Client("You must join first before you can start a game.\r\n");
	}
	else if (playing) {
		player->write_Client("Game already started.\r\n");
	}
	else {
		player->write_Client("Not enough players to start a game.\r\n");
	}
}

void Game::Help(shared_ptr<Player> player) {
	player->write_Client("Game turn:\r\n");
	player->write_Client("Income: Take 2 gold pieces or take 2 build cards and put 1 back.\r\n");
	player->write_Client("Building: Place one build card on your playfield and pay the amount of gold required to the bank.\r\n");
	player->write_Client("Character Specialty: You can activate your characters special ability at any time.\r\n\r\n");

	player->write_Client("Characters:\r\n");
	player->write_Client("1. Assasin: Kill any other character.\r\n");
	player->write_Client("2. Thief: Steal gold from another player.\r\n");
	player->write_Client("3. Magician: Trade all your buildcards with another all buildcards of anoher player.\r\n");
	player->write_Client("4. King: Start next round, Recieves gold from monuments.\r\n");
	player->write_Client("5. Pedo: Is protected against the Warlord, Recieves gold from church buildings.\r\n");
	player->write_Client("6. Merchant: Recieves one extra gold, Recieves gold from commercial buildings.\r\n");
	player->write_Client("7. Architect: Draws 2 extra building cards, Can build up to 3 buildings in one turn.\r\n");
	player->write_Client("8. Warlord: Destroy any building, Recieves gold from military buildings.\r\n");
}

Game::~Game()
{
}
