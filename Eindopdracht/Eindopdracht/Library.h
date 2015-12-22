#pragma once
#include "BuildingCard.h"
class Library : public BuildingCard
{
public:
	Library();
	virtual void execute();
	~Library();
};

