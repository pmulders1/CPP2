#pragma once
#include "BasicCard.h"

class BuildingCard : public BasicCard
{
public:
	BuildingCard(string name, int points, CharacterType type = CharacterType::NONE);
	virtual void execute(Game game);

	virtual ostream& data(ostream& strm) const {
		return strm;
	}

	virtual string print() const {
		return this->get_name() + " - Type " + ToString(this->get_type()) +" (" + to_string(this->get_points()) + "): " + this->get_discription() + "\r\n";
	}

	~BuildingCard();

	void set_points(int amount) { this->points = amount; }
	int get_points() const { return this->points; }

	bool get_special() const { return this->special; }
	void set_special(bool value) { this->special = value; }

private:
	int points;
	bool special;
};

