#include "CharacterCard.h"

using namespace std;

CharacterCard::CharacterCard(string name, string description, CharacterType type) : BasicCard(name, type), description(description)
{
}


CharacterCard::~CharacterCard()
{
}
