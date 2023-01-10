// SupportShip Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#ifndef support_ship_h
#define support_ship_h

#include "naval_unit.h"

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe SupportShip
	// Rappresenta la nave di supporto all'interno del gioco
	class SupportShip : public NavalUnit {

	public:
		// Costruttore
		// Parametri:
		// - centre_coordinates : coordinate centrali
		// - direction : direzione della nave
		SupportShip(Coordinates centre_coordinates, bool direction);

		// Overriding Action. 
		// Vedi naval_unit.h per informazioni su parametri
		// Azione: MUOVI E RIPARA
		// La nave di supporto si muove nelle coordinate indicate nel comando
		// e ripara completamente tutte le navi che si trovano in un'area 3x3
		// dalla sua coordinata centrale
		GameResponse Action(const Command& command,
					Player& current_player,
					Player& enemy_player)  override;

		// Costanti pubbliche
		// Indicano rispettivamente la grandezza della nave di supporto
		// e il suo scudo iniziale
		static constexpr int kSize = 3;
		static constexpr int kShield = 3;

	private:
		
	};


} // namespace battle_ships

#endif // support_ship_h

