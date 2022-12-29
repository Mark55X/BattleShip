#include "support_ship.h"
#include "player.h"

namespace battle_ships {

	SupportShip::SupportShip(Coordinates centre_coordinates, bool direction):
		NavalUnit(kSize, kShield, centre_coordinates, direction)
	{}


	bool SupportShip::Action(const Command& command, 
							 Player& current_player,
							 Player& enemy_player) const
	{
		return false;
	}
}

