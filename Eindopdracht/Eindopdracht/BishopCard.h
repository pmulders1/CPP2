#pragma once
#include "CharacterCard.h"
class BishopCard : public CharacterCard
{
public:
	BishopCard();
	virtual void execute(Game game);
	~BishopCard();
};

