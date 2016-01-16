#include "ISubject.h"
#include <algorithm>
#include "Game.h"

void ISubject::Attach(shared_ptr<BuildingCard> card, shared_ptr<Player> player)
{
	observers[card->get_name()] = make_pair(card, player);
}
void ISubject::Detach(shared_ptr<BuildingCard> card)
{
	if (observers.count(card->get_name()) > 0) {
		observers.erase(card->get_name());
	}
}

void ISubject::ClearObservers()
{
	observers.clear();
}

void ISubject::Notify(string command, Game game)
{
	observers[command].first->execute(game);
}
