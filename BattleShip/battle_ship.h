// BattleShip Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

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
		BattleShip(Coordinates centre_coordinates, bool direction);
		bool Action() const override;

	private:
		static constexpr int kSize = 5;
		static constexpr int kShield = 5;

	};


} // namespace battle_ships

#endif // battle_ship_h

