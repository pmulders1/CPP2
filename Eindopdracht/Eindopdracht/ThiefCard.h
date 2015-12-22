#pragma once
#include "CharacterCard.h"
class ThiefCard : public CharacterCard
{
public:
	ThiefCard();
	virtual void execute();
	~ThiefCard();
};

