#include "CharacterCard.h"

using namespace std;

CharacterCard::CharacterCard(string name, string description, CharacterType type) : BasicCard(name, type), description(description)
{
}

bool CharacterCard::CheckType(CharacterType type) {
	return this->get_type() == type;
}

CharacterCard::~CharacterCard()
{
}
