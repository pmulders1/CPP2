#pragma once
#include <memory>
#include "Socket.h"
#include "Player.hpp"
#include <algorithm>
#include <cstdlib>
#include <string> 
#include <ctime>
#include <vector>
#include <map>
#include "Deck.h"
#include "BuildingCard.h"
#include "AssasinCard.h"
#include "ThiefCard.h"
#include "MagicianCard.h"
#include "KingCard.h"
#include "BishopCard.h"
#include "MerchantCard.h"
#include "ArchitectCard.h"
#include "WarlordCard.h"
#include "CourtOfMiraclesCard.h"
#include "Dragonsgate.h"
#include "Dungeon.h"
#include "Graveyard.h"
#include "Labatorium.h"
#include "Library.h"
#include "MagiciansSchool.h"
#include "University.h"
#include "Workshop.h"
#include "Obversatorium.h"

using namespace std;

class Game
{
public:
	Game();
	void HandleCommand(shared_ptr<Player> player, string command);
	void JoinPlayer(shared_ptr<Player> player);
	void StartGame(shared_ptr<Player> player);
	void Help(shared_ptr<Player> player);
	void PlayTurn(string type);

	void CharacterSelection2P(shared_ptr<Player> player);
	void CharacterSelection3P(shared_ptr<Player> player);
	void CharacterReset();
	void GameReset();
	void FillCharactersDeck();
	void FillBuildingsDeck();
	void ShowBoard();
	void DrawCards();
	void CalculateWinner();
	shared_ptr<BasicCard> DrawSingleCard();
	bool ConstructBuildings();

	vector<shared_ptr<Player>> players;
	map<CharacterType, shared_ptr<CharacterCard>> allCharacters;
	Deck buildingsDeck;
	Deck charactersDeck;
	Deck onTableDeck;
	
	shared_ptr<Player> currentPlayer;

	bool playing = false;
	~Game();
};

