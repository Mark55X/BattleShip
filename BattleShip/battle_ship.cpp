#include "battle_ship.h"

namespace battle_ships {

	BattleShip::BattleShip(Coordinates centre_coordinates, bool direction) : 
		NavalUnit(kSize, kShield, centre_coordinates, direction)
	{}


	bool BattleShip::Action() const
	{
		return false;
	}
}

