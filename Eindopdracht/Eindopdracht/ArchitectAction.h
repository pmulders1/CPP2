#pragma once
#include "BaseAction.h"
class ArchitectAction : public BaseAction
{
public:
	ArchitectAction();

	virtual void Execute(Game game);

	~ArchitectAction();
};

