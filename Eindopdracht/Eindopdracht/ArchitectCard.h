#pragma once
#include "CharacterCard.h"
class ArchitectCard : public CharacterCard
{
public:
	ArchitectCard();
	virtual void execute(Game game);
	~ArchitectCard();
};

