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
	// Rappresenta la corazzata all'interno del gioco
	class SupportShip : public NavalUnit {

	public:
		bool Action() const override;

	private:
		static constexpr int kSize = 3;
		static constexpr int kShield = 3;

	};


} // namespace battle_ships

#endif // support_ship_h

