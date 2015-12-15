#pragma once
#include <vector>
#include "BasicCard.h"
#include "CharacterCard.h"
#include "BuildCard.h"
#include "SpecialCard.h"
#include "Player.hpp"
#include <memory>
#include "Socket.h"

using namespace std;
class Game
{
public:
	Game();

	void HandleCommand(shared_ptr<Socket> client, shared_ptr<Player> player, string command);
	void JoinPlayer(shared_ptr<Player> player, shared_ptr<Socket> client);
	vector<pair<shared_ptr<Player>, shared_ptr<Socket>>> players;
	
	// Moeten die shared of unique_ptr worden?
	vector<shared_ptr<BasicCard>> buildingsDeck;
	vector<shared_ptr<BasicCard>> charactersDeck;

	~Game();
};

