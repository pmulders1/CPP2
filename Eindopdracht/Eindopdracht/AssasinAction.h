#pragma once
#include "BaseAction.h"
class AssasinAction : public BaseAction
{
public:
	AssasinAction();
	virtual void Execute(Game game);
	~AssasinAction();
};

