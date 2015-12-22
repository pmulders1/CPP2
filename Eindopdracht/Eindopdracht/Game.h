#pragma once
#include <memory>
#include "Socket.h"
#include "Player.hpp"
#include <algorithm>
#include <cstdlib>
#include <string> 
#include <ctime>
#include <vector>
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

using namespace std;

class Game
{
public:
	Game();
	void HandleCommand(shared_ptr<Player> player, string command);
	void JoinPlayer(shared_ptr<Player> player);
	void StartGame(shared_ptr<Player> player);
	void Help(shared_ptr<Player> player);

	vector<shared_ptr<Player>> players;
	Deck buildingsDeck;
	Deck charactersDeck;


	bool playing = false;
	~Game();
};

