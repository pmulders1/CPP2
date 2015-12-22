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
	int currentPlayer;

	void HandleCommand(shared_ptr<Socket> client, shared_ptr<Player> player, string command);
	void JoinPlayer(shared_ptr<Player> player, shared_ptr<Socket> client);
	void StartGame(shared_ptr<Player> player, shared_ptr<Socket> client);
	void CharacterSelection2P(shared_ptr<Player> player, shared_ptr<Socket> client);
	void CharacterSelection3P(shared_ptr<Player> player, shared_ptr<Socket> client);
	void Help(shared_ptr<Player> player, shared_ptr<Socket> client);
	
	// Gamefuncties
	void ShowBoard();
	void AddNewGold(int amount);
	void DrawCards();

	pair<int, int> FindPlayer(CharacterType type);
	void KillPlayer(CharacterType type);
	void PlayTurn(CharacterType type);
	
	vector<pair<shared_ptr<Player>, shared_ptr<Socket>>> players;
	
	vector<pair<bool, shared_ptr<BasicCard>>> ontabledeck;
	vector<shared_ptr<BasicCard>> buildingsDeck;
	vector<shared_ptr<BasicCard>> charactersDeck;

	~Game();
};

