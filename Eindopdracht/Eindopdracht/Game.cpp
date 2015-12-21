#include "Game.h"
#include <algorithm>
#include <cstdlib>
#include <string> 
#include <ctime>

Game::Game()
{
	shared_ptr<BasicCard> assasin(new CharacterCard("Assasin", "Kill any other character.", CharacterType::ASSASSIN));
	shared_ptr<BasicCard> thief(new CharacterCard("Thief", "Steal gold from another player.", CharacterType::THIEF));
	shared_ptr<BasicCard> magician(new CharacterCard("Magician", "Trade all your buildcards with all buildcards of anoher player.", CharacterType::MAGICIAN));
	shared_ptr<BasicCard> king(new CharacterCard("King", "Start next round, Recieves gold from monuments.", CharacterType::KING));
	shared_ptr<BasicCard> bishop(new CharacterCard("Bishop", "Is protected against the Warlord, Recieves gold from church buildings.", CharacterType::BISHOP));
	shared_ptr<BasicCard> merchant(new CharacterCard("Merchant", "Recieves one extra gold, Recieves gold from commercial buildings.", CharacterType::MERCHANT));
	shared_ptr<BasicCard> architect(new CharacterCard("Architect", "Draws 2 extra building cards, Can build up to 3 buildings in one turn.", CharacterType::ARCHITECT));
	shared_ptr<BasicCard> warlord(new CharacterCard("Warlord", "Destroy any building, Recieves gold from military buildings.", CharacterType::WARLORD));
	charactersDeck.push_back(assasin);
	charactersDeck.push_back(thief);
	charactersDeck.push_back(magician);
	charactersDeck.push_back(king);
	charactersDeck.push_back(bishop);
	charactersDeck.push_back(merchant);
	charactersDeck.push_back(architect);
	charactersDeck.push_back(warlord);

	shared_ptr<BasicCard> estate(new BuildCard("Estate", 3, CharacterType::KING));
	shared_ptr<BasicCard> castle(new BuildCard("Castle", 4, CharacterType::KING));
	shared_ptr<BasicCard> palace(new BuildCard("Palace", 5, CharacterType::KING));
	buildingsDeck.push_back(estate);
	buildingsDeck.push_back(castle);
	buildingsDeck.push_back(palace);

	shared_ptr<BasicCard> tavern(new BuildCard("Tavern", 1, CharacterType::MERCHANT));
	shared_ptr<BasicCard> stores(new BuildCard("Stores", 2, CharacterType::MERCHANT));
	shared_ptr<BasicCard> market(new BuildCard("Market", 2, CharacterType::MERCHANT));
	shared_ptr<BasicCard> warehouse(new BuildCard("Warehouse", 3, CharacterType::MERCHANT));
	shared_ptr<BasicCard> port(new BuildCard("Port", 4, CharacterType::MERCHANT));
	shared_ptr<BasicCard> townhall(new BuildCard("Town Hall", 5, CharacterType::MERCHANT));
	buildingsDeck.push_back(tavern);
	buildingsDeck.push_back(stores);
	buildingsDeck.push_back(market);
	buildingsDeck.push_back(warehouse);
	buildingsDeck.push_back(port);
	buildingsDeck.push_back(townhall);

	shared_ptr<BasicCard> temple(new BuildCard("Temple", 1, CharacterType::BISHOP));
	shared_ptr<BasicCard> church(new BuildCard("Church", 2, CharacterType::BISHOP));
	shared_ptr<BasicCard> monastery(new BuildCard("Monastery", 3, CharacterType::BISHOP));
	shared_ptr<BasicCard> cathedral(new BuildCard("Cathedral", 5, CharacterType::BISHOP));
	buildingsDeck.push_back(temple);
	buildingsDeck.push_back(church);
	buildingsDeck.push_back(monastery);
	buildingsDeck.push_back(cathedral);

	shared_ptr<BasicCard> watchtower(new BuildCard("Watchtower", 1, CharacterType::WARLORD));
	shared_ptr<BasicCard> prison(new BuildCard("Prison", 2, CharacterType::WARLORD));
	shared_ptr<BasicCard> tournamentfield(new BuildCard("Tournament Field", 3, CharacterType::WARLORD));
	shared_ptr<BasicCard> stronghold(new BuildCard("Stronghold", 5, CharacterType::WARLORD));
	buildingsDeck.push_back(watchtower);
	buildingsDeck.push_back(prison);
	buildingsDeck.push_back(tournamentfield);
	buildingsDeck.push_back(stronghold);

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
	buildingsDeck.push_back(university);
}

