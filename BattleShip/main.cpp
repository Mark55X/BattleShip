// Main
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#include "game_manager.h";

#include <iostream>
#include "grid.h"
#include "enums.h"

#include <chrono>
#include <random>
#include <vector>
#include "computer_player.h"
#include "game_response.h"
#include "coordinates.h"
#include <thread>       

using std::cout;
using std::endl;
using std::cin;

using battle_ships::GameManager;
using battle_ships::PlayerNumber;
using battle_ships::NavalUnitType;
using battle_ships::ComputerPlayer;
using battle_ships::GameResponse;
using battle_ships::Coordinates;

void InsertPlayerNavalUnit(GameManager& game, NavalUnitType type);
void InsertComputerNavalUnit(GameManager& game, 
							 ComputerPlayer& computer_player, 
							 const NavalUnitType type, 
							 PlayerNumber player_number);

int main(int argc, char** argv)
{
	// Controllo dei parametri in ingresso : 
	// -pc per partita GIOCATORE vs COMPUTER
	// -cc per partita COMPUTER vs COMPUTER	
	if (argc != 2)
	{
		std::cerr << "Necessario un parametro: \n -pc per Partita GIOCATORE vs COMPUTER \n -cc per partita COMPUTER vs COMPUTER";
		exit(-1);
	}

	string param = argv[1];
	if (param != "-pc" &&
		param != "-cc")
	{
		std::cerr << "Necessario un parametro: \n -pc per Partita GIOCATORE vs COMPUTER \n -cc per partita COMPUTER vs COMPUTER";
		exit(-1);
	}
	
	bool is_pc_game = (param == "-pc");
	string target_title = is_pc_game == true ? "Player" : "Computer";
	cout << "-------------------------------" << endl;
	cout << "        BATTAGLIA NAVALE       " << endl;
	cout << "       "<< target_title <<" vs Computer      " << endl;
	cout << " Albertin, Selvestrel, Stefani " << endl;
	cout << "-------------------------------" << endl << endl << endl;

	GameManager game;

	// output nel caso di -pc
	cout << "*** REGOLE DEL GIOCO ***" << endl;
	cout << "1. Vengono richieste le coordinate di poppa e prua di ogni unita' navali (Esempio: A1 B6)" << endl;
	cout << "2. I comandi possibili sono: " << endl;
	cout << "   a) A1 B1: Con A1 Coordinata di origine e B1 coordinata target " << endl;
	cout << "      L'azione dipende dalla coordinata di origine  " << endl;
	cout << "   b) XX XX: Display della propria griglia di attacco e difesa " << endl;
	cout << "   c) AA AA: Tutti gli avvistamenti del sottomarino ('Y') vengono cancellati" << endl;
	cout << "   d) BB BB: Tutti i punti colpiti ('X') vengono cancellati" << endl;
	cout << "   d) CC CC: Tutti i punti mancati ('O') vengono cancellati" << endl << endl << endl;

	cout << "*** POSIZIONAMENTO DELLE UNITA' NAVALI ***" << endl;
	

	// ---------- Solo per test
	
	/*game.AddNavalUnit("B6 B10", NavalUnitType::BattleShip, PlayerNumber::PlayerOne);
	game.AddNavalUnit("F8 F12", NavalUnitType::BattleShip, PlayerNumber::PlayerOne);
	game.AddNavalUnit("D2 H2", NavalUnitType::BattleShip, PlayerNumber::PlayerOne);

	game.AddNavalUnit("A2 A4", NavalUnitType::SupportShip, PlayerNumber::PlayerOne);
	game.AddNavalUnit("D6 D8", NavalUnitType::SupportShip, PlayerNumber::PlayerOne);
	game.AddNavalUnit("A12 C12", NavalUnitType::SupportShip, PlayerNumber::PlayerOne);

	game.AddNavalUnit("L2 L2", NavalUnitType::Submarine, PlayerNumber::PlayerOne);
	game.AddNavalUnit("H11 H11", NavalUnitType::Submarine, PlayerNumber::PlayerOne);*/

	// ------------

	/*
	InsertPlayerNavalUnit(game, NavalUnitType::BattleShip);
	InsertPlayerNavalUnit(game, NavalUnitType::SupportShip);
	InsertPlayerNavalUnit(game, NavalUnitType::Submarine);	
	*/

	ComputerPlayer bot_player_one;
	ComputerPlayer bot_player_two;

	InsertComputerNavalUnit(game, bot_player_one, NavalUnitType::BattleShip, PlayerNumber::PlayerOne);
	InsertComputerNavalUnit(game, bot_player_one, NavalUnitType::SupportShip, PlayerNumber::PlayerOne);
	InsertComputerNavalUnit(game, bot_player_one, NavalUnitType::Submarine, PlayerNumber::PlayerOne);

	InsertComputerNavalUnit(game, bot_player_two, NavalUnitType::BattleShip, PlayerNumber::PlayerTwo);
	InsertComputerNavalUnit(game, bot_player_two, NavalUnitType::SupportShip, PlayerNumber::PlayerTwo);
	InsertComputerNavalUnit(game, bot_player_two, NavalUnitType::Submarine, PlayerNumber::PlayerTwo);

	cout << "*** IL GIOCO E' INIZIATO ***" << endl;
	string command = "";
	bool is_player_one_winner = false;
	bool is_player_two_winner = false;
	bool next_shift = false;

	while (!is_player_one_winner && !is_player_two_winner) {

		/*cout << "E' il tuo turno!" << endl;
		while (!next_shift) {
			std::getline(std::cin, command);
			GameResponse response = game.ExecCommand(command, PlayerNumber::PlayerOne);
			cout << response.content() << endl;
			next_shift = response.next_shift();
		}
		cout << "Hai terminato il tuo turno." << endl;
		next_shift = false;*/
		
		while (!next_shift) {
			string bot_command = bot_player_one.ActionCoordinatesGenerator();
			GameResponse response = game.ExecCommand(bot_command, PlayerNumber::PlayerOne);

			int whitespace_index = bot_command.find(" ");
			Coordinates old_coordinates(bot_command.substr(0, whitespace_index));
			Coordinates new_coordinates(bot_command.substr(whitespace_index + 1, bot_command.length() - 1));

			if (response.performed_action() == GameResponse::kMoveExploreAction ||
				response.performed_action() == GameResponse::kMoveRepairAction) {
				bot_player_one.SetCoordinates(old_coordinates, new_coordinates);
			}
			else if (response.error_type() == GameResponse::kIncorrectOrigin) {
				bot_player_one.RemoveCoordinates(old_coordinates);
				if (bot_player_one.GetCoordinatesNumber() == 0) {
					is_player_two_winner = true;
					break;
				}
			}

			next_shift = response.next_shift();
		}
		next_shift = false;

		is_player_one_winner = game.IsWinner(PlayerNumber::PlayerOne);
		if (is_player_one_winner || is_player_two_winner)
			break;

		while (!next_shift) {
			string bot_command = bot_player_two.ActionCoordinatesGenerator();
			GameResponse response = game.ExecCommand(bot_command, PlayerNumber::PlayerTwo);

			int whitespace_index = bot_command.find(" ");
			Coordinates old_coordinates(bot_command.substr(0, whitespace_index));
			Coordinates new_coordinates(bot_command.substr(whitespace_index + 1, bot_command.length() - 1));

			if (response.performed_action() == GameResponse::kMoveExploreAction ||  
				response.performed_action() == GameResponse::kMoveRepairAction) {
				bot_player_two.SetCoordinates(old_coordinates, new_coordinates);
			}
			else if (response.error_type() == GameResponse::kIncorrectOrigin) {
				bot_player_two.RemoveCoordinates(old_coordinates);
				if (bot_player_two.GetCoordinatesNumber() == 0) {
					is_player_two_winner = true;
					break;
				}
			}

			next_shift = response.next_shift();
		}
		//cout << "Il computer ha terminato il suo turno." << endl << endl;
		next_shift = false;

		is_player_two_winner = game.IsWinner(PlayerNumber::PlayerTwo);

		//std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	
	if (is_player_one_winner)
		cout << "VINCITORE GIOCATORE UNO!";
	else
		cout << "VINCITORE GIOCATORE DUE!";

	/*
		*  Solo per test player2
		std::getline(std::cin, command);
		cout << game.ExecCommand(command, PlayerNumber::PlayerTwo).content() << endl;
		*/
}

void InsertPlayerNavalUnit(GameManager& game, NavalUnitType type)
{
	string coordinates = "";
	string output_text = "";
	int max_number = 0;
	switch (type) {
	case NavalUnitType::BattleShip : 
		output_text = "Quali sono le coordinate per la corazzata ";
		max_number = game.kBattleShipNumber;
		break;
	case NavalUnitType::SupportShip:
		output_text = "Quali sono le coordinate per la nave di supporto ";
		max_number = game.kSupportShipNumber;
		break;
	case NavalUnitType::Submarine:
		output_text = "Quali sono le coordinate per il sottomarino ";
		max_number = game.kSubmarineNumber;
		break;
	}

	for (int i = 1; i <= max_number; i++) {
		cout << output_text << i << " : " << endl;
		bool correct = false;
		while (!correct) {
			std::getline(std::cin, coordinates);
			GameResponse response = game.AddNavalUnit(coordinates, type, PlayerNumber::PlayerOne);
			correct = response.status();
			if (!correct) {
				cout << response.content() << endl;
			}	
		}
	}
}

// in questo caso va passato anche il PlayerNumber perché in caso di partita computer vs computer questa
// funzione va chiamata sia per il PlayerOne che per il PlayerTwo
void InsertComputerNavalUnit(GameManager& game, 
							 ComputerPlayer& computer_player, 
							 const NavalUnitType type, 
							 PlayerNumber player_number)
{
	string coordinates = "";
	int max_number = 0;
	switch (type) {
	case NavalUnitType::BattleShip:
		max_number = game.kBattleShipNumber;
		break;
	case NavalUnitType::SupportShip:
		max_number = game.kSupportShipNumber;
		break;
	case NavalUnitType::Submarine:
		max_number = game.kSubmarineNumber;
		break;
	}

	for (int i = 1; i <= max_number; i++) {
		bool correct = false;
		while (!correct) {
			coordinates = computer_player.InsertCoordinatesGenerator(type);
			GameResponse response = game.AddNavalUnit(coordinates, type, player_number);
			correct = response.status();
			if (correct) {
				computer_player.MemorizeCentreCoordinates(coordinates);
			}
		}
	}
}


