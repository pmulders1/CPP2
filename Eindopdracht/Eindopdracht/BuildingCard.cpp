#include "BuildingCard.h"

BuildingCard::BuildingCard(string name, int points, CharacterType type) : BasicCard(name, type), points(points)
{
}

void BuildingCard::execute() {
	std::cout << "Default" << std::endl;
}

BuildingCard::~BuildingCard()
{
}
