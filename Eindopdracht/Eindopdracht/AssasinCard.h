#pragma once
#include "CharacterCard.h"

using namespace std;
class AssasinCard : public CharacterCard
{
public:
	AssasinCard();
	virtual void execute();
	~AssasinCard();
};

