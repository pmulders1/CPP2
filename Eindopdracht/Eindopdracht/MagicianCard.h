#pragma once
#include "CharacterCard.h"
class MagicianCard : public CharacterCard
{
public:
	MagicianCard();
	virtual void execute();
	~MagicianCard();
};

