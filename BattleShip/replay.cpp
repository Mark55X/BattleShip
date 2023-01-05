//#include <chrono>
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <thread> 
//
//#include "game_manager.h"
//
//using std::string;
//using battle_ships::GameManager;
//using battle_ships::NavalUnitType;
//using battle_ships::PlayerNumber;
//using battle_ships::GameResponse;
//using std::cout;
//using std::endl;
//
//// Funzione ManageVideoReplay
//// Gestisce il replay su schermo dato il nome del file di log
//void ManageVideoReplay(string name_log_file);
//
//// Funzione ManageFileReplay
//// Gestisce il replay su file dato il nome del file di log e il file di output
//void ManageFileReplay(string name_log_file, string name_file_output);
//
//// Funzione GetNavalUnitTypeDescription 
//// Ritorna la descrizione dell'unità navale dato il type
//string GetNavalUnitTypeDescription(NavalUnitType type);
//
//// Replay
//// Gestisce il replay di una partita di Battaglia Navale
//// Per l'esecuzione del programma sono necessari i seguenti parametri:
//// -v nome-file-log.txt							Per stampare a video il replay
//// -f nome-file-log.txt  nome-file-output.txt   Per stampare su nome-file-output.txt il replay
//int main(int argc, char** argv)
//{
//	string param = argv[1];
//	if (param == "-v" && argc == 3) {
//		ManageVideoReplay(argv[2]);
//	}
//	else if (param == "-f" && argc == 4) {
//		cout << "Esecuzione del replay su file (Sorgente: "<< argv[2] << " Destinazione: "<< argv[3] << "  )" << endl;
//		cout << "Attendere..." << endl;
//		ManageFileReplay(argv[2], argv[3]);
//		cout << "Replay correttamente salvato su file " << argv[3] << endl;
//	}
//	else {
//		std::cerr << "Necessario un parametro: \n -v [nome_file_log] per stampare a video il replay \n"
//					" -f[nome_file_log][nome_file_output_replay] per scrivere su file il replay del file di log indicato";
//		exit(-1);
//	}
//}
//
//void ManageVideoReplay(string name_log_file)
//{
//	try {
//		std::ifstream log_file(name_log_file);
//		bool start_game = false;
//		bool find_winner = false;
//
//		if (log_file.is_open()) {
//			string log_line;
//			GameManager game;
//			
//			cout << "------------INIZIO REPLAY-------------" << endl;
//			cout << "****** DISPOSIZIONI UNITA' NAVALI ******" << endl;
//			
//			while (log_file.good()) {
//				std::getline(log_file, log_line);
//
//				// Formato: ADD-C|Player1:A1 B2 
//				// 		    EXEC|Player1:A1 B2
//				int dash_index = log_line.find("|");
//				int colon_index = log_line.find(":");
//
//				string mode = log_line.substr(0, dash_index);
//				string player = log_line.substr(dash_index + 1, 7);
//				string coordinates = log_line.substr(colon_index + 1);
//				PlayerNumber player_number = (player[6] == '1') ?
//					PlayerNumber::PlayerOne : PlayerNumber::PlayerTwo;
//
//				if (mode.find("ADD") != std::string::npos) {
//					NavalUnitType type = static_cast<NavalUnitType>(mode[4]);
//					string naval_type = GetNavalUnitTypeDescription(type);
//					cout << "******" << player << " aggiunge " << naval_type
//						<< " con poppa e prua: " << coordinates << endl;
//					game.AddNavalUnit(coordinates, type, player_number);
//				}
//				else { // Esecuzione comando
//
//					if (!start_game) {
//						cout << endl << "****** IL GIOCO HA INIZIO ******" << endl << endl;
//						start_game = true;
//					}
//
//					GameResponse response = game.ExecCommand(coordinates, player_number);
//					response = game.ExecCommand("XX XX", player_number);
//					cout << response.content() << endl;
//
//					if (game.IsWinner(player_number)) {
//						cout << "****** VINCITORE: " + player + "******" << endl;
//						find_winner = true;
//						break;
//					}
//				}
//
//				std::this_thread::sleep_for(std::chrono::milliseconds(800));
//			}
//
//			if (!find_winner) {
//				cout << "La partita è stata terminata prima del termine oppure è nulla" << endl;
//			}
//			cout << "------------FINE REPLAY-------------" << endl;
//
//		}else {
//			std::cerr << "Errore: Non e' stato possibile aprire il file sorgente" << name_log_file << std::endl;
//		}
//
//	}
//	catch (std::exception ex) {
//		std::cerr << "Errore nella riproduzione a video del replay, errore: " << ex.what() << std::endl;
//	}
//}
//
//void ManageFileReplay(string name_log_file, string name_file_output)
//{
//	try {
//		std::ifstream log_file(name_log_file);
//		std::ofstream output_file(name_file_output);
//
//		if (log_file.is_open()) {
//			string log_line;
//			GameManager game;
//			bool start_game = false;
//			bool find_winner = false;
//
//			if (output_file.good()) {
//				output_file << "------------INIZIO REPLAY-------------" << endl;
//				output_file << "****** DISPOSIZIONI UNITA' NAVALI ******" << endl;
//			}
//			
//			while (log_file.good()) {
//
//				std::getline(log_file, log_line);
//
//				int dash_index = log_line.find("|");
//				int colon_index = log_line.find(":");
//
//				string mode = log_line.substr(0, dash_index);
//				string player = log_line.substr(dash_index + 1, 7);
//				string coordinates = log_line.substr(colon_index + 1);
//				PlayerNumber player_number = (player[6] == '1') ?
//					PlayerNumber::PlayerOne : PlayerNumber::PlayerTwo;
//
//				if (mode.find("ADD") != std::string::npos) {
//					NavalUnitType type = static_cast<NavalUnitType>(mode[4]);
//					string naval_type = GetNavalUnitTypeDescription(type);
//					output_file << "******" << player << " aggiunge " << naval_type 
//								<< " con poppa e prua: " << coordinates << endl;
//					game.AddNavalUnit(coordinates, type, player_number);
//				}
//				else { // Esecuzione comando
//
//					if (!start_game) {
//						output_file << endl << "****** IL GIOCO HA INIZIO ******" << endl << endl;
//						start_game = true;
//					}
//
//					output_file << endl << "****** Turno " << player << "******" << endl;
//					if (output_file.good()) {
//						GameResponse response = game.ExecCommand(coordinates, player_number);
//						output_file << response.content() << endl << endl;
//						response = game.ExecCommand("XX XX", player_number);
//
//						output_file << response.content() << "\n";
//						output_file.flush();
//					}
//
//					if (game.IsWinner(player_number)) {
//						output_file << "****** VINCITORE: " + player + "******" << endl;
//						find_winner = true;
//						break;
//					}
//				}
//
//				if (!find_winner) {
//					output_file << "La partita è stata terminata prima del termine oppure è nulla" << endl;
//				}
//				output_file << "------------FINE REPLAY-------------" << endl;
//			}
//		}
//		else {
//			std::cerr << "Errore: Non e' stato possibile aprire il file sorgente" << name_log_file << std::endl;
//		}
//
//		output_file.close();
//		log_file.close();
//	}
//	catch (std::exception ex) {
//		std::cerr << "Errore nella riproduzione a video del replay, errore: " << ex.what() << std::endl;
//	}
//}
//
//string GetNavalUnitTypeDescription(NavalUnitType type) {
//	switch (type) {
//	case NavalUnitType::BattleShip:
//		return "CORAZZATA";
//	case NavalUnitType::Submarine:
//		return "SOTTOMARINO";
//	case NavalUnitType::SupportShip:
//		return "NAVE DI SUPPORTO";
//	}
//}
