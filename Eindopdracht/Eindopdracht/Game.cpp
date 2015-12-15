#include "Game.h"

Game::Game()
{
	shared_ptr<BasicCard> assasin(new CharacterCard("Assasin", CharacterType::ASSASSIN));
	shared_ptr<BasicCard> thief(new CharacterCard("Thief", CharacterType::THIEF));
	shared_ptr<BasicCard> magician(new CharacterCard("Magician", CharacterType::MAGICIAN));
	shared_ptr<BasicCard> king(new CharacterCard("King", CharacterType::KING));
	shared_ptr<BasicCard> bishop(new CharacterCard("Bishop", CharacterType::BISHOP));
	shared_ptr<BasicCard> merchant(new CharacterCard("Merchant", CharacterType::MERCHANT));
	shared_ptr<BasicCard> architect(new CharacterCard("Architect", CharacterType::ARCHITECT));
	shared_ptr<BasicCard> warlord(new CharacterCard("Warlord", CharacterType::WARLORD));
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
	if (command == "Join") {
		this->JoinPlayer(player, client);
	}
}

void Game::JoinPlayer(shared_ptr<Player> player, shared_ptr<Socket> client) {
	// Move constructor
	this->players.push_back(make_pair(player, client));

	for (size_t i = 0; i < players.size(); i++)
	{
		*players[i].second << player->get_name() << " has joined the game";
	}
}

Game::~Game()
{
}
