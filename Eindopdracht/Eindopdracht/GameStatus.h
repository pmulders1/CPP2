#pragma once
#include <string>
enum GameStatus { PLAYING = 0, CHARACTERSELECT = 1 };

inline const char* ToStringGameStatus(GameStatus v)
{
	switch (v)
	{
	case PLAYING:   return "Playing";
	case CHARACTERSELECT:   return "CharacterSelect";
	default:      return "Playing";
	}
}

inline const GameStatus ToEnumGameStatus(const std::string v)
{
	if (v == "Playing") return PLAYING;
	if (v == "CharacterSelect") return CHARACTERSELECT;
	else return PLAYING;
}