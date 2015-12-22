#pragma once
#include "Game.h"
class BaseAction
{
public:
	BaseAction();
	
	virtual void Execute(Game game) = 0;

	virtual ~BaseAction() = 0;
};

