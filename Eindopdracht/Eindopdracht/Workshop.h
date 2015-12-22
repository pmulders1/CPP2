#pragma once
#include "BuildingCard.h"
class Workshop : public BuildingCard
{
public:
	Workshop();
	virtual void execute();
	~Workshop();
};

