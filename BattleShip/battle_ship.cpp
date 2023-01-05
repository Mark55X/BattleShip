// BattleShip
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Anna Albertin

#include "battle_ship.h"

#include "player.h"

namespace battle_ships {

	BattleShip::BattleShip(Coordinates centre_coordinates, bool direction) : 
		NavalUnit(kSize, kShield, centre_coordinates, direction)
	{}

	
	GameResponse BattleShip::Action(const Command& command,
							Player& current_player, 
							Player& enemy_player) 
	{	
		Coordinates target = command.target();
		
		Grid& enemy_defence_grid = enemy_player.defence_grid();
		Grid& attack_grid = current_player.attack_grid();

		char value = enemy_defence_grid.GetCellValue(target);

		string game_response_content = "Eseguita azione FUOCO da [" + to_string(command.origin()) + 
										"] a [" + to_string(command.target()) + "] con esito: ";

		if (value == ' ') {
			attack_grid.EditCell('O', target);
			game_response_content += "acqua!";
			return GameResponse(true, game_response_content, true, GameResponse::kFireAction);
		}
		else if (islower(value)) {
			game_response_content += "già colpito!";
			return GameResponse(true, game_response_content, true, GameResponse::kFireAction);
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
					bool check = unit->direction() ? (target.y() == centre_coordinate.y()) : 
													 (target.x() == centre_coordinate.x());

					int range = unit->size() / 2;
					return target_coordinate >= (coordinate - range) &&
						   target_coordinate <= (coordinate + range) && 
						   check;
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

				game_response_content += "colpito e affondato!";
			}
			else {
				enemy_defence_grid.EditCell(static_cast<char>(tolower(value)), target);

				game_response_content += "colpito!";
			}
		}

		attack_grid.EditCell('X', target);
		return GameResponse(true,game_response_content, true, GameResponse::kFireAction);
	}
}

