// BattleShip Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

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
		SupportShip(Coordinates centre_coordinates, bool direction);

		bool Action(const Command& command, 
					Player& current_player,
					Player& enemy_player)  override;

		static constexpr int kSize = 3;
		static constexpr int kShield = 3;

	private:
		
	};


} // namespace battle_ships

#endif // support_ship_h

