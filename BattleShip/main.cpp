// Main
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#include <iostream>

#include "game_manager.h"
#include "computer_player.h"

using std::cout;
using std::endl;
using std::cin;

using battle_ships::GameManager;
using battle_ships::PlayerNumber;
using battle_ships::NavalUnitType;
using battle_ships::ComputerPlayer;
using battle_ships::GameResponse;
using battle_ships::Coordinates;

// Funzione principale per l'esecuzione di una partita Player vs Computer
void RunPlayerVsComputerGame();

// Funzione principale per l'esecuzione di una partita Computer vs Computer
void RunComputerVsComputerGame();


// -- Funzioni di supporto -- 

// Funzione InsertPlayerNavalUnit
// Gestisce l'inserimento delle unità navali da parte dell'utente
void InsertPlayerNavalUnit(GameManager& game, NavalUnitType type);

// Funzione InsertComputerNavalUnit
// Gestisce l'inserimento delle unità navali da parte del computer
void InsertComputerNavalUnit(GameManager& game, 
							 ComputerPlayer& computer_player, 
							 const NavalUnitType type, 
							 PlayerNumber player_number);

// Funzione ManageComputerShift
// Gestisce il turno e l'esecuzione del comando da parte del computer
void ManageComputerShift(ComputerPlayer& bot_player,
						 GameManager& game,
						 PlayerNumber player_number);

// Funzione ManagePlayerShift
// Gestisce il turno e l'esecuzione del comando da parte del giocatore
void ManagePlayerShift(GameManager& game);

// Funzione GetStartPlayer
// Reestituisce random un booleano per la scelta del giocatore che deve
// iniziare la partita
bool GetStartPlayer();

// Funzione main
int main(int argc, char** argv)
{
	// Controllo dei parametri in ingresso : 
	// -pc per partita GIOCATORE vs COMPUTER
	// -cc per partita COMPUTER vs COMPUTER	
	if (argc != 2)
	{
		std::cerr << "Parametri non corretti. Il gioco si esegue con i seguenti comandi:"<< endl;
		std::cerr << "battaglia_navale pc  : Partita PLAYER vs COMPUTER" << endl;
		std::cerr << "battaglia_navale cc  : Partita COMPUTER vs COMPUTER" << endl << endl;
		exit(-1);
	}

	string param = argv[1];
	if (param != "pc" &&
		param != "cc")
	{
		std::cerr << "Parametro inserito non corretto. Il gioco si esegue con i seguenti comandi:" << endl;
		std::cerr << "battaglia_navale pc  : Partita PLAYER vs COMPUTER" << endl;
		std::cerr << "battaglia_navale cc  : Partita COMPUTER vs COMPUTER" << endl << endl;
		exit(-1);
	}
	
	bool is_pc_game = (param == "pc");
	string target_title = is_pc_game == true ? "Player" : "Computer";
	cout << "-------------------------------" << endl;
	cout << "        BATTAGLIA NAVALE       " << endl;
	cout << "       "<< target_title <<" vs Computer      " << endl;
	cout << " Albertin, Selvestrel, Stefani " << endl;
	cout << "-------------------------------" << endl << endl << endl;

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

	if (is_pc_game) {
		RunPlayerVsComputerGame();
	}
	else {
		RunComputerVsComputerGame();
	}
}

void ManageComputerShift(ComputerPlayer& bot_player, GameManager& game,PlayerNumber player_number) {
	bool next_shift = false;

	while (!next_shift) {
		string bot_command = bot_player.ActionCoordinatesGenerator();
		GameResponse response = game.ExecCommand(bot_command, player_number);

		int whitespace_index = bot_command.find(" ");
		Coordinates old_coordinates(bot_command.substr(0, whitespace_index));
		Coordinates new_coordinates(bot_command.substr(whitespace_index + 1, bot_command.length() - 1));

		if (response.performed_action() == GameResponse::kMoveExploreAction ||
			response.performed_action() == GameResponse::kMoveRepairAction) {
			bot_player.SetCoordinates(old_coordinates, new_coordinates);
		}
		else if (response.error_type() == GameResponse::kIncorrectOrigin) {
			bot_player.RemoveCoordinates(old_coordinates);
			if (bot_player.GetCoordinatesNumber() == 0) {
				break;
			}
		}

		next_shift = response.next_shift();
	}
}

void ManagePlayerShift(GameManager& game) 
{
	bool next_shift = false;
	string command = "";
	cout << "E' il tuo turno!" << endl;
	while (!next_shift) {
		cout << "Player >> ";
		std::getline(std::cin, command);
		GameResponse response = game.ExecCommand(command, PlayerNumber::PlayerOne);
		cout << response.content() << endl;
		next_shift = response.next_shift();
	}
	cout << "Hai terminato il tuo turno." << endl;
}

bool GetStartPlayer()
{
	std::uniform_int_distribution<> distribution(0, 1);
	std::default_random_engine gen(std::chrono::system_clock::now().time_since_epoch().count());
	return distribution(gen);
}

