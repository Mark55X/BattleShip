// GameManager Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef game_manager_h
#define game_manager_h

#include <string>

#include "player.h"
#include "logger.h"
#include "enums.h"
#include "game_response.h"

using std::string;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe GameManager
	// Rappresenta il gestore del gioco, l'unica classe che viene resa
	// utilizzabile nel main perch� fornisce tutti gli strumenti 
	// necessari per lo svolgimento del gioco:
	// 1. Eseguire un comando di un particolare giocatore
	// 2. Restituire se qualcuno ha vinto
	class GameManager {

	public:

		GameResponse AddNavalUnit(const string& coordinates,
						  const NavalUnitType unit_type, 
						  const PlayerNumber player);

		// Gestisce ed Esegue un comando
		// Restituisce un oggetto di tipo GameResponse (vedi game_response.h per dettagli)
		// con le indicazioni sull'esecuzione del comando
		GameResponse ExecCommand(const string& command, const PlayerNumber player);

		// Funzione IsWinner
		// Restituisce true se il giocatore passato come argomento � il vincitore
		// Un giocatore ha vinto se tutte le unit� navali del suo avversario sono affondate
		bool IsWinner(const PlayerNumber player);

		// Costanti 
		// Contengono il numero delle unit� navali (per tipo)
		// che sono presenti ad inizio partita
		static constexpr int kBattleShipNumber = 3;
		static constexpr int kSupportShipNumber = 3;
		static constexpr int kSubmarineNumber = 2;

		// TODO: da spostare nelle navi???
		static constexpr char kSonarCharacter = 'Y';
		static constexpr char kHitCharacter = 'X';
		static constexpr char kMissCharacter = 'O';

	private:
		// Oggetto di tipo Logger che gestisce il file di log 
		// contenente i comandi validi eseguiti correttamente
		Logger logger_;

		// I due giocatori
		Player first_player_;
		Player second_player_;
		
		// Funzione privata ValidateCommand
		// Restituisce true se il comando passato come parametro
		// � negli standard del formato accettato
		bool ValidateCommand(const string& command);

		// Costanti private riguradante i comandi speciali
		static constexpr const char* kCommandDisplay = "XX XX";
		static constexpr const char* kCommandEraseSonar = "AA AA";
		static constexpr const char* kCommandEraseHit = "BB BB";
		static constexpr const char* kCommandEraseMiss = "CC CC";

	};


} // namespace battle_ships

#endif // game_manager_h



