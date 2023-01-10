// Submarine Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Anna Albertin

#ifndef submarine_h
#define submarine_h

#include "naval_unit.h"

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe Submarine
	// Rappresenta il sottomarino all'interno del gioco
	class Submarine : public NavalUnit {

	public:
		// Costruttore
		// Parametri:
		// - centre_coordinates : coordinate centrali
		// - direction : direzione della nave
		Submarine(Coordinates centre_coordinates, bool direction);

		// Overriding Action. 
		// Vedi naval_unit.h per informazioni su parametri
		// Azione: MUOVI E CERCA
		// Il sottomarino si muove nelle coordinate indicate nel comando
		// e cerca le unità navali avversarie in un'area 5x5, riportando in corrispondenza
		// di esse delle Y se la nave avvistata non è colpita,
		// delle X se invece era già stata colpita
		GameResponse Action(const Command& command,
					Player& current_player,
					Player& enemy_player)  override;

		// Costanti pubbliche
		// Indicano rispettivamente la grandezza del sottomarino
		// e il suo scudo iniziale
		static constexpr int kSize = 1;
		static constexpr int kShield = 1;

	private:
	

	};


} // namespace battle_ships

#endif // submarine_h

