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

bool Game::FindPlayer(CharacterType type) {
	for (size_t i = 0; i < players.size(); i++)
	{
		for (size_t j = 0; j < players[i].first->characterCards.size(); j++)
		{
			if (players[i].first->characterCards[j]->CheckType(type)) {
				currentPlayer = i;
				return true;
				break;
			}
		}
	}
	return false;
}

void Game::HandleCommand(shared_ptr<Socket> client, shared_ptr<Player> player, string command) {
	transform(command.begin(), command.end(), command.begin(), ::tolower);
	if (command == "join") {
		this->JoinPlayer(player, client);
	} else if (command == "start-game") {
		this->StartGame(player, client);
		if(players.size() == 2){
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

	} else if (command == "help") {
		this->Help(player, client);
	}
}

void Game::PlayTurn(CharacterType type) {
	*players[currentPlayer].second << "\u001B[2J";
	*players[currentPlayer].second << "You are playing as: " << ToString(type) << "\r\n";
	*players[currentPlayer].second << "Gold: " << to_string(players[currentPlayer].first->get_coins()) << "\r\n";
	*players[currentPlayer].second << "Buildings: \r\n";
	for (size_t i = 0; i < players[currentPlayer].first->buildingCards.size(); i++)
	{
		*players[currentPlayer].second << " " << players[currentPlayer].first->buildingCards[i]->get_name() << "(" << ToString(players[currentPlayer].first->buildingCards[i]->get_type()) << ", " << players[currentPlayer].first->buildingCards[i]->printCost() << "):\r\n";
	}
	*players[currentPlayer].second << "Cards in hand: \r\n" << m.prompt;
	for (size_t i = 0; i < players[currentPlayer].first->buildingCards.size(); i++)
	{
		*players[currentPlayer].second << " " << players[currentPlayer].first->buildingCards[i]->get_name() << "(" << ToString(players[currentPlayer].first->buildingCards[i]->get_type()) << ", " << players[currentPlayer].first->buildingCards[i]->printCost() << "):\r\n";
	}
	string temp{ players[currentPlayer].second->readline() };
}

void Game::StartGame(shared_ptr<Player> player, shared_ptr<Socket> client) {

	if (players.size() >= 2 && !started) {
		this->started = true;

		srand(time(0));
		random_shuffle(buildingsDeck.begin(), buildingsDeck.end());
		random_shuffle(charactersDeck.begin(), charactersDeck.end());

		for (size_t i = 0; i < players.size(); i++)
		{
			*players[i].second << "Game has started. Good luck!\r\n" << m.prompt;
			players[i].first->set_coins(2);

			for (int j = 0; j < 4; j++){
				players[i].first->set_buildingCard(buildingsDeck[0]);
				buildingsDeck.erase(buildingsDeck.begin());
			}
		}
		players[0].first->set_isKing(true);
		*players[0].second << "You are the King. You may start the game.\r\n" << m.prompt;
	} else if(players.size() == 0){
		*client << "You must join first before you can start a game.\r\n" << m.prompt;
	} else if (started) {
		*client << "Game already started.\r\n" << m.prompt;
	} else {
		*client << "Not enough players to start a game.\r\n" << m.prompt;
	}
}

void Game::CharacterSelection2P(shared_ptr<Player> player, shared_ptr<Socket> client) {
	if(!this->started){
		*client << "Invalid command. Game has not started yet. Try the start-game command to start the game.\r\n" << m.prompt;
		return;
	}
	*players[0].second << "The following card will be placed face down on the table: \r\n" << m.prompt;
	*players[0].second << charactersDeck[0]->print() << "\r\n" << m.prompt;
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
			*players[currentPlayer].second << "Choose one of the following Character cards:\r\n\r\n" << m.prompt;
			for (size_t j = 0; j < charactersDeck.size(); j++)
			{
				*players[currentPlayer].second << to_string(j) << ". " << charactersDeck[j]->print() << m.prompt;
			}
			*players[currentPlayer].second << "Select a card by number: \r\n" << m.prompt;
			string temp{ players[currentPlayer].second->readline() };
			
			try {
				int cardnr = atoi(temp.c_str());
				if (cardnr < 0 || cardnr > charactersDeck.size() - 1) {
					throw exception();
				}
				players[currentPlayer].first->set_characterCard(charactersDeck[cardnr]);
				charactersDeck.erase(charactersDeck.begin() + cardnr);
				valid = true;
			}
			catch (exception e) {
				*players[currentPlayer].second << "Invalid input. Select a card by number!\r\n" << m.prompt;
				valid = false;
			}
		}
		if (!first) {
			bool valid = false;
			while (!valid) {
				*players[currentPlayer].second << "\r\nChoose one of the following Character cards to lay down:\r\n\r\n" << m.prompt;
				for (size_t j = 0; j < charactersDeck.size(); j++)
				{
					*players[currentPlayer].second << to_string(j) << ". " << charactersDeck[j]->print() << m.prompt;
				}
				*players[currentPlayer].second << "Select a card by number: \r\n" << m.prompt;
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
					*players[currentPlayer].second << "Invalid input. Select a card by number!\r\n" << m.prompt;
					valid = false;
				}
			}
		}
		first = false;
	}
}

