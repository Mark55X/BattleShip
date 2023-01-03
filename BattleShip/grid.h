// Grid Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#ifndef grid_h
#define grid_h

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
	// Possiede :
	//   1. Una matrice (grid) che rappresenta la griglia quadrata 12x12 del gioco
	class Grid {

	public:
		// Costruttore: crea una griglia di gioco 12x12 inizialmente vuota
		// (ogni cella contiene in realtà uno spazio vuoto ' ')
		Grid();
		bool AddRangeCells(char value, const Coordinates& start, const Coordinates& finish);
		void RemoveRangeCells(const Coordinates& start, const Coordinates& finish);
		bool MoveRangeCells(const Coordinates& origin_start, const Coordinates& origin_finish,
							const Coordinates& target_start, const Coordinates& target_finish);
		void EditCell(char value, const Coordinates& cell);
		char GetCellValue(const Coordinates& coordinates);
		string Display() const;
		
		class InvalidCellGridException : public std::invalid_argument {
		public:
			InvalidCellGridException(string msg) : std::invalid_argument(msg) {}
		};

		static constexpr int kGridSize = 12;

	private:
		char grid_[kGridSize][kGridSize];

		void ValidateCoordinates(const Coordinates& coordinates) const;
		bool CheckRangeCoordinates(const Coordinates& start, const Coordinates& finish) const;
		int GetCellCoordinateX(const Coordinates& coordinates) const;
		int GetCellCoordinateY(const Coordinates& coordinates) const;

	};


} // namespace battle_ships

#endif // grid_h