void RunPlayerVsComputerGame()
{
	GameManager game;

	InsertPlayerNavalUnit(game, NavalUnitType::BattleShip);
	InsertPlayerNavalUnit(game, NavalUnitType::SupportShip);
	InsertPlayerNavalUnit(game, NavalUnitType::Submarine);

	ComputerPlayer bot_player;
	InsertComputerNavalUnit(game, bot_player, NavalUnitType::BattleShip, PlayerNumber::PlayerTwo);
	InsertComputerNavalUnit(game, bot_player, NavalUnitType::SupportShip, PlayerNumber::PlayerTwo);
	InsertComputerNavalUnit(game, bot_player, NavalUnitType::Submarine, PlayerNumber::PlayerTwo);

	cout << endl << "*** Chi inizia la partita? Lancio della moneta..." << endl;

	bool first_player_one = GetStartPlayer();

	if (first_player_one)
		cout << "*** Hai vinto il lancio della moneta, e' tuo il primo turno!" << endl << endl;
	else
		cout << "*** Hai perso il lancio della moneta, il primo turno e' per l'avversario!" << endl << endl;

	bool is_player_one_winner = false;
	bool is_player_two_winner = false;
	string command = "";
	bool next_shift = false;

	int max_shifts = game.kMaxShiftPC;
	int shifts = 0;
	while ((!is_player_one_winner && !is_player_two_winner) || shifts >= max_shifts) {

		if (first_player_one) {

			ManagePlayerShift(game);

			is_player_one_winner = game.IsWinner(PlayerNumber::PlayerOne);
			if (is_player_one_winner || is_player_two_winner)
				break;

			ManageComputerShift(bot_player, game, PlayerNumber::PlayerTwo);
			cout << "Il computer ha terminato il suo turno." << endl << endl;

			is_player_two_winner = game.IsWinner(PlayerNumber::PlayerTwo);
		}
		else {
			ManageComputerShift(bot_player, game, PlayerNumber::PlayerTwo);
			cout << "Il computer ha terminato il suo turno." << endl << endl;

			is_player_two_winner = game.IsWinner(PlayerNumber::PlayerTwo);
			if (is_player_one_winner || is_player_two_winner)
				break;

			ManagePlayerShift(game);
			is_player_two_winner = game.IsWinner(PlayerNumber::PlayerOne);
		}
	}

	if (shifts >= max_shifts)
		cout << "*** PARTITA TERMINATA PER NUMERO MASSIMO DI TURNI RAGGIUNTO (" << max_shifts << ")" << endl << endl;
	else if (is_player_one_winner)
		cout << "*** GIOCO TERMINATO! COMPLIMENTI HAI VINTO!" << endl << endl;
	else
		cout << "*** GIOCO TERMINATO! HAI PERSO!" << endl << endl;

	cout << "Puoi rivedere la partita con il replay. File di Log creato: " << game.GetLogFileName() << endl;
}

void RunComputerVsComputerGame()
{
	GameManager game;
	ComputerPlayer bot_player_one;
	ComputerPlayer bot_player_two;

	InsertComputerNavalUnit(game, bot_player_one, NavalUnitType::BattleShip, PlayerNumber::PlayerOne);
	InsertComputerNavalUnit(game, bot_player_one, NavalUnitType::SupportShip, PlayerNumber::PlayerOne);
	InsertComputerNavalUnit(game, bot_player_one, NavalUnitType::Submarine, PlayerNumber::PlayerOne);

	InsertComputerNavalUnit(game, bot_player_two, NavalUnitType::BattleShip, PlayerNumber::PlayerTwo);
	InsertComputerNavalUnit(game, bot_player_two, NavalUnitType::SupportShip, PlayerNumber::PlayerTwo);
	InsertComputerNavalUnit(game, bot_player_two, NavalUnitType::Submarine, PlayerNumber::PlayerTwo);

	cout << endl << "*** Chi inizia la partita? Lancio della moneta..." << endl;

	bool first_player_one = GetStartPlayer();
	PlayerNumber firstPlayer = first_player_one ? PlayerNumber::PlayerOne : PlayerNumber::PlayerTwo;
	PlayerNumber secondPlayer = first_player_one ? PlayerNumber::PlayerTwo : PlayerNumber::PlayerOne;

	ComputerPlayer& first_bot = firstPlayer == PlayerNumber::PlayerOne ? bot_player_one : bot_player_two;
	ComputerPlayer& second_bot = secondPlayer == PlayerNumber::PlayerOne ? bot_player_one : bot_player_two;

	cout << "*** Inizia il giocatore " << firstPlayer << "!!" << endl << endl;

	cout << "*** IL GIOCO E' INIZIATO ***" << endl;
	cout << "*** E' in corso la partita tra i due bot..." << endl;
	string command = "";
	bool is_first_player_winner = false;
	bool is_second_player_winner = false;

	int max_shifts = game.kMaxShiftsCC;
	int shifts = 0;
	while ((!is_first_player_winner && !is_second_player_winner) && shifts < max_shifts)
	{
		ManageComputerShift(first_bot, game, firstPlayer);

		is_first_player_winner = game.IsWinner(firstPlayer);
		is_second_player_winner = game.IsWinner(secondPlayer);
		if (is_first_player_winner || is_second_player_winner)
			break;
		shifts++;

		ManageComputerShift(second_bot, game, secondPlayer);
		//is_first_player_winner = game.IsWinner(firstPlayer);
		is_second_player_winner = game.IsWinner(secondPlayer);
		shifts++;
	}

	if (shifts >= max_shifts)
		cout << "*** PARTITA TERMINATA PER NUMERO MASSIMO DI TURNI RAGGIUNTO (" << max_shifts << ")" << endl << endl;
	else if (is_first_player_winner)
		cout << "*** GIOCO TERMINATO! VINCE IL GIOCATORE " << firstPlayer << endl << endl;
	else
		cout << "*** GIOCO TERMINATO! VINCE IL GIOCATORE " << secondPlayer << endl << endl;

	cout << "Puoi rivedere la partita con il replay. File di Log creato: " << game.GetLogFileName() << endl;
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