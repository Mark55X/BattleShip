#include "submarine.h"
#include "player.h"

namespace battle_ships {

	Submarine::Submarine(Coordinates centre_coordinates, bool direction) :
		NavalUnit(kSize, kShield, centre_coordinates, direction)
	{}


	bool Submarine::Action(const Command& command, 
						   Player& current_player,
						   Player& enemy_player) const
	{
		return false;
	}
}

