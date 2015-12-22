#pragma once
#include <string>
#include <istream>
#include "Socket.h"
#include "CharacterType.h"
using namespace std;
class BasicCard
{
public:
	BasicCard(std::string name, CharacterType type = CharacterType::NONE);
	virtual void execute() = 0;
	virtual ~BasicCard() = 0;

	string get_name() const { return name; }
	void set_name(const string& new_name) { name = new_name; }

	bool get_visible() const { return visible; }
	void set_visible(const bool& new_visible) { visible = new_visible; }

	CharacterType get_type() const { return type; }

private:
	string name;
	bool visible;
	CharacterType type;
};