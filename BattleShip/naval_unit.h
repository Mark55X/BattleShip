// NavalUnit Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef naval_unit_h
#define naval_unit_h

#include "coordinates.h"
#include "grid.h"
#include "command.h"
#include "game_response.h"

namespace battle_ships {

	class Player;

	// Classe virtuale pura NavalUnit
	// Rappresenta un unità navale all'interno del gioco
	// Possiede :
	//   1. Una grandezza (size), ovvero il numero di caselle nella griglia di gioco
	//   2. Uno scudo (shield), ovvero il numero di celle non ancora colpite 
	//		(inizialmente uguale a Size)
	//	 3. Le coordinate del centro (centre_coordinates), importanti perché
	//		rappresentano la nave nel momento in cui essa deve compiere un'azione
	//   4. L'orientamento (direction), rappresentato con una variabile booleana,
	//		che può essere verticale (true) o orizzontale (false) ?????????????
	class NavalUnit {

	public:

		NavalUnit(int size, 
				  int shield, 
				  Coordinates centre_coordinates, 
				  bool direction);

		// getters
		int size() const { return size_; }
		int shield() const { return shield_; }
		Coordinates centre_coordinates() const { return centre_coordinates_; }
		bool direction() const { return direction_; }

		void set_shield(int value) { shield_ = value; }
		void set_centre_coordinates(Coordinates coordinates) { centre_coordinates_ = coordinates; }

		// Una Unità navale può compiere un'azione in base
		// al tipo di unità. Non è possibile definire tale comportamento
		// in questa classe
		virtual GameResponse Action(const Command& command,
							Player& current_player,
							Player& enemy_player)  = 0;

	private:
		int size_;
		int shield_;
		Coordinates centre_coordinates_;
		bool direction_;

	};


} // namespace battle_ships

#endif // naval_unit_h
