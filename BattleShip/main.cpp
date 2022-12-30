// Main
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#include "game_manager.h";

#include <iostream>
#include "grid.h"
#include "enums.h"

#include <chrono>
#include <random>
#include <vector>
#include "computer_player.h"

using std::cout;
using std::endl;
using std::cin;

using battle_ships::GameManager;
using battle_ships::PlayerNumber;
using battle_ships::NavalUnitType;
using battle_ships::ComputerPlayer;

/*
* Pensieri miei abbastanza profondi da scrivere nel readme.TXT
*
* Secondo me è ESSENZIALE dividere il MAIN dal resto del progetto
* tale che si possono creare molti modi per fare il main
* senza che influisca DIRETTAMENTE nella logica del gioco.
*
* Mi spiego meglio: perchè il main dovrebbe fare i controlli di validità dei comandi?
* Per me non deve farli, non è il suo ruolo. Lui sa solo che è un comando, non sa
* nemmeno cosa fa, perché la descrizione di tale esecuzione deve essere descritta dal
* CORE del gioco che mi invierà un oggetto di tipo RESPONSE
*
* Attenzione, parte importante perché il RESPONSE sarà una risponsa GENERICA (non è un template attenzione :) )
* Response{
	StatusExecution : bool  -> Se avvenuto con successo o meno
	Content : string        -> Contenuto (può essere la string aformattata per il comando XX XX
										  o la descrizione tipo 'Eseguito FUOCO su cella nemica A1 ')
	NextShift : bool        -> False se il turno è ancora del giocatore che ha eseguito il comando
  }

  QUESTO PERCHE' giustamente se io avessi i metodi che restituiscono bool cosa capirei?
  Se è false, per quale motivo è false? Coordiante fuori? Entrambe? O solo una? Oppure sono giuste
  ma l'origin riguarda nessun unità navale e per me QUESTO NON FA LO SWITCH DEL TURNO!!

  Ok quindi ha senso usare un oggetto più descrittivo, si ok però perchè non usare le eccezioni?
  Tipo: InvalidCellException con la DESCRIZIONE interna di cosa è sbagliato?

  Se siamo nel caso di Logger/Replay è palese l'uso delle eccezioni: il file non esiste, problemi di scrittura
  ecc,... MA NEL GIOCO?? Forse si, forse no: bloccare l'esecuzione di colpo mi implicherebbe che non serve più
  la Response descritta qui sopra perchè so che se c'è un eccezione TEORICAMENTE devo rifare il turno...
  ma se tipo mi parte un eccezione per il Logger? Quella viene catturata da sé e quindi non influenzerebbe
  l'andamento della partita...dovrebbe bloccare la partita? Come ? Vado a lavarmi, buon Natale a tutti.

  Abbiamo quindi: Eccezioni ->  PRO: Dati che si passano più leggeri (o così si crede)
								CONTRO: Blocco dell'esecuzione improvviso

				  Response ->   PRO: Non c'è interruzione del flusso (forse un pò stile retro?)
								CONTRO: La gran parte delle funzioni resituiscono la response

  Attenzione che... XX XX SUCCESFUL ma non cambia turno..come faccio con eccezioni?
					A1 B2 SUCCESFUL fantastico...nessuna eccezione ma come stampo che è avvenuta l'azione?
	Quello che sto dicendo è che: io ho lo stesso risultato di Response SOLO se avviene l'eccezione. Ma
	io magari vorrei avere il risultato anche quando non accade. OVVERO dare più potere al main,
	fargli capire cosa significano tali comandi... (impossibile capire l'AZIONE in sé)


*/

void InsertPlayerNavalUnit(GameManager& game, NavalUnitType type);

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
	cout << "   c) AA AA: ?? " << endl;
	cout << "   d) BB BB: ?? " << endl;
	cout << "   d) CC CC: ?? " << endl << endl << endl;

	cout << "*** POSIZIONAMENTO DELLE UNITA' NAVALI ***" << endl;
	//InsertPlayerNavalUnit(game, NavalUnitType::BattleShip);
	//InsertPlayerNavalUnit(game, NavalUnitType::SupportShip);
	//InsertPlayerNavalUnit(game, NavalUnitType::Submarine);

	// ---------- Solo per test
	game.AddNavalUnit("A1 A5", NavalUnitType::BattleShip, PlayerNumber::PlayerOne);
	game.AddNavalUnit("D6 H6", NavalUnitType::BattleShip, PlayerNumber::PlayerOne);
	game.AddNavalUnit("D8 D12", NavalUnitType::BattleShip, PlayerNumber::PlayerOne);

	//game.AddNavalUnit("A1 A5", NavalUnitType::BattleShip, PlayerNumber::PlayerTwo);
	//game.AddNavalUnit("E6 I6", NavalUnitType::BattleShip, PlayerNumber::PlayerTwo);
	//game.AddNavalUnit("A8 A12", NavalUnitType::BattleShip, PlayerNumber::PlayerTwo);
	ComputerPlayer p;
	game.AddNavalUnit(p.InsertCoordinatesGenerator(NavalUnitType::BattleShip), NavalUnitType::BattleShip, PlayerNumber::PlayerTwo);
	string s = p.InsertCoordinatesGenerator(NavalUnitType::BattleShip);
	s = p.InsertCoordinatesGenerator(NavalUnitType::BattleShip);

	// ------------

	cout << "*** IL GIOCO E' INIZIATO ***" << endl;
	string command = "";
	while (true) {
		std::getline(std::cin, command);
		cout << game.ExecCommand(command, PlayerNumber::PlayerOne).content() << endl;

		std::getline(std::cin, command);
		cout << game.ExecCommand(command, PlayerNumber::PlayerTwo).content() << endl;
	}
	
}

void InsertPlayerNavalUnit(GameManager& game, NavalUnitType type)
{
	string coordinates = "";
	string output_text = "";
	int max_number = 0;
	switch (type) {
	case NavalUnitType::BattleShip : 
		output_text = "Quali sono le coordinate per la corazzata";
		max_number = game.kBattleShipNumber;
		break;
	case NavalUnitType::SupportShip:
		output_text = "Quali sono le coordinate per la nave di supporto";
		max_number = game.kSupportShipNumber;
		break;
	case NavalUnitType::Submarine:
		output_text = "Quali sono le coordinate per il sottomarino ";
		max_number = game.kSubmarineNumber;
		break;
	}

	for (int i = 1; i <= max_number; i++) {
		cout << "Quali sono le coordinate per la corazzata " << i << " : " << endl;
		bool correct = false;
		while (!correct) {
			std::getline(std::cin, coordinates);
			correct = game.AddNavalUnit(coordinates, type, PlayerNumber::PlayerOne);
			if (!correct) {
				cout << "Errore nell'inserimento..." << endl;
			}	
		}
	}
}


