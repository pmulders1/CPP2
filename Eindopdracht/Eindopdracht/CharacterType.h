#pragma once
enum CharacterType { NONE = 0, ASSASSIN = 1, THIEF = 2, MAGICIAN = 3, KING = 4, BISHOP = 5, MERCHANT = 6, ARCHITECT = 7, WARLORD = 8};

inline const char* ToString(CharacterType v)
{
	switch (v)
	{
	case ASSASSIN:   return "Assasin";
	case THIEF:   return "Thief";
	case MAGICIAN: return "Magician";
	case KING:   return "King";
	case BISHOP:   return "Bishop";
	case MERCHANT: return "Merchant";
	case ARCHITECT:   return "Architect";
	case WARLORD:   return "Warlord";
	default:      return "Special";
	}
}