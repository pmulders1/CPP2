#pragma once
#include <memory>
#include <map>
#include "BuildingCard.h"
#include "Player.hpp"

using namespace std;

class Game;

class ISubject
{
public:
	map<string, pair<shared_ptr<BuildingCard>, shared_ptr<Player>>> observers;
	void Attach(shared_ptr<BuildingCard> card, shared_ptr<Player>);
	void Detach(shared_ptr<BuildingCard> card);
	void ClearObservers();
	void Notify(string command, Game game);
};

