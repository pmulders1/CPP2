#pragma once
#include "BaseAction.h"
class TheifAction : public BaseAction
{
public:
	TheifAction();
	virtual void Execute(Game game);
	~TheifAction();
};

