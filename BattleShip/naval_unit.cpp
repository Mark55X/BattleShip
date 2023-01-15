// NavalUnit
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#include "naval_unit.h"

#include "coordinates.h"

namespace battle_ships {

	NavalUnit::NavalUnit(int size, int shield, Coordinates centre_coordinates, bool direction)
		: size_{size}, 
		shield_{ shield }, 
		centre_coordinates_{ centre_coordinates }, 
		direction_{ direction } {}

}

