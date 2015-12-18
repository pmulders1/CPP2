#pragma once
#include "BasicCard.h"

using namespace std;
class BuildCard : public BasicCard
{
public:
	BuildCard(std::string name, int points, CharacterType type = CharacterType::NONE);

	int get_points() const { return points; }
	void set_points(const int points) { this->points = points; }

	virtual string print() const {
		return this->get_name() + ": " + to_string(this->get_points()) + "\r\n";
	}

	~BuildCard();

private: 
	int points;
};

