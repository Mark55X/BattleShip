#include "submarine.h"

#include "enums.h"
#include "player.h"

namespace battle_ships {

	Submarine::Submarine(Coordinates centre_coordinates, bool direction) :
		NavalUnit(kSize, kShield, centre_coordinates, direction)
	{}


	GameResponse Submarine::Action(const Command& command,
						   Player& current_player,
						   Player& enemy_player) 
	{
		Coordinates origin = command.origin();
		Coordinates target = command.target();

		Grid& enemy_defence_grid = enemy_player.defence_grid();
		Grid& defence_grid = current_player.defence_grid();
		Grid& attack_grid = current_player.attack_grid();

		//Move
		if (defence_grid.GetCellValue(target) != ' ') {
			return GameResponse(false, "Impossibile muovere il sottomarino nella cella [" +to_string(target) + 
										"] : e' gia' occupata", false);
		}
		defence_grid.EditCell(static_cast<char>(NavalUnitType::Submarine), target);
		defence_grid.EditCell(' ', centre_coordinates());
		set_centre_coordinates(target);

		//Action
		Coordinates centre = target;	
		int start_x = (centre.x() - 2 < 1) ? 1 : centre.x() - 2;
		int start_y = (centre.y() - 2 < 'A') ? 'A' : centre.y() - 2;

		int finish_x = (centre.x() + 2 <= 12) ? centre.x() + 2 : 12;
		int finish_y = (centre.y() + 2 <= 'A' + 12) ? centre.y() + 2 : 'A' + 12;

		for (int y = start_y; y <= finish_y; y++) {
			for (int x = start_x; x <= finish_x; x++) {
				Coordinates check_coordinates(x, y);

				if (check_coordinates == centre)
					continue;

				char value = enemy_defence_grid.GetCellValue(check_coordinates);
				if (value != ' ') {
					attack_grid.EditCell('Y', check_coordinates);
				}
			}
		}
		return GameResponse(true,"Sottomarino spostato in cella [" + to_string(target) +
			"] ed eseguita azione CERCA",true, GameResponse::kMoveExploreAction);
	}
}

