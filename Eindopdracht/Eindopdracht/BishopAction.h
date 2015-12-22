#pragma once
#include "BaseAction.h"
class BishopAction : public BaseAction
{
public:
	BishopAction();
	virtual void Execute(Game game);
	~BishopAction();
};

