#include "BuildingCard.h"
#include "Game.h"

BuildingCard::BuildingCard(string name, int points, CharacterType type) : BasicCard(name, type), points(points)
{
}

void BuildingCard::execute(Game game) {
	std::cout << "Default" << std::endl;
}

BuildingCard::~BuildingCard()
{
}
