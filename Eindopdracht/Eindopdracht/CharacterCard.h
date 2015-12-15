#pragma once
#include "BasicCard.h"

class CharacterCard : public BasicCard
{
public:
	CharacterCard(std::string name, CharacterType type = CharacterType::NONE);
	~CharacterCard();
};

