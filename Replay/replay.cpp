#include <iostream>
#include <string>
#include <fstream>
#include "../BattleShip/game_manager.h"

using std::string;
using battle_ships::GameManager;
using battle_ships::NavalUnitType;
using battle_ships::PlayerNumber;
using battle_ships::GameResponse;
using std::cout;
using std::endl;

void ManageVideoReplay(string name_log_file);
void ManageFileReplay(string name_log_file, string name_file_output);

int main(int argc, char** argv)
{
	// Controllo dei parametri in ingresso 
	if (argc != 3 &&  argc != 4)
	{
		std::cerr << "Necessario un parametro: \n -v [nome_file_log] per stampare a video il replay \n -f [nome_file_log] [nome_file_output_replay] per scrivere su file il replay del file di log indicato";
		exit(-1);
	}

	string param = argv[1];
	if (param == "-v" && argc == 3) {
		ManageVideoReplay(argv[2]);
	}
	else if (param == "-f" && argc == 4) {
		ManageFileReplay(argv[2], argv[3]);
	}
	else {
		std::cerr << "Necessario un parametro: \n -v [nome_file_log] per stampare a video il replay \n -f [nome_file_log] [nome_file_output_replay] per scrivere su file il replay del file di log indicato";
		exit(-1);
	}
}

void ManageVideoReplay(string name_log_file)
{
	try {
		std::ifstream log_file(name_log_file); 

		if (log_file.is_open()) {
			string log_line;
			GameManager game;

			while (log_file.good()) {

				std::getline(log_file, log_line);
				cout << log_line << ": " << log_file.tellg() << '\n';

				// Prima ci sono gli ADD e poi gli EXEC
				// ADD-C|Player1:A1 B2
				// EXEC|Player1:A1 B2

				//int dash_index = log_line.find("|");
				//int colon_index = log_line.find(":");

				//string mode = log_line.substr(0, dash_index);
				//string player = log_line.substr(dash_index + 1, colon_index);
				//string coordinates = log_line.substr(colon_index);
				//PlayerNumber player_number = player.find("1") ? 
				//	PlayerNumber::PlayerOne : PlayerNumber::PlayerTwo;

				//if (mode.find("ADD") != std::string::npos) {
				//	game.AddNavalUnit(coordinates, static_cast<NavalUnitType>(mode[4]), player_number);
				//}
				//else { // Esecuzione comando

				//	GameResponse response = game.ExecCommand(coordinates, player_number);
				//	response = game.ExecCommand("XX XX", player_number);
				//	cout << response.content() << endl;

				//	if (game.IsWinner(player_number)) {
				//		cout << "VINCITORE: " << player << endl;
				//		break;
				//	}
				//}
			}
		}

	}
	catch (std::exception ex) {
		std::cerr << "Errore nella riproduzione a video del replay, errore: " << ex.what() << std::endl;
	}
}

void ManageFileReplay(string name_log_file, string name_file_output)
{

}
