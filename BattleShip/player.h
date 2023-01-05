// Player Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef player_h
#define player_h

#include <memory>
#include <vector>

#include "naval_unit.h"
#include "command.h"
#include "enums.h"
#include "game_response.h"

using std::vector;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe Player
	// Rappresenta un giocatore all'interno del gioco
	// Possiede:
	// - Una griglia di attacco
	// - Una griglia di difesa
	// - Una collezione delle unit� navali che possiede
	class Player {

	public:
		// Funzione AddNavalUnit
		// Inserisce un unit� navale nel gioco con parametri:
		//		start : coordinata poppa
		//		finish : coordinata prua
		//		unit_type : tipo di unit� navale da inserire
		//  
		// Ritorna una GameResponse che pu� indicare errore se le coordinate inserite
		// non sono valide (celle gi� occupate oppure lunghezza tra poppa e prua non 
		// conforme alla lunghezza dell'unit� navale da inserire)
		GameResponse AddNavalUnit(const Coordinates& start, 
								  const Coordinates& finish,
								  const NavalUnitType unit_type);

		// Funzione IsLoser
		// Restituisce true se non ha pi� navi disponibili
		bool IsLoser();

		// Funzione Display
		// Restituisce una stringa con le configurazioni della
		// griglia di attacco e di difesa
		string Display() const;

		// getters
		Grid& defence_grid() { return defence_grid_; }
		Grid& attack_grid() { return attack_grid_; }
		vector<std::unique_ptr<NavalUnit>>& naval_units() { return naval_units_; }

	private:
		// Collezione di Unit� Navali
		vector<std::unique_ptr<NavalUnit>> naval_units_;

		// Griglie di difesa e attacco
		Grid defence_grid_;
		Grid attack_grid_;

		// Funzione privata CheckCellLength
		// restituisce true se la lunghezza delle celle corrispondenti
		// equivale a quella ammessa per un tipo di unit� navale
		bool CheckCellLength(const NavalUnitType unit_type, int cell_length);
	};

	// Helper function ExecCommand
	// Esegue un particolare comando (non speciale) per un giocatore
	// Parametri:
	// - command : comando da eseguire
	// - current_player : giocatore per cui si esegue il comando
	// - enemy_player : giocatore avversario
	GameResponse ExecCommand(const Command& command, Player& current_player, Player& enemy_player);

} // namespace battle_ships

#endif // player_h