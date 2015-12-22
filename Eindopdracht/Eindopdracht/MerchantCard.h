#pragma once
#include "CharacterCard.h"
class MerchantCard : public CharacterCard
{
public:
	MerchantCard();
	virtual void execute();
	~MerchantCard();
};

