#pragma once
#include "CharacterType.h"
#include <string>
#include <istream>
#include "Socket.h"

using namespace std;
class BasicCard
{
public:
	BasicCard(std::string name, CharacterType type = CharacterType::NONE);
	virtual ~BasicCard() = 0;

	string get_name() const { return name; }
	void set_name(const string& new_name) { name = new_name; }
	virtual string print() const = 0;
private:
	string name;
	CharacterType type;
};

