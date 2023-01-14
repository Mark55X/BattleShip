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
	// Rappresenta una griglia generica di gioco
	class Grid {

	public:
		// Costruttore: crea una griglia di gioco 12x12 inizialmente vuota
		// (ogni cella contiene in realtà uno spazio vuoto ' ')
		Grid();

		// Funzioni di gestione dei dati nella griglia

		// Funzione AddRangeCells
		// Inserisce un determinato valore in tutte le coordinate da quella 
		// iniziale a quella finale (se tutte le celle sono disponibili)
		// Parametri: 
		// - value: valore da inserire
		// - start: coordinata iniziale
		// - finish: coordinata finale
		bool AddRangeCells(char value, const Coordinates& start, const Coordinates& finish);

		// Funzione RemoveRangeCells
		// Rimuove un determinato valore in tutte le coordinate da quella 
		// iniziale a quella finale
		// Parametri: 
		// - start: coordinata iniziale
		// - finish: coordinata finale
		void RemoveRangeCells(const Coordinates& start, const Coordinates& finish);

		// Funzione MoveRangeCells
		// Sposta i valori delle celle Range: [origin_finish, origin_finish] 
		// a  [target_start, target_finish] solo se le celle target sono vuote
		bool MoveRangeCells(const Coordinates& origin_start, const Coordinates& origin_finish,
							const Coordinates& target_start, const Coordinates& target_finish);

		// Funzione EditCell
		// Modifica il valore di una determinata cella
		// Parametri:
		// - value : nuovo valore
		// - cell: coordianata della cella da modificare
		void EditCell(char value, const Coordinates& cell);

		// Funzione GetCellValue
		// Ritorna il valore di una determinata cella
		// - coordinates: coordianata della cella da ispezionare
		char GetCellValue(const Coordinates& coordinates);

		// Funzione Display
		// Ritorna una stringa con la configurazione della griglia
		string Display() const;
		
		// Classe InvalidCellGridException
		// Eccezione che descrive l'invalidità della cella di una griglia 
		// (esempio: coordinata per la griglia non valida)
		class InvalidCellGridException : public std::invalid_argument {
		public:
			InvalidCellGridException(string msg) : std::invalid_argument(msg) {}
		};

		static constexpr int kGridSize = 12;

	private:
		// Matrice quadrata contenente i dati
		char grid_[kGridSize][kGridSize];

		// Funzione ValidateCoordinates
		// Valida le coordinate passate come parametro
		// Se non sono corrette lancia eccezione InvalidCellGridException
		void ValidateCoordinates(const Coordinates& coordinates) const;

		// Funzione CheckRangeCoordinates
		// Restituisce true solo se tutte le celle che stanno nel range [start,finish]
		// sono celle vuote. Nel suo controllo ignora le coordinate che stanno
		// tra ignore_start e ignore_finish
		bool CheckRangeCoordinates(const Coordinates& start, const Coordinates& finish, 
								    int ignore_start = -1,  int ignore_finish = -1, int fixed_coordinate = -1) const;

		// Funzione GetCellCoordinateX
		// Data una coordinata, ritorna l'indice x per accedere alla matrice
		int GetCellCoordinateX(const Coordinates& coordinates) const;

		// Funzione GetCellCoordinateY
		// Data una coordinata, ritorna l'indice y per accedere alla matrice
		int GetCellCoordinateY(const Coordinates& coordinates) const;

	};


} // namespace battle_ships

#endif // grid_h


