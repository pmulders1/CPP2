#pragma once
#include "BaseAction.h"
class KingAction : public BaseAction
{
public:
	KingAction();
	virtual void Execute(Game game);
	~KingAction();
};

