#include "BuildCard.h"

using namespace std;

BuildCard::BuildCard(string name, int points, CharacterType type) : BasicCard(name, type), points(points)
{
}

bool BuildCard::CheckType(CharacterType type) {
	return this->get_type() == type;
}

BuildCard::~BuildCard()
{
}