void Game::CharacterSelection3P(shared_ptr<Player> player, shared_ptr<Socket> client) {
	if (!this->started) {
		*client << "Invalid command. Game has not started yet. Try the start-game command to start the game.\r\n" << m.prompt;
		return;
	}
	*players[0].second << "The following card will be placed face down on the table: \r\n" << m.prompt;
	*players[0].second << charactersDeck[0]->print() << "\r\n" << m.prompt;
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
			*players[currentPlayer].second << "Choose one of the following Character cards:\r\n\r\n" << m.prompt;
			for (size_t j = 0; j < charactersDeck.size(); j++)
			{
				*players[currentPlayer].second << to_string(j) << ". " << charactersDeck[j]->print() << m.prompt;
			}
			*players[currentPlayer].second << "Select a card by number: \r\n" << m.prompt;
			string temp{ players[currentPlayer].second->readline() };

			try {
				int cardnr = atoi(temp.c_str());
				if (cardnr < 0 || cardnr > charactersDeck.size() - 1) {
					throw exception();
				}
				players[currentPlayer].first->set_characterCard(charactersDeck[cardnr]);
				charactersDeck.erase(charactersDeck.begin() + cardnr);
				valid = true;
			}
			catch (exception e) {
				*players[currentPlayer].second << "Invalid input. Select a card by number!\r\n" << m.prompt;
				valid = false;
			}
		}
	}

	ontabledeck.push_back(make_pair(false, move(charactersDeck[0])));
	charactersDeck.erase(charactersDeck.begin());
}

void Game::Help(shared_ptr<Player> player, shared_ptr<Socket> client) {
	*client << "Game turn:\r\n" << m.prompt;
	*client << "Income: Take 2 gold pieces or take 2 build cards and put 1 back.\r\n" << m.prompt;
	*client << "Building: Place one build card on your playfield and pay the amount of gold required to the bank.\r\n" << m.prompt;
	*client << "Character Specialty: You can activate your characters special ability at any time.\r\n\r\n" << m.prompt;

	*client << "Characters:\r\n" << m.prompt;
	*client << "1. Assasin: Kill any other character.\r\n" << m.prompt;
	*client << "2. Thief: Steal gold from another player.\r\n" << m.prompt;
	*client << "3. Magician: Trade all your buildcards with another all buildcards of anoher player.\r\n" << m.prompt;
	*client << "4. King: Start next round, Recieves gold from monuments.\r\n" << m.prompt;
	*client << "5. Pedo: Is protected against the Warlord, Recieves gold from church buildings.\r\n" << m.prompt;
	*client << "6. Merchant: Recieves one extra gold, Recieves gold from commercial buildings.\r\n" << m.prompt;
	*client << "7. Architect: Draws 2 extra building cards, Can build up to 3 buildings in one turn.\r\n" << m.prompt;
	*client << "8. Warlord: Destroy any building, Recieves gold from military buildings.\r\n" << m.prompt;
}

void Game::JoinPlayer(shared_ptr<Player> player, shared_ptr<Socket> client) {
	this->players.push_back(make_pair(player, client));

	for (size_t i = 0; i < players.size(); i++)
	{
		*players[i].second << player->get_name() << " has joined the game\r\n" << m.prompt;
	}
}

Game::~Game()
{
}
