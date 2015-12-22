#pragma once
#include "BaseAction.h"
class MerchantAction : public BaseAction
{
public:
	MerchantAction();

	virtual void Execute(Game game);

	~MerchantAction();
};

