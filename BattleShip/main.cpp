// Main
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#include "game_manager.h";

#include <iostream>
#include "grid.h"
#include "logger.h"
#include <regex>
#include "enums.h"

using std::cout;
using std::endl;
using battle_ships::GameManager;
using std::regex;
using battle_ships::PlayerNumber;
using battle_ships::NavalUnitType;

/*
* Pensieri miei abbastanza profondi da scrivere nel readme.TXT
*
* Secondo me � ESSENZIALE dividere il MAIN dal resto del progetto
* tale che si possono creare molti modi per fare il main
* senza che influisca DIRETTAMENTE nella logica del gioco.
*
* Mi spiego meglio: perch� il main dovrebbe fare i controlli di validit� dei comandi?
* Per me non deve farli, non � il suo ruolo. Lui sa solo che � un comando, non sa
* nemmeno cosa fa, perch� la descrizione di tale esecuzione deve essere descritta dal
* CORE del gioco che mi invier� un oggetto di tipo RESPONSE
*
* Attenzione, parte importante perch� il RESPONSE sar� una risponsa GENERICA (non � un template attenzione :) )
* Response{
	StatusExecution : bool  -> Se avvenuto con successo o meno
	Content : string        -> Contenuto (pu� essere la string aformattata per il comando XX XX
										  o la descrizione tipo 'Eseguito FUOCO su cella nemica A1 ')
	NextShift : bool        -> False se il turno � ancora del giocatore che ha eseguito il comando
  }

  QUESTO PERCHE' giustamente se io avessi i metodi che restituiscono bool cosa capirei?
  Se � false, per quale motivo � false? Coordiante fuori? Entrambe? O solo una? Oppure sono giuste
  ma l'origin riguarda nessun unit� navale e per me QUESTO NON FA LO SWITCH DEL TURNO!!

  Ok quindi ha senso usare un oggetto pi� descrittivo, si ok per� perch� non usare le eccezioni?
  Tipo: InvalidCellException con la DESCRIZIONE interna di cosa � sbagliato?

  Se siamo nel caso di Logger/Replay � palese l'uso delle eccezioni: il file non esiste, problemi di scrittura
  ecc,... MA NEL GIOCO?? Forse si, forse no: bloccare l'esecuzione di colpo mi implicherebbe che non serve pi�
  la Response descritta qui sopra perch� so che se c'� un eccezione TEORICAMENTE devo rifare il turno...
  ma se tipo mi parte un eccezione per il Logger? Quella viene catturata da s� e quindi non influenzerebbe
  l'andamento della partita...dovrebbe bloccare la partita? Come ? Vado a lavarmi, buon Natale a tutti.

  Abbiamo quindi: Eccezioni ->  PRO: Dati che si passano pi� leggeri (o cos� si crede)
								CONTRO: Blocco dell'esecuzione improvviso

				  Response ->   PRO: Non c'� interruzione del flusso (forse un p� stile retro?)
								CONTRO: La gran parte delle funzioni resituiscono la response

  Attenzione che... XX XX SUCCESFUL ma non cambia turno..come faccio con eccezioni?
					A1 B2 SUCCESFUL fantastico...nessuna eccezione ma come stampo che � avvenuta l'azione?
	Quello che sto dicendo � che: io ho lo stesso risultato di Response SOLO se avviene l'eccezione. Ma
	io magari vorrei avere il risultato anche quando non accade. OVVERO dare pi� potere al main,
	fargli capire cosa significano tali comandi... (impossibile capire l'AZIONE in s�)


*/
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
	bool s;
	s = game.AddNavalUnit("A1 A5", NavalUnitType::BattleShip, PlayerNumber::PlayerOne);
	s = game.AddNavalUnit("B2 B2", NavalUnitType::Submarine, PlayerNumber::PlayerOne);

	s = game.AddNavalUnit("A1 A5", NavalUnitType::BattleShip, PlayerNumber::PlayerTwo);

	// Da verificare l'edit della cella
	s = game.ExecCommand("A3 A5", PlayerNumber::PlayerOne);
	cout << "ciao";
	//cout << game.ExecCommand("XX XX", PlayerNumber::PlayerOne);
	
	/*battle_ships::Grid g;
	
	 g.AddRangeCells('C', Coordinates("A5"), Coordinates("A1"));
	 g.AddRangeCells('C', Coordinates("A7"), Coordinates("D7"));
	 g.AddRangeCells('C', Coordinates("C1"), Coordinates("C7"));

	 g.RemoveRangeCells(Coordinates("A1"), Coordinates("A5"));

	cout << g.Display();

	battle_ships::Grid m;

	m.AddRangeCells('C', Coordinates("A5"), Coordinates("A1"));
	m.AddRangeCells('C', Coordinates("A7"), Coordinates("D7"));
	m.AddRangeCells('C', Coordinates("C1"), Coordinates("C7"));

	m.RemoveRangeCells(Coordinates("A1"), Coordinates("A5"));

	cout << m.Display();

	 devo prendere la prima riga di str_defence_grid e sostituire il \n con
	 un tab seguito dalla prima riga di str_attack_grid (fino al |n compreso)
	 poi ripetere il processo per ogni riga, quindi in totale 13 volte (tutte
	 le righe di gioco pi� la riga degli indici x

	string str_g = g.Display();
	string str_m = m.Display();

	 metto prima g poi m

	string g_m = "";
	int pos_return_g = -1;
	int pos_return_m = -1;

	int width = 48;
	string title_defence = "Griglia di difesa";
	string title_attack = "Griglia di attacco";
	int number_of_spaces = width - title_defence.length();
	g_m += "    ";
	for (int k = 0; k < number_of_spaces / 2; k++)
		g_m += " ";
	g_m += title_defence;
	for (int k = 0; k < width - title_defence.length() - number_of_spaces / 2; k++)
		g_m += " ";
	g_m += "\t\t    ";
	number_of_spaces = width - title_attack.length();
	for (int k = 0; k < number_of_spaces / 2; k++)
		g_m += " ";
	g_m += title_attack;
	g_m += '\n';

	for (int i = 0; i < 26; i++)
	{
		pos_return_g = str_g.find('\n');
		g_m += str_g.substr(0, pos_return_g);
		str_g.erase(0, pos_return_g + 1);

		g_m += "\t\t";

		pos_return_m = str_m.find('\n');
		g_m += str_m.substr(0, pos_return_m + 1);
		str_m.erase(0, pos_return_m + 1);
	}

	cout << g_m;*/


	/*battle_ships::Logger l;
	l.LogCommand(GameManager::PlayerOne, "XX XX");
	l.LogCommand(GameManager::PlayerOne, "A2 B4");
	l.LogCommand(GameManager::PlayerOne, "XX XX");*/
	
}


