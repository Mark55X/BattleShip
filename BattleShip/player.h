// Player Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef player_h
#define player_h

#include <vector>

#include "naval_unit.h"
#include "battle_ship.h"
#include "submarine.h"
#include "support_ship.h"
#include "grid.h"
#include "command.h"

using std::vector;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe Player
	class Player {

	public:
		bool AddNavalUnit(/*tipo*/ const Coordinates& start, const Coordinates& finish);
		bool ExecCommand(const Command& command);
		string Display() const;

	private:
		vector<BattleShip> battleships_;
		vector<Submarine> submarines_;
		vector<SupportShip> supportships_;

		Grid defence_grid_;
		Grid attack_grid_;

	};


} // namespace battle_ships

#endif // player_h

