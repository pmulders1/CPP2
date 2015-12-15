#pragma once
#include "BuildCard.h"

class SpecialCard : public BuildCard
{
public:
	SpecialCard(std::string name, int points, CharacterType type = CharacterType::NONE);
	~SpecialCard();
};

