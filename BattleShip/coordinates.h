// Coordinates Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#ifndef coordinates_h
#define coordinates_h

#include <stdexcept>
#include <string>

using std::string;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe Coordinates
	// Rappresenta le coordinate di una griglia
	// Invarianti:
	// 1. Una coordinata è formata da un carattere alfabetico e 
	//	  da un numero intero di massimo due cifre (0-99)
	class Coordinates {

	public:
		//Costruttore
		// Parametri:
		// x: ascissa (valore numerico)
		// y: ordinata (carattere alfabetico)
		Coordinates(int x, char y);

		// Costruttore che accetta le coordinate nel formato "CN", con
		// C carattere alfabetico
		// N numero di una o due cifre (da 0 a 99)
		Coordinates(const string& coordinates );

		// Getters
		int x() const { return x_; }
		char y() const { return y_; }
		
		// Setters
		void set_x(int x) { x_ = x; }
		void set_y(char y) { y_ = y; }

		// Classe InvalidDateException 
		// Eredita da std::invalid_argument perchè riguarda l'invalidità 
		// degli argomenti (x, y) per la creazione/modifica delle coordinate
		class InvalidCoordinatesException : public std::invalid_argument {
		public:
			InvalidCoordinatesException(string msg) : std::invalid_argument(msg) {}
		};

	private:
		int x_;  // ascissa
		char y_; // ordinata
	};

	// Overloading operatore == e !=
	bool operator==(Coordinates first_coordinates, Coordinates second_coordinates);
	bool operator!=(Coordinates first_coordinates, Coordinates second_coordinates);

	// Funzione to_string
	// Restituisce le coordinate in formato stringa
	string to_string(Coordinates coordinates);

} // namespace battle_ships

#endif // coordinates_h

