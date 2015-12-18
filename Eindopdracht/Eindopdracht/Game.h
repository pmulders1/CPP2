#pragma once
#include <vector>
#include "BasicCard.h"
#include "CharacterCard.h"
#include "BuildCard.h"
#include "SpecialCard.h"
#include "Player.hpp"
#include <memory>
#include "Socket.h"
#include <map>

using namespace std;
struct machiavelli {
	const int tcp_port{ 1080 };
	const string prompt{ "machiavelli> " };
};

class Game
{
public:
	Game();
	machiavelli m;

	bool started = false;

	int jackpot = 30;

	void HandleCommand(shared_ptr<Socket> client, shared_ptr<Player> player, string command);
	void JoinPlayer(shared_ptr<Player> player, shared_ptr<Socket> client);
	void StartGame(shared_ptr<Player> player, shared_ptr<Socket> client);
	void CharacterSelection(shared_ptr<Player> player, shared_ptr<Socket> client);
	void Help(shared_ptr<Player> player, shared_ptr<Socket> client);

	vector<pair<shared_ptr<Player>, shared_ptr<Socket>>> players;
	
	vector<pair<bool, shared_ptr<BasicCard>>> ontabledeck;
	vector<shared_ptr<BasicCard>> buildingsDeck;
	vector<shared_ptr<BasicCard>> charactersDeck;

	~Game();
};

