//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

/*
Vragen:
1. Exception handling waar?
2. Shuffle is niet random - Voor bart
3. Laden van een game bevat alleen nog maar een lijst van ingelade spelers. (nieuwe spelers moeten oud profiel kiezen).
4. Saven van een game wordt nu aan het einde van een spelers beurt gedaan. (niet tijdens character selection)

TODO:
1. Attach/Detach bij het laden van game (playerfield)
2. Laden van een game bevat alleen nog maar een lijst van ingelade spelers. (nieuwe spelers moeten oud profiel kiezen).
3. Kaart wordt wel toegewezen aan een speler tijdens het laden maar er worden geen gegevens van mee genomen.
4. Ontabledeck wordt nog niet mee genomen in de save/load.
5. Refactoren MagicianCard.cpp eventueel ook anderen.

VRAGEN:
*/

#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
using namespace std;

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "Player.hpp"
#include "Game.h"

namespace machiavelli {
	const int tcp_port{ 1080 };
	const string prompt{ "machiavelli> " };
}

static Sync_queue<ClientCommand> queue;
static shared_ptr<Game> game;

void consume_command() // runs in its own thread
{
	try {
		while (true) {
			ClientCommand command{ queue.get() }; // will block here unless there are still command objects in the queue
			shared_ptr<Socket> client{ command.get_client() };
			shared_ptr<Player> player{ command.get_player() };
			try {
				player->set_Client(client);
				game->HandleCommand(player, command.get_cmd());
				//*client << player->get_name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << machiavelli::prompt;
			}
			catch (const exception& ex) {
				cerr << "*** exception in consumer thread for player " << player->get_name() << ": " << ex.what() << '\n';
				client->write(ex.what());
				if (client->is_open()) {
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
			}
			catch (...) {
				cerr << "*** exception in consumer thread for player " << player->get_name() << '\n';
				if (client->is_open()) {
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
			}
		}
	}
	catch (...) {
		cerr << "consume_command crashed\n";
	}
}

void handle_client(shared_ptr<Socket> client) // this function runs in a separate thread
{
	try {
		client->write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
		client->write("What's your name?\r\n");
		client->write(machiavelli::prompt);
		string name{ client->readline() };
		shared_ptr<Player> player{ new Player{ name } };
		if (!game->playing) {
			*client << "Welcome, " << name << ", have fun playing our game!\r\n" << machiavelli::prompt;
		}
		else {
			*client << "Sorry, " << name << " a game is already running. please try again later!\r\n" << machiavelli::prompt;
			client->close();
			return;
		}

		bool disableClient = false;
		while (!disableClient) { // game loop
			try {
				// read first line of request
				string cmd;
				if (game->players.size() > 1 && game->players[0] == player && game->playing) {
					//client->write("You are the party leader\r\n");
					disableClient = true;
				}
				else {
					cmd = client->readline();
				}

				if (game->players.size() > 0 && game->players[0] != player && !game->playing && cmd == "join") {
					//client->write("You have joined the game. wait for the party leader to start\r\n");
					disableClient = true;
				}
				cerr << '[' << client->get_dotted_ip() << " (" << client->get_socket() << ") " << player->get_name() << "] " << cmd << "\r\n";

				if (cmd == "quit") {
					client->write("Bye!\r\n");
					break; // out of game loop, will end this thread and close connection
				}

				ClientCommand command{ cmd, client, player };
				queue.put(command);

			}
			catch (const exception& ex) {
				*client << "ERROR: " << ex.what() << "\r\n";
			}
			catch (...) {
				client->write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
			}
		}
		//client->close();
	}
	catch (...) {
		cerr << "handle_client crashed\n";
	}
}

int main(int argc, const char * argv[])
{
	game = make_shared<Game>();
	// start command consumer thread
	thread consumer{ consume_command };

	// create a server socket
	ServerSocket server{ machiavelli::tcp_port };

	while (true) {
		try {
			while (true) {
				// wait for connection from client; will create new socket
				cerr << "server listening" << '\n';
				shared_ptr<Socket> client{ server.accept() };

				// communicate with client over new socket in separate thread
				thread handler{ handle_client, move(client) };

				handler.detach(); // detaching is usually ugly, but in this case the right thing to do
			}
		}
		catch (const exception& ex) {
			cerr << ex.what() << ", resuming..." << '\n';
		}
		catch (...) {
			cerr << "problems, problems, but: keep calm and carry on!\n";
		}
	}
	consumer.join();
	return 0;
}

