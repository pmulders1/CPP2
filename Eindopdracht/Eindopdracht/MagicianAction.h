#pragma once
#include "BaseAction.h"
class MagicianAction : public BaseAction
{
public:
	MagicianAction();
	virtual void Execute(Game game);
	~MagicianAction();
};

