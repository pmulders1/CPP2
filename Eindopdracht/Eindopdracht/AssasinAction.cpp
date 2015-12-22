#include "AssasinAction.h"



AssasinAction::AssasinAction()
{
}

void AssasinAction::Execute(Game game){
	auto client = game.players[game.currentPlayer].second;
	*client << "\u001B[2J";
	*client << "Choose a character to chop his head off.\r\n\r\n";

	*client << "1. Kill the Thief.\r\n";
	*client << "2. Kill the Magician.\r\n";
	*client << "3. Kill the King.\r\n";
	*client << "4. Kill the Bishop.\r\n";
	*client << "5. Kill the Merchant.\r\n";
	*client << "6. Kill the Architect.\r\n";
	*client << "7. Kill the Warlord.\r\n\r\n";

	// Check voor geldige invoer
	bool valid = false;
	while (!valid) {
		string temp{ client->readline() };

		try {
			int choice = atoi(temp.c_str());
			if (choice < 1 || choice > 7) {
				throw exception();
			}

			game.KillPlayer((CharacterType)(choice + 1));

			valid = true;
		}
		catch (exception e) {
			*client << "Invalid input. Select a option by number!\r\n";
			valid = false;
		}
	}
}

AssasinAction::~AssasinAction()
{
}
