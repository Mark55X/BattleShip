// Computer Player Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#ifndef computer_player_h
#define computer_player_h

#include <chrono>
#include <random>
#include <vector>

#include "naval_unit.h"
#include "battle_ship.h"
#include "submarine.h"
#include "support_ship.h"
#include "grid.h"
#include "command.h"
#include "enums.h"

using std::vector;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe ComputerPlayer
	class ComputerPlayer {

	public:
		ComputerPlayer(void);
		string InsertCoordinatesGenerator(const NavalUnitType unit_type);
		void MemorizeCentreCoordinates(string& couple_coordinates);
		string ActionCoordinatesGenerator();

	private:
		vector<Coordinates> ships_centre_coordinates_;
		static constexpr int kGridSize = 12;

		int NumberGenerator(const int n);
		Coordinates CoordinatesGenerator(const int grid_size);
	};


} // namespace battle_ships

#endif // computer_player_h