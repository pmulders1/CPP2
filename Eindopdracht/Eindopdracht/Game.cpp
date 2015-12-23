#include "Game.h"

Game::Game()
{
	srand(time(0));
	allCharacters.insert(make_pair(CharacterType::ASSASSIN, shared_ptr<AssasinCard>{new AssasinCard()}));
	allCharacters.insert(make_pair(CharacterType::THIEF, shared_ptr<ThiefCard>{new ThiefCard()}));
	allCharacters.insert(make_pair(CharacterType::MAGICIAN, shared_ptr<MagicianCard>{new MagicianCard()}));
	allCharacters.insert(make_pair(CharacterType::KING, shared_ptr<KingCard>{new KingCard()}));
	allCharacters.insert(make_pair(CharacterType::BISHOP, shared_ptr<BishopCard>{new BishopCard()}));
	allCharacters.insert(make_pair(CharacterType::MERCHANT, shared_ptr<MerchantCard>{new MerchantCard()}));
	allCharacters.insert(make_pair(CharacterType::ARCHITECT, shared_ptr<ArchitectCard>{new ArchitectCard()}));
	allCharacters.insert(make_pair(CharacterType::WARLORD, shared_ptr<WarlordCard>{new WarlordCard()}));
	
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
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Dungeon()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Graveyard()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Labatorium()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Workshop()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Obversatorium()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Library()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new MagiciansSchool()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Dragonsgate()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new University()});

	for (int i = 1; i <= CharacterType::WARLORD; i++)
	{
		charactersDeck.add_Card(allCharacters[static_cast<CharacterType>(i)]);
	}
}

