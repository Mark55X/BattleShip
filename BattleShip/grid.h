// Grid Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef grid_h
#define grid_h

#include "naval_unit.h"

#include <stdexcept>
#include <string>

#include "coordinates.h"

using std::string;
using battle_ships::Coordinates;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe Grid
	// Rappresenta una griglia di gioco
	class Grid {

	public:
		Grid();
		bool AddRangeCells(char value, const Coordinates& start, const Coordinates& finish);
		bool RemoveRangeCells(const Coordinates& start, const Coordinates& finish);
		bool EditCell(char value, const Coordinates& cell);
		string Display() const;

	private:
		static constexpr int kGridSize = 12;
		char grid_[kGridSize][kGridSize];

		bool ValidateCoordinates(const Coordinates& coordinates) const;
		bool CheckRangeCoordinates(const Coordinates& start, const Coordinates& finish) const;
		int GetCellCoordinateX(const Coordinates& coordinates) const;
		int GetCellCoordinateY(const Coordinates& coordinates) const;

	};


} // namespace battle_ships

#endif // grid_h