void Game::HandleCommand(shared_ptr<Socket> client, shared_ptr<Player> player, string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);
	if (command == "join") {
		this->JoinPlayer(player, client);
	}
	else if (command == "start-game") {
		this->StartGame(player, client);
		if (players.size() == 2) {
			this->CharacterSelection2P(player, client);
		}
		if (players.size() == 3) {
			this->CharacterSelection3P(player, client);
		}

		for (int i = 1; i <= CharacterType::WARLORD; i++)
		{
			if (this->FindPlayer((CharacterType)i)) {
				this->PlayTurn((CharacterType)i);
			}
		}

	}
	else if (command == "help") {
		this->Help(player, client);
	}
}

void Game::JoinPlayer(shared_ptr<Player> player, shared_ptr<Socket> client) {
	this->players.push_back(make_pair(player, client));

	for (size_t i = 0; i < players.size(); i++)
	{
		*players[i].second << player->get_name() << " has joined the game\r\n";
	}
}

void Game::CharacterSelection2P(shared_ptr<Player> player, shared_ptr<Socket> client) {
	if (!this->started) {
		*client << "Invalid command. Game has not started yet. Try the start-game command to start the game.\r\n";
		return;
	}
	*players[0].second << "The following card will be placed face down on the table: \r\n";
	*players[0].second << charactersDeck[0]->print() << "\r\n";
	ontabledeck.push_back(make_pair(false, move(charactersDeck[0])));
	charactersDeck.erase(charactersDeck.begin());

	bool first = true;

	// iedere speler kan 2 kaarten pakken.
	for (size_t i = 0; i < players.size() * 2; i++) {
		currentPlayer = i;
		if (currentPlayer >= players.size()) {
			currentPlayer = currentPlayer - players.size();
		}
		bool valid = false;
		while (!valid) {
			*players[currentPlayer].second << "Choose one of the following Character cards:\r\n\r\n";
			for (size_t j = 0; j < charactersDeck.size(); j++)
			{
				*players[currentPlayer].second << to_string(j) << ". " << charactersDeck[j]->print();
			}
			*players[currentPlayer].second << "Select a card by number: \r\n";
			string temp{ players[currentPlayer].second->readline() };

			try {
				int cardnr = atoi(temp.c_str());
				if (cardnr < 0 || cardnr > charactersDeck.size() - 1) {
					throw exception();
				}
				players[currentPlayer].first->set_characterCard(false, charactersDeck[cardnr]);
				charactersDeck.erase(charactersDeck.begin() + cardnr);
				valid = true;
			}
			catch (exception e) {
				*players[currentPlayer].second << "Invalid input. Select a card by number!\r\n";
				valid = false;
			}
		}
		if (!first) {
			bool valid = false;
			while (!valid) {
				*players[currentPlayer].second << "\r\nChoose one of the following Character cards to lay down:\r\n\r\n";
				for (size_t j = 0; j < charactersDeck.size(); j++)
				{
					*players[currentPlayer].second << to_string(j) << ". " << charactersDeck[j]->print();
				}
				*players[currentPlayer].second << "Select a card by number: \r\n";
				string temp{ players[currentPlayer].second->readline() };

				try {
					int cardnr = atoi(temp.c_str());
					if (cardnr < 0 || cardnr > charactersDeck.size() - 1) {
						throw exception();
					}
					ontabledeck.push_back(make_pair(false, move(charactersDeck[cardnr])));
					charactersDeck.erase(charactersDeck.begin() + cardnr);
					valid = true;
				}
				catch (exception e) {
					*players[currentPlayer].second << "Invalid input. Select a card by number!\r\n";
					valid = false;
				}
			}
		}
		first = false;
	}
}

void Game::CharacterSelection3P(shared_ptr<Player> player, shared_ptr<Socket> client) {
	if (!this->started) {
		*client << "Invalid command. Game has not started yet. Try the start-game command to start the game.\r\n";
		return;
	}
	*players[0].second << "The following card will be placed face down on the table: \r\n";
	*players[0].second << charactersDeck[0]->print() << "\r\n";
	ontabledeck.push_back(make_pair(false, move(charactersDeck[0])));
	charactersDeck.erase(charactersDeck.begin());

	// iedere speler kan 2 kaarten pakken.
	for (size_t i = 0; i < players.size() * 2; i++) {
		currentPlayer = i;
		if (currentPlayer >= players.size()) {
			currentPlayer = currentPlayer - players.size();
		}
		bool valid = false;
		while (!valid) {
			*players[currentPlayer].second << "Choose one of the following Character cards:\r\n\r\n";
			for (size_t j = 0; j < charactersDeck.size(); j++)
			{
				*players[currentPlayer].second << to_string(j) << ". " << charactersDeck[j]->print();
			}
			*players[currentPlayer].second << "Select a card by number: \r\n";
			string temp{ players[currentPlayer].second->readline() };

			try {
				int cardnr = atoi(temp.c_str());
				if (cardnr < 0 || cardnr > charactersDeck.size() - 1) {
					throw exception();
				}
				players[currentPlayer].first->set_characterCard(false, charactersDeck[cardnr]);
				charactersDeck.erase(charactersDeck.begin() + cardnr);
				valid = true;
			}
			catch (exception e) {
				*players[currentPlayer].second << "Invalid input. Select a card by number!\r\n";
				valid = false;
			}
		}
	}

	ontabledeck.push_back(make_pair(false, move(charactersDeck[0])));
	charactersDeck.erase(charactersDeck.begin());
}

