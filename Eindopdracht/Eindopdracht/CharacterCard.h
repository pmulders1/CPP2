#pragma once
#include "BasicCard.h"

using namespace std;
class CharacterCard : public BasicCard
{
public:
	CharacterCard(string name, CharacterType type = CharacterType::NONE);

	virtual void execute() = 0;

	string get_Discription() { return this->discription; }
	void set_Discription(string val) { this->discription = val; }

	virtual ~CharacterCard() = 0;
private:
	string discription;
};

