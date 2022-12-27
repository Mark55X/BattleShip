#include "support_ship.h"

namespace battle_ships {

	SupportShip::SupportShip(Coordinates centre_coordinates, bool direction):
		NavalUnit(kSize, kShield, centre_coordinates, direction)
	{}


	bool SupportShip::Action() const
	{
		return false;
	}
}

