#pragma once
#include "BasicCard.h"
#include <string>

using namespace std;
class CharacterCard : public BasicCard
{
public:
	CharacterCard(string name, string description, CharacterType type = CharacterType::NONE);
	
	virtual string print() const {
		return this->get_name() + ": " + this->get_description() + "\r\n";
	}
	virtual string printCost() const { return ""; }
	string get_description() const { return this->description; }
	void set_description(const string& description) { this->description = description; }
	virtual bool CheckType(CharacterType type);
	~CharacterCard();
private:
	string description;
};