void Game::HandleCommand(shared_ptr<Player> player, string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);
	if (command == "join") {
		this->JoinPlayer(player);
	}
	else if (command == "start-game") {
		this->StartGame(player);
		if (players.size() == 2) {
			this->CharacterSelection2P(player);
		}
		if (players.size() == 3) {
			this->CharacterSelection3P(player);
		}

		for (int i = 1; i <= CharacterType::WARLORD; i++)
		{
			CharacterType type = static_cast<CharacterType>(i);
			if (allCharacters[type]->get_owner() == nullptr) {
				continue;
			}

			currentPlayer = allCharacters[type]->get_owner();
			if (!allCharacters[type]->get_alive()) {
				currentPlayer->write_Client(allCharacters[type]->get_name() + " has been killed this round so we are skipping its turn.");
			} else {
				currentPlayer->characterCards[type]->set_visible(true);
				onTableDeck.add_Card(currentPlayer->characterCards[type]);

				this->PlayTurn(ToString(type));
			}
		}
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

void Game::CharacterSelection2P(shared_ptr<Player> player) {
	this->Reset();
	players[0]->write_Client("The following card will be placed face down on the table: \r\n");
	players[0]->write_Client(charactersDeck[0]->print() + "\r\n");

	charactersDeck[0]->set_visible(false);
	onTableDeck.add_Card(charactersDeck[0]);
	charactersDeck.remove_Card(0);

	bool first = true;

	for (size_t i = 0; i < players.size() * 2; i++) {
		if (i >= players.size()) {
			currentPlayer = players[i - players.size()];
		} else {
			currentPlayer = players[i];
		}

		bool valid = false;
		while (!valid) {
			currentPlayer->write_Client("Choose one of the following Character cards:\r\n\r\n");
			for (size_t j = 0; j < charactersDeck.size(); j++)
			{
				currentPlayer->write_Client(to_string(j) + ". " + charactersDeck[j]->print());
			}
			currentPlayer->write_Client("Select a card by number: \r\n");
			string temp{ currentPlayer->readline() };

			try {
				int cardnr = atoi(temp.c_str());
				if (cardnr < 0 || cardnr > charactersDeck.size() - 1) {
					throw exception();
				}
				charactersDeck[cardnr]->set_visible(false);
				currentPlayer->characterCards.add_Card(charactersDeck[cardnr]);
				allCharacters[charactersDeck[cardnr]->get_type()]->set_owner(currentPlayer);
				charactersDeck.remove_Card(cardnr);
				valid = true;
			}
			catch (exception e) {
				currentPlayer->write_Client("Invalid input. Select a card by number!\r\n");
				valid = false;
			}
		}
		if (!first) {
			bool valid = false;
			while (!valid) {
				currentPlayer->write_Client("\r\nChoose one of the following Character cards to lay down:\r\n\r\n");
				for (size_t j = 0; j < charactersDeck.size(); j++)
				{
					currentPlayer->write_Client(to_string(j) + ". " + charactersDeck[j]->print());
				}
				currentPlayer->write_Client("Select a card by number: \r\n");
				string temp{ currentPlayer->readline() };

				try {
					int cardnr = atoi(temp.c_str());
					if (cardnr < 0 || cardnr > charactersDeck.size() - 1) {
						throw exception();
					}
					charactersDeck[cardnr]->set_visible(false);
					onTableDeck.add_Card(charactersDeck[cardnr]);
					charactersDeck.remove_Card(cardnr);

					valid = true;
				}
				catch (exception e) {
					currentPlayer->write_Client("Invalid input. Select a card by number!\r\n");
					valid = false;
				}
			}
		}
		first = false;
	}
}

void Game::CharacterSelection3P(shared_ptr<Player> player) {
	this->Reset();
	players[0]->write_Client("The following card will be placed face down on the table: \r\n");
	players[0]->write_Client(charactersDeck[0]->print() + "\r\n");

	charactersDeck[0]->set_visible(false);
	onTableDeck.add_Card(charactersDeck[0]);
	charactersDeck.remove_Card(0);

	// iedere speler kan 2 kaarten pakken.
	for (size_t i = 0; i < players.size() * 2; i++) {
		if (i >= players.size()) {
			currentPlayer = players[i - players.size()];
		} else {
			currentPlayer = players[i];
		}

		bool valid = false;
		while (!valid) {
			currentPlayer->write_Client("Choose one of the following Character cards:\r\n\r\n");
			for (size_t j = 0; j < charactersDeck.size(); j++)
			{
				currentPlayer->write_Client(to_string(j) + ". " + charactersDeck[j]->print());
			}
			currentPlayer->write_Client("Select a card by number: \r\n");
			string temp{ currentPlayer->readline() };

			try {
				int cardnr = atoi(temp.c_str());
				if (cardnr < 0 || cardnr > charactersDeck.size() - 1) {
					throw exception();
				}
				charactersDeck[cardnr]->set_visible(false);
				currentPlayer->characterCards.add_Card(charactersDeck[cardnr]);
				allCharacters[charactersDeck[cardnr]->get_type()]->set_owner(currentPlayer);
				charactersDeck.remove_Card(cardnr);
				valid = true;
			}
			catch (exception e) {
				currentPlayer->write_Client("Invalid input. Select a card by number!\r\n");
				valid = false;
			}
		}
	}
	charactersDeck[0]->set_visible(false);
	onTableDeck.add_Card(charactersDeck[0]);
	charactersDeck.remove_Card(0);
}

void Game::PlayTurn(string type) {
	bool firstpart = true;
	bool secondpart = true;
	bool specialpart = true;
	bool skipturn = false;

	while ((firstpart && secondpart && specialpart) || !skipturn) {

		currentPlayer->write_Client("\u001B[2J");
		currentPlayer->write_Client("You are playing as: " + type + "\r\n");
		currentPlayer->write_Client("Gold: " + to_string(currentPlayer->get_Coins()) + "\r\n\r\n");
		currentPlayer->write_Client("Buildings: \r\n");

		for (size_t i = 0; i < currentPlayer->playerField.size(); i++)
		{
			currentPlayer->write_Client(to_string(i + 1) + ". " + currentPlayer->playerField[i]->print());
		}
		if (currentPlayer->playerField.size() == 0) {
			currentPlayer->write_Client("No buildings build.");
		}

		currentPlayer->write_Client("\r\nCards in hand: \r\n");

		for (size_t i = 0; i < currentPlayer->buildingCards.size(); i++)
		{
			currentPlayer->write_Client(to_string(i + 1) + ". " + currentPlayer->buildingCards[i]->print());
		}
		if (currentPlayer->buildingCards.size() == 0) {
			currentPlayer->write_Client("No cards in hand.");
		}

		string firstpartstr = firstpart ? "Available" : "Unavailable";
		string secondpartstr = secondpart ? "Available" : "Unavailable";
		string specialpartstr = specialpart ? "Available" : "Unavailable";

		currentPlayer->write_Client("\r\nMake a choice: \r\n");
		currentPlayer->write_Client("1. Show players and playfield. \r\n");
		currentPlayer->write_Client("2. Take 2 gold coins. (" + firstpartstr + ") \r\n");
		currentPlayer->write_Client("3. Take 2 cards from deck. (" + firstpartstr + ") \r\n");
		currentPlayer->write_Client("4. Construct buildings. (" + secondpartstr + ") \r\n");
		currentPlayer->write_Client("5. Use special ability of " + type + ". (" + specialpartstr + ") \r\n");
		currentPlayer->write_Client("6. Skip turn. \r\n");

		bool valid = false;
		while (!valid) {
			string temp{ currentPlayer->readline() };

			try {
				int choice = atoi(temp.c_str());
				if (choice < 1 || choice > 6) {
					throw exception();
				}

				switch (choice) {
				case 1:
					ShowBoard();
					break;
				case 2:
					if(firstpart){
						currentPlayer->set_Coins(2);
						firstpart = false;
					} else {
						currentPlayer->write_Client("Selected function is no longer available");
					}
					break;
				case 3:
					if (firstpart) {
						DrawCards();
						firstpart = false;
					} else {
						currentPlayer->write_Client("Selected function is no longer available");
					}
					break;
				case 4:
					if (secondpart) {
						secondpart = ConstructBuildings();
					} else {
						currentPlayer->write_Client("Selected function is no longer available");
					}
					break;
				case 5:
					if (specialpart) {
						currentPlayer->characterCards[ToEnum(type)]->execute();
						specialpart = false;
					} else {
						currentPlayer->write_Client("Selected function is no longer available");
					}
					break;
				case 6:
					skipturn = true;
					break;
				default:
					break;
				}

				valid = true;
			}
			catch (exception e) {
				currentPlayer->write_Client("Invalid input. Select a option by number!\r\n");
				valid = false;
			}
		}
	}
}

void Game::ShowBoard() {
	currentPlayer->write_Client("\u001B[2J");
	currentPlayer->write_Client("Gameboard: \r\n\r\n");

	for (size_t i = 0; i < players.size(); i++) {
		// Naam printen van speler
		currentPlayer->write_Client(players[i]->get_name() + " (" + to_string(players[i]->get_Coins()) + " gold): \r\n");

		currentPlayer->write_Client("Plays as: \r\n\r\n");
		for (size_t x = 0; x < players[i]->characterCards.size(); x++) {
			// Als de speler zijn character nog gesloten zijn omdat hij nog niet aan de beurt is 
			// geweest dan wordt er not available geprint.
			

			if (players[i]->characterCards[x]->get_visible())
			{
				currentPlayer->write_Client(to_string(x + 1) + ": " + players[i]->characterCards[x]->print());
			}
			else {
				currentPlayer->write_Client(to_string(x + 1) + ": Still unknown.\r\n");
			}
		}
		currentPlayer->write_Client("\r\nBuildings played: \r\n\r\n");

		if (players[i]->playerField.size() == 0) {
			currentPlayer->write_Client("No buildings on the field. \r\n");
		}
		for (size_t j = 0; j < players[i]->playerField.size(); j++)
		{
			currentPlayer->write_Client(" " + players[i]->playerField[j]->print() + "\r\n");
		}
		currentPlayer->write_Client("\r\n");
	}
	currentPlayer->readline();
}

void Game::DrawCards() {
	currentPlayer->write_Client("\u001B[2J");
	currentPlayer->write_Client("Cards drawn:\r\n\r\n");

	for (size_t i = 0; i < 2; i++) {
		currentPlayer->write_Client(to_string(i) + ": " + buildingsDeck[i]->print());
	}

	currentPlayer->write_Client("Choose a card to keep: ");

	// Check voor geldige invoer
	bool valid = false;
	while (!valid) {
		string temp{ currentPlayer->readline() };

		try {
			int choice = atoi(temp.c_str());
			if (choice < 0 || choice > 1) {
				throw exception();
			}
			currentPlayer->buildingCards.add_Card(buildingsDeck[choice]);
			buildingsDeck.remove_Card(choice);
			buildingsDeck.shuffle();

			valid = true;
		}
		catch (exception e) {
			currentPlayer->write_Client("Invalid input. Select a option by number!\r\n");
			valid = false;
		}
	}
}

bool Game::ConstructBuildings() {
	currentPlayer->write_Client("\u001B[2J");
	currentPlayer->write_Client("Cards in hand: \r\n\r\n");

	for (size_t i = 0; i < currentPlayer->buildingCards.size(); i++)
	{
		currentPlayer->write_Client(to_string(i + 1) + ". " + currentPlayer->buildingCards[i]->print());
	}
	if (currentPlayer->buildingCards.size() == 0) {
		currentPlayer->write_Client("No cards in hand. You can't construct any buildings.\r\n");
		currentPlayer->write_Client("Returning to main menu.");
		currentPlayer->readline();
		return true;
	}

	currentPlayer->write_Client("\r\nChoose a card to build: \r\n");

	// Check voor geldige invoer
	bool valid = false;
	while (!valid) {
		string temp{ currentPlayer->readline() };

		try {
			int choice = atoi(temp.c_str());
			if (choice < 0 || choice > currentPlayer->buildingCards.size()) {
				throw exception();
			}
			int cardCost = dynamic_pointer_cast<BuildingCard>(currentPlayer->buildingCards[choice - 1])->get_points();
			if (cardCost > currentPlayer->get_Coins()) {
				valid = false;
				currentPlayer->write_Client("You can't afford to construct this building");
			} else {
				currentPlayer->playerField.add_Card(currentPlayer->buildingCards[choice - 1]);
				currentPlayer->buildingCards.remove_Card(choice - 1);

				currentPlayer->set_Coins(-cardCost);

				valid = true;
				return false;
			}
		}
		catch (exception e) {
			currentPlayer->write_Client("Invalid input. Select a option by number!\r\n");
			valid = false;
		}
	}
	return true;
}

void Game::Reset() {
	for (int i = 1; i <= CharacterType::WARLORD; i++)
	{
		allCharacters[(CharacterType)i]->set_owner(nullptr);
	}
	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->characterCards.clear();
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
