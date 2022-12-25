// GameManager Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef game_manager_h
#define game_manager_h

#include <string>

using std::string;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe GameManager
	// Rappresenta il gestore del gioco, l'unica classe che viene resa
	// utilizzabile nel main perchè fornisce tutti gli strumenti 
	// necessari per lo svolgimento del gioco:
	// 1. Eseguire un comando di un particolare giocatore
	// 2. Restituire se qualcuno ha vinto
	class GameManager {

	public:

		enum PlayerNumber
		{
			PlayerOne = 1,
			PlayerTwo
		};

		bool AddNavalUnit();

		// Esegue un comando 
		// Restituisce true solo se il comando viene eseguito con successo
		bool ExecCommand(const string& command, const PlayerNumber player);

		// Funzione IsWinner
		// Restituisce true se il giocatore passato come argomento è il vincitore
		// Un giocatore ha vinto se tutte le unità navali del suo avversario sono affondate
		bool IsWinner(const PlayerNumber player);

	private:
		

	};


} // namespace battle_ships

#endif // game_manager_h