void Game::StartGame(shared_ptr<Player> player, shared_ptr<Socket> client) {

	if (players.size() >= 2 && !started) {
		this->started = true;

		srand(time(0));
		random_shuffle(buildingsDeck.begin(), buildingsDeck.end());
		random_shuffle(charactersDeck.begin(), charactersDeck.end());

		for (size_t i = 0; i < players.size(); i++)
		{
			*players[i].second << "Game has started. Good luck!\r\n";
			players[i].first->set_coins(2);

			for (int j = 0; j < 4; j++) {
				players[i].first->set_buildingCard(buildingsDeck[0]);
				buildingsDeck.erase(buildingsDeck.begin());
			}
		}
		players[0].first->set_isKing(true);
		*players[0].second << "You are the King. You may start the game.\r\n";
	}
	else if (players.size() == 0) {
		*client << "You must join first before you can start a game.\r\n";
	}
	else if (started) {
		*client << "Game already started.\r\n";
	}
	else {
		*client << "Not enough players to start a game.\r\n";
	}
}

bool Game::FindPlayer(CharacterType type) {
	for (size_t i = 0; i < players.size(); i++)
	{
		for (size_t j = 0; j < players[i].first->characterCards.size(); j++)
		{
			if (players[i].first->characterCards[j].second->CheckType(type)) {
				players[i].first->characterCards[j].first = true;
				currentPlayer = i;
				return true;
				break;
			}
		}
	}
	return false;
}

void Game::PlayTurn(CharacterType type) {
	// Scherm leegmaken en nieuwe waardes printen van de huidige speler/character
	*players[currentPlayer].second << "\u001B[2J";
	*players[currentPlayer].second << "You are playing as: " << ToString(type) << "\r\n";
	*players[currentPlayer].second << "Gold: " << to_string(players[currentPlayer].first->get_coins()) << "\r\n\r\n";
	*players[currentPlayer].second << "Buildings: \r\n";

	// Als de speler geen kaarten heeft gespeeld.
	if (players[currentPlayer].first->playedCards.size() == 0) {
		*players[currentPlayer].second << "No buildings on the field. \r\n";
	}
	for (size_t i = 0; i < players[currentPlayer].first->playedCards.size(); i++)
	{
		*players[currentPlayer].second << " " << players[currentPlayer].first->playedCards[i]->get_name() << "(" << ToString(players[currentPlayer].first->playedCards[i]->get_type()) << ", " << players[currentPlayer].first->playedCards[i]->printCost() << "):\r\n";
	}

	// Weergeven welke kaarten de speler in de hand heeft.
	*players[currentPlayer].second << "\r\nCards in hand: \r\n";
	if (players[currentPlayer].first->buildingCards.size() == 0) {
		*players[currentPlayer].second << "No cards in hand. \r\n";
	}
	for (size_t i = 0; i < players[currentPlayer].first->buildingCards.size(); i++)
	{
		*players[currentPlayer].second << " " << players[currentPlayer].first->buildingCards[i]->get_name() << "(" << ToString(players[currentPlayer].first->buildingCards[i]->get_type()) << ", " << players[currentPlayer].first->buildingCards[i]->printCost() << "):\r\n";
	}

	*players[currentPlayer].second << "\r\nMake a choice: \r\n";
	*players[currentPlayer].second << "1. Show players and playfield. \r\n";
	*players[currentPlayer].second << "2. Take 2 gold coins. \r\n";
	*players[currentPlayer].second << "3. Take 2 cards from deck. \r\n";
	*players[currentPlayer].second << "4. Use special ability of " << ToString(type) << ". \r\n";

	// Check voor geldige invoer
	bool valid = false;
	while (!valid) {
		string temp{ players[currentPlayer].second->readline() };

		try {
			int choice = atoi(temp.c_str());
			if (choice < 1 || choice > 4) {
				throw exception();
			}

			switch (choice) {
			case 1:
				ShowBoard();
				break;
			case 2:
				AddNewGold(2);
				break;
			case 3:
				DrawCards();
				break;
			case 4:
				break;
			default:
				break;
			}

			valid = true;
		}
		catch (exception e) {
			*players[currentPlayer].second << "Invalid input. Select a option by number!\r\n";
			valid = false;
		}
	}
	string temp{ players[currentPlayer].second->readline() };
}

