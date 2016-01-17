#include "Game.h"

void JoinPlayer(shared_ptr<Player> player, Game& game) {
	if (!game.playing) {
		game.players.push_back(player);

		for (size_t i = 0; i < game.players.size(); i++)
		{
			game.players[i]->write_Client(player->get_name() + " has joined the game\r\n");
		}
	}
	else {
		player->write_Client("Game already started.\r\n");
	}
}
void StartGame(shared_ptr<Player> player, Game& game) {
	if (game.players.size() > 1 && !game.playing) {
		bool gameOver = false;
		game.playing = true;

		// Shuffle decks
		game.buildingsDeck.shuffle();
		game.charactersDeck.shuffle();

		for (size_t i = 0; i < game.players.size(); i++)
		{
			game.players[i]->write_Client("Game has started. Good luck!\r\n");
			game.players[i]->set_Coins(2);

			for (int j = 0; j < 4; j++) {
				game.players[i]->buildingCards.add_Card(move(game.buildingsDeck[0]));
				game.buildingsDeck.remove_Card(0);
			}
		}
		game.players[0]->set_King(true);
		game.players[0]->write_Client("You are the King. You may start the game.\r\n");

		while (!gameOver) {
			
			if (game.players.size() == 2) {
				game.CharacterSelection2P(player);
			}
			if (game.players.size() == 3) {
				game.CharacterSelection3P(player);
			}

			for (int i = 1; i <= CharacterType::WARLORD; i++)
			{
				CharacterType type = static_cast<CharacterType>(i);
				if (game.allCharacters[type]->get_owner() == nullptr) {
					continue;
				}

				game.currentPlayer = game.allCharacters[type]->get_owner();
				if (!game.allCharacters[type]->get_alive()) {
					game.currentPlayer->write_Client(game.allCharacters[type]->get_name() + " has been killed this round so we are skipping its turn.");
					game.currentPlayer->readline();
				}
				else {
					if (dynamic_pointer_cast<CharacterCard>(game.currentPlayer->characterCards[type])->get_beenStolen()) {
						game.currentPlayer->write_Client("You have been stolen by the thief!\r\n");
						game.currentPlayer->write_Client("All of your coins will be transfered to the thief!\r\n");

						shared_ptr<Player> thief = game.allCharacters[CharacterType::THIEF]->get_owner();
						thief->set_Coins(game.currentPlayer->get_Coins());
						game.currentPlayer->set_Coins(-game.currentPlayer->get_Coins());
						game.currentPlayer->readline();
					}

					game.currentPlayer->characterCards[type]->set_visible(true);
					game.onTableDeck.add_Card(game.currentPlayer->characterCards[type]);

					game.PlayTurn(ToString(type));
					if (game.currentPlayer->playerField.size() >= 8) {
						if (!gameOver) {
							game.currentPlayer->set_FirsToEight(true);
						}
						gameOver = true;
					}
				}
				game.WriteGameStatus();
			}
		}
		game.CalculateWinner();
		game.GameReset();
	}
	else if (game.players.size() == 0) {
		player->write_Client("You must join first before you can start a game.\r\n");
	}
	else if (game.playing) {
		player->write_Client("Game already started.\r\n");
	}
	else {
		player->write_Client("Not enough players to start a game.\r\n");
	}
}
void Help(shared_ptr<Player> player, Game& game) {
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
void LoadGame(shared_ptr<Player> player, Game& game) {
	if (game.players.size() > 1 && !game.playing) {
		ifstream file2{ "data.txt" };
		try{
			file2 >> game;
		}
		catch (...) {
			throw exception("Corrupte save file. Unable to load game");
		}
	}
	else if (game.players.size() == 0) {
		player->write_Client("You must join first before you can load a game.\r\n");
	}
	else if (game.playing) {
		player->write_Client("Game already started.\r\n");
	}
	else {
		player->write_Client("Not enough players to load a game.\r\n");
	}
}

Game::Game()
{
	m["join"] = &JoinPlayer;
	m["start-game"] = &StartGame;
	m["help"] = &Help;
	m["load-game"] = &LoadGame;

	srand(time(0));
	FillCharactersDeck();
	FillBuildingsDeck();
}

void Game::HandleCommand(shared_ptr<Player> player, string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);
	call_script(command, player);
}

