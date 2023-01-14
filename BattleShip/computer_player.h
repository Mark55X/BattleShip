// Computer Player Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#ifndef computer_player_h
#define computer_player_h

#include <vector>

#include <chrono>
#include <random>

#include "battle_ship.h"
#include "enums.h"
#include "submarine.h"
#include "support_ship.h"

using std::vector;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe ComputerPlayer
	class ComputerPlayer {

	public:
		// Funzione InsertCoordinatesGenerator
		// Genera casualmente una coppia di coordinate per l'inserimento della nave
		// Parametri:
		//  - unit_type : il tipo di unita navale
		string InsertCoordinatesGenerator(const NavalUnitType unit_type);

		// Funzione MemorizeCentreCoordinates
		// Memorizza le coordinate centrali della nave nel vettore ships_centre_coordinates_
		// Parametri:
		//  - couple_coordinates : contiene le coordinate di poppa e prua della nave da memorizzare
		bool MemorizeCentreCoordinates(string& couple_coordinates);

		// Funzione ActionCoordinatesGenerator
		// Genera una coppia di coordinate valide per l'esecuzione di un'azione
		string ActionCoordinatesGenerator();

		// Funzione RemoveCoordinates
		// Rimuove le coordinate date dal vettore ships_centre_coordinates_
		// Parametri:
		//  - coordinates : le coordinate da rimuovere dal vettore
		bool RemoveCoordinates(const Coordinates& coordinates);

		// Funzione SetCoordinates
		// Sostituisce all'interno del vettore ships_centre_coordinates_ le
		// vecchie coordinate con le nuove
		// Parametri:
		//  - old_coordinates : le vecchie da sostituire
		//  - new_coordinates : le nuove coordinate 
		bool SetCoordinates(Coordinates& old_coordinates, Coordinates& new_coordinates);

		// Funzione GetCoordinatesNumber
		// Restituisce il numero di coordinate (e quindi di navi) memorizzate nel
		// vettore ships_centre_coordinates_
		int GetCoordinatesNumber() { return ships_centre_coordinates_.size(); }

	private:
		// vettore di coordinate centrali delle navi del giocatore computer
		vector<Coordinates> ships_centre_coordinates_;

		// Funzione privata NumberGenerator
		// Genera un numero casuale da 0 a n (parametro)
		int NumberGenerator(const int n);

		// Funzione privata CoordinatesGenerator
		// Genera delle coordinate casuali
		// Parametri:
		//  - grid_size : indica la dimensione della griglia, per conoscere il 
		//    range di coordinate possibili
		Coordinates CoordinatesGenerator(const int grid_size);
	};


} // namespace battle_ships

#endif // computer_player_h