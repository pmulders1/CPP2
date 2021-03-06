#pragma once
#include "BasicCard.h"
#include "Player.hpp"
using namespace std;
class CharacterCard : public BasicCard
{
public:
	CharacterCard(string name, CharacterType type = CharacterType::NONE);
	virtual string print() const {
		return this->get_name() + ": " + this->get_discription() + "\r\n";
	}

	virtual ostream& data(ostream& strm) const {
		strm << endl << get_beenStolen() << endl << get_alive() << endl << get_visible();
		return strm;
	}

	virtual void execute(Game game) = 0;

	string get_discription() const { return this->discription; }
	void set_discription(string val) { this->discription = val; }

	shared_ptr<Player> get_owner() const { return this->owner; }
	void set_owner(shared_ptr<Player> new_owner) { this->owner = new_owner; }

	bool get_alive() const { return this->alive; }
	void set_alive(bool val) { this->alive = val; }

	bool get_beenStolen() const { return this->beenStolen; }
	void set_beenStolen(bool val) { this->beenStolen = val; }

	virtual ~CharacterCard() = 0;
private:
	string discription;
	bool alive = true;
	bool beenStolen = false;
	shared_ptr<Player> owner;
};