void Game::CharacterSelection2P(shared_ptr<Player> player) {
	this->CharacterReset();
	int index = 0;
	for (; index < players.size(); index++)
	{
		if (players[index]->get_King()) {
			break;
		}
	}
	players[index]->write_Client("\u001B[2J");
	players[index]->write_Client("The following card will be placed face down on the table: \r\n");
	players[index]->write_Client(charactersDeck[0]->print() + "\r\n");
	players[index]->readline();

	charactersDeck[0]->set_visible(false);
	onTableDeck.add_Card(charactersDeck[0]);
	charactersDeck.remove_Card(0);

	bool first = true;
	int count = 0;
	while (count < players.size() * 2) {
		currentPlayer = players[index];
		currentPlayer->write_Client("\u001B[2J");
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

				count++;

				if (charactersDeck[cardnr]->get_type() == CharacterType::KING && !currentPlayer->get_King()) {
					for (size_t i = 0; i < players.size(); i++)
					{
						if (players[i]->get_King()) {
							players[i]->set_King(false);
							currentPlayer->set_King(true);
							break;
						}
					}
				}
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

		index++;
		if (index > players.size() - 1) {
			index = 0;
		}
	}
}

void Game::CharacterSelection3P(shared_ptr<Player> player) {
	this->CharacterReset();
	int index = 0;
	for (; index < players.size(); index++)
	{
		if (players[index]->get_King()) {
			break;
		}
	}

	players[index]->write_Client("The following card will be placed face down on the table: \r\n");
	players[index]->write_Client(charactersDeck[0]->print() + "\r\n");

	charactersDeck[0]->set_visible(false);
	onTableDeck.add_Card(charactersDeck[0]);
	charactersDeck.remove_Card(0);

	// iedere speler kan 2 kaarten pakken.
	int count = 0;
	while (count < players.size() * 2) {
		currentPlayer = players[index];

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
				count++;

				valid = true;
			}
			catch (exception e) {
				currentPlayer->write_Client("Invalid input. Select a card by number!\r\n");
				valid = false;
			}
		}
		index++;
		if (index > players.size() - 1) {
			index = 0;
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
						currentPlayer->characterCards[ToEnum(type)]->execute(*this);
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

shared_ptr<BasicCard> Game::DrawSingleCard() {
	buildingsDeck.shuffle();
	shared_ptr<BasicCard> temp = buildingsDeck[0];
	buildingsDeck.remove_Card(0);
	return temp;
}

void Game::DrawCards() {
	currentPlayer->write_Client("\u001B[2J");
	currentPlayer->write_Client("Cards drawn:\r\n\r\n");
	buildingsDeck.shuffle();
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

void Game::CalculateWinner() {
	// Berekening alle scores
	vector<pair<shared_ptr<Player>, int>> scores;
	for (size_t i = 0; i < players.size(); i++)
	{
		this->players[i]->CalculateScore();
		scores.push_back(make_pair(this->players[i],this->players[i]->get_Points()));
	}
	sort(scores.begin(), scores.end(), [](const std::pair<shared_ptr<Player>, int> &left, const std::pair<shared_ptr<Player>, int> &right) {
		return left.second < right.second;
	});

	// Berekening voor meerdere gelijke scores
	int highest = scores[0].second;
	vector<pair<shared_ptr<Player>, int>> buildingsScores;
	buildingsScores.push_back(make_pair(scores[0].first, scores[0].first->CalculateBuildingScore()));
	for (size_t i = 1; i < scores.size(); i++)
	{
		if (scores[i].second == highest) {
			buildingsScores.push_back(make_pair(scores[i].first, scores[i].first->CalculateBuildingScore()));
		}
	}
	sort(buildingsScores.begin(), buildingsScores.end(), [](const std::pair<shared_ptr<Player>, int> &left, const std::pair<shared_ptr<Player>, int> &right) {
		return left.second < right.second;
	});
	
	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->write_Client("Player " + buildingsScores[0].first->get_name() + " is the winner! The rest is a LOSER!! \r\nThank you for playing!\r\n");
	}
}

bool Game::ConstructBuildings() {
	currentPlayer->write_Client("\u001B[2J");
	currentPlayer->write_Client("Gold amount: \r\n");
	currentPlayer->write_Client(to_string(currentPlayer->get_Coins())+" gold pieces.\r\n\r\n");
	currentPlayer->write_Client("Cards in hand: \r\n\r\n");

	for (size_t i = 0; i < currentPlayer->buildingCards.size(); i++)
	{
		currentPlayer->write_Client(to_string(i) + ". " + currentPlayer->buildingCards[i]->print());
	}
	if (currentPlayer->buildingCards.size() == 0) {
		currentPlayer->write_Client("No cards in hand. You can't construct any buildings.\r\n");
		currentPlayer->write_Client("Returning to main menu.");
		currentPlayer->readline();
		return false;
	}

	currentPlayer->write_Client("\r\nType 'stop' to stop building.\r\n");
	currentPlayer->write_Client("\r\nChoose a card to build: \r\n");

	// Check voor geldige invoer
	bool valid = false;
	while (!valid) {
		string temp{ currentPlayer->readline() };


		try {
			if (temp == "stop") {
				currentPlayer->write_Client("\u001B[2J");
				currentPlayer->write_Client("Current playfield:\r\n\r\n");

				for (int i = 0; i < currentPlayer->playerField.size(); i++)
				{
					currentPlayer->playerField[i]->print();
				}

				currentPlayer->write_Client("\r\nPress any key to continue...\r\n");
				currentPlayer->readline();
				return false;
			}

			int choice = atoi(temp.c_str());
			if (choice < 0 || choice > currentPlayer->buildingCards.size() - 1) {
				throw exception();
			}
			shared_ptr<BuildingCard> card = dynamic_pointer_cast<BuildingCard>(currentPlayer->buildingCards[choice]);
			if (card->get_points() > currentPlayer->get_Coins()) {
				valid = false;
				currentPlayer->write_Client("You can't afford to construct this building");
			} else {
				if (find(notifyCards.begin(), notifyCards.end(), card) != notifyCards.end()) {
					this->Attach(card, currentPlayer);
				}
				
				currentPlayer->playerField.add_Card(currentPlayer->buildingCards[choice]);
				currentPlayer->buildingCards.remove_Card(choice);

				currentPlayer->set_Coins(-card->get_points());

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

void Game::CharacterReset() {
	onTableDeck.clear();
	for (int i = 1; i <= CharacterType::WARLORD; i++)
	{
		allCharacters[(CharacterType)i]->set_owner(nullptr);
	}
	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->characterCards.clear();
	}

	charactersDeck.clear();
	for (int i = 1; i <= CharacterType::WARLORD; i++)
	{
		charactersDeck.add_Card(allCharacters[static_cast<CharacterType>(i)]);
	}
	charactersDeck.shuffle();
}

void Game::GameReset() {
	for (size_t i = 0; i < players.size(); i++)
	{
		players[i]->Reset();
	}
	FillBuildingsDeck();
	FillCharactersDeck();
	ClearObservers();
	onTableDeck.clear();
	playing = false;
}

void Game::FillBuildingsDeck() {
	buildingsDeck.clear();
	notifyCards.clear();
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

	shared_ptr<BuildingCard> gv = shared_ptr<BuildingCard>{ new Graveyard() };
	notifyCards.push_back(gv);

	buildingsDeck.add_Card(shared_ptr<BasicCard>{new CourtOfMiraclesCard()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Dungeon()});
	buildingsDeck.add_Card(gv);
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Labatorium()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Workshop()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Obversatorium()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Library()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new MagiciansSchool()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new Dragonsgate()});
	buildingsDeck.add_Card(shared_ptr<BasicCard>{new University()});
}

void Game::FillCharactersDeck() {
	allCharacters.clear();
	allCharacters.insert(make_pair(CharacterType::ASSASSIN, shared_ptr<AssasinCard>{new AssasinCard()}));
	allCharacters.insert(make_pair(CharacterType::THIEF, shared_ptr<ThiefCard>{new ThiefCard()}));
	allCharacters.insert(make_pair(CharacterType::MAGICIAN, shared_ptr<MagicianCard>{new MagicianCard()}));
	allCharacters.insert(make_pair(CharacterType::KING, shared_ptr<KingCard>{new KingCard()}));
	allCharacters.insert(make_pair(CharacterType::BISHOP, shared_ptr<BishopCard>{new BishopCard()}));
	allCharacters.insert(make_pair(CharacterType::MERCHANT, shared_ptr<MerchantCard>{new MerchantCard()}));
	allCharacters.insert(make_pair(CharacterType::ARCHITECT, shared_ptr<ArchitectCard>{new ArchitectCard()}));
	allCharacters.insert(make_pair(CharacterType::WARLORD, shared_ptr<WarlordCard>{new WarlordCard()}));

	charactersDeck.clear();
	for (int i = 1; i <= CharacterType::WARLORD; i++)
	{
		charactersDeck.add_Card(allCharacters[static_cast<CharacterType>(i)]);
	}
}

void Game::WriteGameStatus() {
	ofstream file{ "data.txt" };
	file << *this;
}

void Game::ClaimBuildingCards(istream& strm, Player& player){
	string omschrijving;
	strm >> omschrijving;
	string cardName;
	strm >> cardName;
	// door alle kaarten van een speler in de save file loopen
	while (cardName != "EndBuildingCards") {

		bool found = false;

		// door alle beschikbare kaarten loopen en reserveren.
		for (size_t b = 0; b < this->buildingsDeck.size(); b++)
		{
			if (this->buildingsDeck[b]->get_name() == cardName) {
				found = true;
				// reserveren
				player.buildingCards.add_Card(this->buildingsDeck[b]);
				this->buildingsDeck.remove_Card(b);
				break;
			}
		}
		// Kaart is niet gevonden. melding geven.
		if (!found) {
			throw exception("Invalid save file. One of the building cards is either already taken or does not excist.");
		}

		// verzetten naar de volgende kaart
		strm >> cardName;
	}
}

void Game::ClaimCharacterCards(istream& strm, Player& player) {
	string omschrijving;
	strm >> omschrijving;
	string cardName;
	strm >> cardName;
	// door alle kaarten van een speler in de save file loopen
	while (cardName != "EndCharacterCards") {

		bool found = false;

		// door alle beschikbare kaarten loopen en reserveren.
		for (size_t b = 0; b < this->charactersDeck.size(); b++)
		{
			if (this->charactersDeck[b]->get_name() == cardName) {
				found = true;
				// reserveren
				player.characterCards.add_Card(this->charactersDeck[b]);
				this->charactersDeck.remove_Card(b);
				break;
			}
		}
		// Kaart is niet gevonden. melding geven.
		if (!found) {
			throw exception("Invalid save file. One of the building cards is either already taken or does not excist.");
		}

		// verzetten naar de volgende kaart
		strm >> cardName;
	}
}

void Game::ClaimPlayerFieldCards(istream& strm, Player& player) {
	string omschrijving;
	strm >> omschrijving;
	string cardName;
	strm >> cardName;
	// door alle kaarten van een speler in de save file loopen
	while (cardName != "EndPlayerField") {

		bool found = false;

		// door alle beschikbare kaarten loopen en reserveren.
		for (size_t b = 0; b < this->buildingsDeck.size(); b++)
		{
			if (this->buildingsDeck[b]->get_name() == cardName) {
				found = true;
				// reserveren
				player.playerField.add_Card(this->buildingsDeck[b]);
				this->buildingsDeck.remove_Card(b);
				break;
			}
		}
		// Kaart is niet gevonden. melding geven.
		if (!found) {
			throw exception("Invalid save file. One of the building cards is either already taken or does not excist.");
		}

		// verzetten naar de volgende kaart
		strm >> cardName;
	}
}

Game::~Game()
{
}
