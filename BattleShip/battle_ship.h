// BattleShip Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#ifndef battle_ship_h
#define battle_ship_h

#include "naval_unit.h"

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe BattleShip
	// Rappresenta la corazzata all'interno del gioco
	class BattleShip : public NavalUnit {

	public:
		// Costruttore
		// Parametri:
		// - centre_coordinates : coordinate centrali
		// - direction : direzione della nave
		BattleShip(Coordinates centre_coordinates, bool direction);

		// Overriding Action. 
		// Vedi naval_unit.h per informazioni su parametri
		// Azione: FUOCO
		// La corazzata spara un colpo nelle coordinate ricevute
		// Nella griglia di attacco viene riportata una X se l'esito è "colpito",
		// una O se l'esito è "acqua"
		GameResponse Action(const Command& command,
					Player& current_player,
					Player& enemy_player)  override;

		// Costanti pubbliche
		// Indicano rispettivamente la grandezza della corazzata
		// e il suo scudo iniziale
		static constexpr int kSize = 5;
		static constexpr int kShield = 5;		

	};


} // namespace battle_ships

#endif // battle_ship_h

