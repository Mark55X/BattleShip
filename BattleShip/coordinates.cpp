// Coordinates
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#include "coordinates.h"
#include <regex>

namespace battle_ships {


	Coordinates::Coordinates(int x, char y) : x_{x}, y_{static_cast<char>(toupper(y))}
	{
	}

	Coordinates::Coordinates(const string& coordinates) 
	{
		if (!regex_match(coordinates, std::regex(R"~([a-zA-Z][0-9]+)~"))) {
			InvalidCoordinatesException("InvalidCoordinatesException - Le coordinate devono essere nel formato 'A1' o 'A10' ");
		}

		x_ = (coordinates.length() == 2) ? coordinates[1] - '0' : stoi(coordinates.substr(1));
		y_ = static_cast<char>(toupper(coordinates[0]));
	}

	bool operator==(Coordinates first_coordinates, Coordinates second_coordinates)
	{
		return first_coordinates.x() == second_coordinates.x() &&
			   first_coordinates.y() == second_coordinates.y();
	}

	string to_string(Coordinates coordinates)
	{
		string str_coordinates = "";
		str_coordinates += (coordinates.y() >= 'J') ? (coordinates.y() + 2) : coordinates.y();
		str_coordinates += std::to_string(coordinates.x());
		return str_coordinates;
	}

}

