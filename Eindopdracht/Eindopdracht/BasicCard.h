#pragma once
#include "CharacterType.h"
#include <string>
class BasicCard
{
public:
	BasicCard(std::string name, CharacterType type = CharacterType::NONE);
	virtual ~BasicCard() = 0;

	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }
	
private:
	std::string name;
	CharacterType type;
};

