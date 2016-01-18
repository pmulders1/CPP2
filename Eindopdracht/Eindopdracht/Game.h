#pragma once
#include <memory>
#include "Socket.h"
#include "Player.hpp"
#include <algorithm>
#include <cstdlib>
#include <string> 
#include <ctime>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "Deck.h"
#include "BuildingCard.h"
#include "AssasinCard.h"
#include "ThiefCard.h"
#include "MagicianCard.h"
#include "KingCard.h"
#include "BishopCard.h"
#include "MerchantCard.h"
#include "ArchitectCard.h"
#include "WarlordCard.h"
#include "CourtOfMiraclesCard.h"
#include "Dragonsgate.h"
#include "Dungeon.h"
#include "Graveyard.h"
#include "Labatorium.h"
#include "Library.h"
#include "MagiciansSchool.h"
#include "University.h"
#include "Workshop.h"
#include "Obversatorium.h"
#include "ISubject.h"
#include "GameStatus.h"

using namespace std;

class Game : public ISubject
{
public:
	Game();

	// Functions map
	typedef void(*FunctionsMap)(shared_ptr<Player>, Game& game);
	typedef map<string, FunctionsMap> functions_map;

	functions_map m;
	void call_script(const std::string& pFunction, shared_ptr<Player> player)
	{
		functions_map::const_iterator iter = m.find(pFunction);
		if (iter == m.end())
		{
			player->write_Client("Function not found! Please try again!\r\n");
		}
		else {
			(*iter->second)(player, *this);
		}
	}

	void HandleCommand(shared_ptr<Player> player, string command);
	void PlayTurn(string type, Game& game);

	void CharacterSelection2P(shared_ptr<Player> player, Game& game);
	void CharacterSelection3P(shared_ptr<Player> player, Game& game);
	void CharacterReset();
	void GameReset();
	void FillCharactersDeck();
	void FillBuildingsDeck();
	void ShowBoard();
	void DrawCards();
	void CalculateWinner();
	shared_ptr<BasicCard> DrawSingleCard();
	bool ConstructBuildings();

	vector<shared_ptr<Player>> players;
	map<CharacterType, shared_ptr<CharacterCard>> allCharacters;
	Deck buildingsDeck;
	Deck charactersDeck;
	Deck onTableDeck;

	// Observer pattren
	shared_ptr<BuildingCard> tempCard;
	vector<shared_ptr<BuildingCard>> notifyCards;
	
	// Wegschrijven van GameStatus
	void WriteGameStatus();

	void ClaimBuildingCards(istream& strm, shared_ptr<Player> player);
	void ClaimCharacterCards(istream& strm, shared_ptr<Player> player);
	void ClaimPlayerFieldCards(istream& strm, shared_ptr<Player> player);

	friend ostream& operator<<(ostream& strm, const Game& game) {
		strm << "GameIsPlaying: " << game.playing << endl;

		strm << "firstpart: " << game.firstpart << endl;

		strm << "secondpart: " << game.secondpart << endl;

		strm << "specialpart: " << game.specialpart << endl;

		strm << "CurrentPlayer: " << game.currentPlayer.get()->get_name() << endl;

		strm << "GameStatus: " << ToStringGameStatus(game.gameStatus) << endl;

		strm << "PlayerCount: " << game.players.size() << endl;

		for (size_t i = 0; i < game.players.size(); i++)
		{
			strm << "BeginPlayer:" << endl << *game.players[i] << ":EndPlayer" << endl;
		}

		return strm;
	}
	friend istream& operator>>(istream& strm, Game& game) {
		bool playing;
		bool firstpart;
		bool secondpart;
		bool specialpart;
		string status;
		string currentPlayer;
		string playerCount;

		string omschrijving;

		// Status van plaing/current player ophalen en het aantal spelers van de savegame
		strm >> omschrijving >> playing >> omschrijving >> firstpart >> omschrijving >> secondpart >> omschrijving >> specialpart >> omschrijving >> currentPlayer >> omschrijving >> status >> omschrijving >> playerCount;

		if (stoi(playerCount) != game.players.size()) {
			for (size_t i = 0; i < game.players.size(); i++)
			{
				game.players[i]->write_Client("Not the right amount of players to load a game!");
			}
			return strm;
		}
		
		// Hoe weten we zeker dat de spelers die de game loaden dezelfde spelers zijn?.
		// Hoe wordt deze volgorde bepaald?
		game.FillBuildingsDeck();
		game.FillCharactersDeck();
		
		for (size_t i = 0; i < stoi(playerCount); i++)
		{
			strm >> *game.players[i];

			game.ClaimBuildingCards(strm, game.players[i]);
			game.ClaimCharacterCards(strm, game.players[i]);
			game.ClaimPlayerFieldCards(strm, game.players[i]);
			
			if (game.players[i]->get_name() == currentPlayer) {
				game.currentPlayer = game.players[i];
			}

			strm >> omschrijving;
		}

		game.playing = playing;
		game.firstpart = firstpart;
		game.secondpart = secondpart;
		game.specialpart = specialpart;
		game.gameStatus = ToEnumGameStatus(status);
		return strm;
	}

	GameStatus gameStatus = GameStatus::PLAYING;

	shared_ptr<Player> currentPlayer;

	bool playing = false;
	bool firstpart = true;
	bool secondpart = true;
	bool specialpart = true;
	~Game();
};

