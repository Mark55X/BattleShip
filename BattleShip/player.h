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

using std::vector;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe Player
	class Player {

	public:
		bool AddNavalUnit(const Coordinates& start, 
						  const Coordinates& finish,
						 const NavalUnitType unit_type);

		bool IsLoser();
		string Display() const;

		// getters
		Grid& defence_grid() { return defence_grid_; }
		Grid& attack_grid() { return attack_grid_; }
		vector<std::unique_ptr<NavalUnit>>& naval_units() { return naval_units_; }

	private:
		/*vector<BattleShip> battleships_;
		vector<Submarine> submarines_;
		vector<SupportShip> supportships_;*/

		//vector<unique_ptr<NavalUnit>> naval_units;
		vector<std::unique_ptr<NavalUnit>> naval_units_;

		Grid defence_grid_;
		Grid attack_grid_;

		bool CheckCellLength(const NavalUnitType unit_type, int cell_length);
	};

	bool ExecCommand(const Command& command, Player& current_player, Player& enemy_player);

} // namespace battle_ships

#endif // player_h