void Game::ShowBoard() {
	shared_ptr<Socket> client = players[currentPlayer].second;
	*client << "\u001B[2J";
	*client << "Gameboard: \r\n\r\n";
	
	// Loopen door alle spelers en per speler de inhoud van hun veld laten zien.
	for (size_t i = 0; i < players.size(); i++) {
		// Naam printen van speler
		*client << players[i].first->get_name() << " (" << to_string(players[i].first->get_coins()) << " gold): \r\n";
		
		*client << "Plays as: \r\n\r\n";
		for (size_t x = 0; x < players[i].first->characterCards.size(); x++) {
			// Als de speler zijn character nog gesloten zijn omdat hij nog niet aan de beurt is 
			// geweest dan wordt er non available geprint.
			if (players[i].first->characterCards[x].first == true) {
				*client << to_string(x + 1) << ": " << players[i].first->characterCards[x].second->print();
			}
			// Anders wordt de naam van het character geprint.
			else {
				*client << to_string(x + 1) << ": Still unknown.\r\n" ;
			}
		}
		*client << "\r\nBuildings played: \r\n\r\n";
		
		if (players[i].first->playedCards.size() == 0) {
			*client << "No buildings on the field. \r\n";
		}
		for (size_t j = 0; j < players[i].first->playedCards.size(); j++)
		{
			*client << " " << players[i].first->playedCards[j]->get_name() << "(" << ToString(players[i].first->playedCards[j]->get_type()) << ", " << players[i].first->playedCards[j]->printCost() << "):\r\n";
		}
		*client << "\r\n";
	}
}

void Game::DrawCards() {
	*players[currentPlayer].second << "\u001B[2J";
	*players[currentPlayer].second << "Cards drawn:\r\n\r\n";
	
	for (size_t i = 0; i < 2; i++) {
		*players[currentPlayer].second << to_string(i) << ": " << buildingsDeck[i]->print();
	}

	*players[currentPlayer].second << "Choose a card to keep: ";

	// Check voor geldige invoer
	bool valid = false;
	while (!valid) {
		string temp{ players[currentPlayer].second->readline() };

		try {
			int choice = atoi(temp.c_str());
			if (choice < 0 || choice > 1) {
				throw exception();
			}

			players[currentPlayer].first->set_buildingCard(buildingsDeck[choice]);
			buildingsDeck.erase(buildingsDeck.begin() + choice);
			random_shuffle(buildingsDeck.begin(), buildingsDeck.end());

			valid = true;
		}
		catch (exception e) {
			*players[currentPlayer].second << "Invalid input. Select a option by number!\r\n";
			valid = false;
		}
	}
}

void Game::AddNewGold(int amount) {
	players[currentPlayer].first->set_coins(players[currentPlayer].first->get_coins() + amount);
	*players[currentPlayer].second << "New gold amount: " << players[currentPlayer].first->get_coins();
}

void Game::Help(shared_ptr<Player> player, shared_ptr<Socket> client) {
	*client << "Game turn:\r\n" ;
	*client << "Income: Take 2 gold pieces or take 2 build cards and put 1 back.\r\n" ;
	*client << "Building: Place one build card on your playfield and pay the amount of gold required to the bank.\r\n" ;
	*client << "Character Specialty: You can activate your characters special ability at any time.\r\n\r\n" ;

	*client << "Characters:\r\n" ;
	*client << "1. Assasin: Kill any other character.\r\n" ;
	*client << "2. Thief: Steal gold from another player.\r\n" ;
	*client << "3. Magician: Trade all your buildcards with another all buildcards of anoher player.\r\n" ;
	*client << "4. King: Start next round, Recieves gold from monuments.\r\n" ;
	*client << "5. Pedo: Is protected against the Warlord, Recieves gold from church buildings.\r\n" ;
	*client << "6. Merchant: Recieves one extra gold, Recieves gold from commercial buildings.\r\n" ;
	*client << "7. Architect: Draws 2 extra building cards, Can build up to 3 buildings in one turn.\r\n" ;
	*client << "8. Warlord: Destroy any building, Recieves gold from military buildings.\r\n" ;
}

Game::~Game()
{
}
