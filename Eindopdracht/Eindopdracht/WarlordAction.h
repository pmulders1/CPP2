#pragma once
#include "BaseAction.h"
class WarlordAction : public BaseAction
{
public:
	WarlordAction();

	virtual void Execute(Game game);

	~WarlordAction();
};

