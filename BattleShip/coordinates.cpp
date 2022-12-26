#include "coordinates.h"

namespace battle_ships {


	Coordinates::Coordinates(int x, char y) : x_{x}, y_{static_cast<char>(toupper(y))}
	{
	}

	Coordinates::Coordinates(const string& coordinates) 
	{
		if (coordinates.length() != 2 && coordinates.length() != 3) {
			throw InvalidCoordinatesException("InvalidCoordinatesException - Le coordinate devono essere nel formato 'A1' o 'A10' ");
		}
		
		if (!isalpha(coordinates[0]) || !isdigit(coordinates[1])) {
			throw InvalidCoordinatesException("InvalidCoordinatesException - La prima coordinata deve essere un carattere "
											  "alfabetico, la seconda un numero ");
		}

		if (coordinates.length() == 3 && !isdigit(coordinates[2])) {
			throw InvalidCoordinatesException("InvalidCoordinatesException - La prima coordinata deve essere un carattere "
											  "alfabetico, la seconda un numero ");
		}

		x_ = (coordinates.length() == 2) ? coordinates[1] - '0' : stoi(coordinates.substr(1));
		y_ = static_cast<char>(toupper(coordinates[0]));
	}

}

