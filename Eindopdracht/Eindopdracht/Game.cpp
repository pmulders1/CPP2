#include "Game.h"

Game::Game()
{
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
