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
#include "ISubject.h"

using namespace std;

class Game : public ISubject
{
public:
	Game();

	// Functions map
	typedef void(*FunctionsMap)(shared_ptr<Player>, Game& game);
	typedef map<string, FunctionsMap> functions_map;

	functions_map m;
	void call_script(const std::string& pFunction, shared_ptr<Player> player)
	{
		functions_map::const_iterator iter = m.find(pFunction);
		if (iter == m.end())
		{
			player->write_Client("Function not found! Please try again!\r\n");
		}
		else {
			(*iter->second)(player, *this);
		}
	}

	void HandleCommand(shared_ptr<Player> player, string command);
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

	// Observer pattren
	shared_ptr<BuildingCard> tempCard;
	vector<shared_ptr<BuildingCard>> notifyCards;
	
	shared_ptr<Player> currentPlayer;

	bool playing = false;
	~Game();
};

