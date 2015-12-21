#pragma once
#include "BasicCard.h"

using namespace std;
class BuildCard : public BasicCard
{
public:
	BuildCard(std::string name, int points, CharacterType type = CharacterType::NONE);

	int get_points() const { return points; }
	void set_points(const int points) { this->points = points; }

	virtual string printCost() const {
		return to_string(this->get_points());
	}

	virtual string print() const {
		return this->get_name() + ": " + to_string(this->get_points()) + "\r\n";
	}
	virtual bool CheckType(CharacterType type);
	~BuildCard();

private: 
	int points;
};

