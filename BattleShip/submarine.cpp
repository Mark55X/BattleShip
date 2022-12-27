#include "submarine.h"

namespace battle_ships {

	Submarine::Submarine(Coordinates centre_coordinates, bool direction) :
		NavalUnit(kSize, kShield, centre_coordinates, direction)
	{}


	bool Submarine::Action() const
	{
		return false;
	}
}

