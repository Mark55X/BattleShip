#include "battle_ship.h"
#include "player.h"

namespace battle_ships {

	BattleShip::BattleShip(Coordinates centre_coordinates, bool direction) : 
		NavalUnit(kSize, kShield, centre_coordinates, direction)
	{}

	
	bool BattleShip::Action(const Command& command,
							Player& current_player, 
							Player& enemy_player) 
	{	
		Coordinates target = command.target();
		
		Grid& enemy_defence_grid = enemy_player.defence_grid();
		Grid& attack_grid = current_player.attack_grid();

		char value = enemy_defence_grid.GetCellValue(target);
		if (value == ' ') {
			return attack_grid.EditCell('O', target);
		}
		else if (isupper(value)) {

			// Logica che si dovrebbe spostare su Player.Attack(); ?? 
			// Dato il target, capire a che oggetto appartiene e fare shield --
			// Se shield == 0 ELIMINO

			auto& enemy_units = enemy_player.naval_units();
			auto iter = std::find_if(enemy_units.begin(), enemy_units.end(),
				[target](const std::unique_ptr<NavalUnit>& unit) {
					int target_coordinate = unit->direction() ? target.x() : target.y();

					Coordinates centre_coordinate = unit->centre_coordinates();
					int coordinate = unit->direction() ? centre_coordinate.x() : centre_coordinate.y();

					int range = unit->size() / 2;
					return target_coordinate >= coordinate - range &&
						target_coordinate <= coordinate + range;
				});

			if (iter == enemy_units.end()) {
				// ATTENZIONE!! NON DEVE MAI SUCCEDERE QUESTO
				throw std::logic_error("BattleShip - Action: Errore nella gestione!");
			}

			std::unique_ptr<NavalUnit>& unit = *iter;
			unit->set_shield(unit->shield() - 1);

			if (unit->shield() == 0) {			
				Coordinates centre = unit->centre_coordinates();

				int range = unit->size() / 2;
				if (unit->direction()) {
					Coordinates start(centre.x() - range, centre.y());
					Coordinates finish(centre.x() + range, centre.y());
					enemy_defence_grid.RemoveRangeCells(start, finish);
				}
				else {
					Coordinates start(centre.x(), centre.y() - range);
					Coordinates finish(centre.x() , centre.y() + range);
					enemy_defence_grid.RemoveRangeCells(start, finish);
				}
			
				enemy_units.erase(iter);
			}
			else {
				if (!enemy_defence_grid.EditCell(static_cast<char>(tolower(value)), target))
					return false; // POSSIBILE TRY-CATCH CON ROLLBACK??
			}
		}

		return attack_grid.EditCell('X', target);
	}
}

