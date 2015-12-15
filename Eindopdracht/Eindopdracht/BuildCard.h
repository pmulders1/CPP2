#pragma once
#include "BasicCard.h"

class BuildCard : public BasicCard
{
public:
	BuildCard(std::string name, int points, CharacterType type = CharacterType::NONE);

	int get_points() const { return points; }
	void set_points(const int points) { this->points = points; }

	~BuildCard();

private: 
	int points;
};

