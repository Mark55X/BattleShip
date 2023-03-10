// SupportShip
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#include "support_ship.h"
#include "player.h"
#include <algorithm>

namespace battle_ships {

	SupportShip::SupportShip(Coordinates centre_coordinates, bool direction) :
		NavalUnit(kSize, kShield, centre_coordinates, direction)
	{}

	GameResponse SupportShip::Action(const Command& command,
		Player& current_player,
		Player& enemy_player)
	{
		Coordinates origin = command.origin();
		Coordinates target = command.target();

		Grid& defence_grid = current_player.defence_grid();
		auto& naval_units = current_player.naval_units();

		string str_target = "";
		str_target += static_cast<char>((target.y() >= 'J') ? (target.y() + 2) : target.y());
		str_target += std::to_string(target.x());

		//Move
		GameResponse response= Move(origin, target, defence_grid);
		if (response.status() == false)
			return response;

		// Action
		Coordinates centre = centre_coordinates();

		int start_x = (centre.x() - 1 < 1) ? 1 : centre.x() - 1;
		int start_y = (centre.y() - 1 < 'A') ? 'A' : centre.y() - 1;

		int finish_x = (centre.x() + 1 <= 12) ? centre.x() + 1 : 12;
		int finish_y = (centre.y() + 1 <= 'A' + 11) ? centre.y() + 1 : 'A' + 11;

		vector<Coordinates> coordinates;

		for (int y = start_y; y <= finish_y; y++) {
			for (int x = start_x; x <= finish_x; x++) {
				Coordinates check_coordinates(x, y);

				if (direction() && check_coordinates.y() == centre.y())
					continue;

				if (!direction() && check_coordinates.x() == centre.x())
					continue;

				if (defence_grid.GetCellValue(check_coordinates) != ' ' &&
					defence_grid.GetCellValue(check_coordinates) != 'E') {
					coordinates.push_back(check_coordinates);
				}
			}
		}

		for (auto p = coordinates.begin(); p != coordinates.end(); ++p) {

			Coordinates current_coordinate = *p;
			auto iter = std::find_if(naval_units.begin(), naval_units.end(),
				[current_coordinate](const std::unique_ptr<NavalUnit>& unit) {
					int target_coordinate = unit->direction() ? current_coordinate.x() : current_coordinate.y();

					Coordinates centre_coordinate = unit->centre_coordinates();
					int coordinate = unit->direction() ? centre_coordinate.x() : centre_coordinate.y();
					bool check = unit->direction() ? (current_coordinate.y() == centre_coordinate.y()) :
						(current_coordinate.x() == centre_coordinate.x());

					int range = unit->size() / 2;
					return target_coordinate >= coordinate - range &&
						target_coordinate <= coordinate + range && check;
				});

			if (iter == naval_units.end()) {
				// ATTENZIONE!! NON DEVE MAI SUCCEDERE QUESTO
				throw std::logic_error("SupportShip - Action: Errore nella gestione! - 1");
			}

			std::unique_ptr<NavalUnit>& unit = *iter;
			if (unit->shield() != unit->size()) {
				unit->set_shield(unit->size());
				Coordinates unit_centre = unit->centre_coordinates();

				char new_value = toupper(defence_grid.GetCellValue(unit_centre));

				int range = unit->size() / 2;
				if (unit->direction()) {
					defence_grid.RemoveRangeCells(Coordinates(unit_centre.x() - range, unit_centre.y()),
						Coordinates(unit_centre.x() + range, unit_centre.y()));

					if (defence_grid.AddRangeCells(new_value,
						Coordinates(unit_centre.x() - range, unit_centre.y()),
						Coordinates(unit_centre.x() + range, unit_centre.y())) == false)
						throw std::logic_error("SupportShip - Action: Errore nella gestione! - 2");
				}
				else {
					defence_grid.RemoveRangeCells(Coordinates(unit_centre.x(), unit_centre.y() - range),
						Coordinates(unit_centre.x(), unit_centre.y() + range));

					if (defence_grid.AddRangeCells(new_value,
						Coordinates(unit_centre.x(), unit_centre.y() - range),
						Coordinates(unit_centre.x(), unit_centre.y() + range)) == false)
						throw std::logic_error("SupportShip - Action: Errore nella gestione! - 3");
				}
			}
		}
		return GameResponse(true, "Nave di supporto spostata in cella [" + str_target +
			"] ed eseguita azione RIPARA", true, GameResponse::kMoveRepairAction);
	}

	GameResponse SupportShip::Move(const Coordinates& origin, const Coordinates& target, Grid& defence_grid)
	{

		Coordinates centre = centre_coordinates();

		string str_target = "";
		str_target += static_cast<char>((target.y() >= 'J') ? (target.y() + 2) : target.y());
		str_target += std::to_string(target.x());

		defence_grid.GetCellValue(target); // Lancia eccezione se target non ? valida
		if (direction()) {

			if (target.x() > centre.x()) {

				if (!defence_grid.MoveRangeCells(Coordinates(origin.x() + 1, origin.y()),
					Coordinates(origin.x() - 1, origin.y()),
					Coordinates(target.x() + 1, target.y()),
					Coordinates(target.x() - 1, target.y()))) {

					return GameResponse(false, "Impossibile muovere la nave di supporto nella cella [" + str_target +
						"] : alcune celle sono gia' occupate", false);
				}
			}
			else {
				if (!defence_grid.MoveRangeCells(Coordinates(origin.x() - 1, origin.y()),
					Coordinates(origin.x() + 1, origin.y()),
					Coordinates(target.x() - 1, target.y()),
					Coordinates(target.x() + 1, target.y()))) {


					return GameResponse(false, "Impossibile muovere la nave di supporto nella cella [" + str_target +
						"] : alcune celle sono gia' occupate", false);
				}
			}
		}
		else {
			if (target.y() > centre.y()) {
				if (!defence_grid.MoveRangeCells(Coordinates(origin.x(), origin.y() + 1),
					Coordinates(origin.x(), origin.y() - 1),
					Coordinates(target.x(), target.y() + 1),
					Coordinates(target.x(), target.y() - 1))) {
					return GameResponse(false, "Impossibile muovere la nave di supporto nella cella [" + str_target +
						"] : alcune celle sono gia' occupate", false);
				}
			}
			else {

				if (!defence_grid.MoveRangeCells(Coordinates(origin.x(), origin.y() - 1),
					Coordinates(origin.x(), origin.y() + 1),
					Coordinates(target.x(), target.y() - 1),
					Coordinates(target.x(), target.y() + 1))) {
					return GameResponse(false, "Impossibile muovere la nave di supporto nella cella [" + str_target +
						"] : alcune celle sono gia' occupate", false);
				}
			}

		}
		set_centre_coordinates(target);

		return GameResponse(true);
	}
}

