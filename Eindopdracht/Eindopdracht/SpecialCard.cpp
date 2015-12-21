#include "SpecialCard.h"

using namespace std;

SpecialCard::SpecialCard(string name, int points, CharacterType type) : BuildCard(name, points, type)
{
}

bool SpecialCard::CheckType(CharacterType type) {
	return this->get_type() == type;
}

SpecialCard::~SpecialCard()
{
}
