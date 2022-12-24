// BattleShip Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

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
		bool Action() const override;

	private:
		static constexpr int kSize = 1;
		static constexpr int kShield = 1;

	};


} // namespace battle_ships

#endif // submarine_h
