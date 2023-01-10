// Command Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Anna Albertin

#ifndef command_h
#define command_h

#include "coordinates.h"

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe Command
	// Descrive un comando di gioco (CoordinataORIGIN CoordinataTARGET)
	class Command {

	public:
		// Costruttore
		// Parametri:
		// - origin : coordinata di origine del comando
		// - target : coordinata target del comando
		Command(Coordinates origin, Coordinates target)
			: origin_{origin}, target_{target} {}

		//Getters
		Coordinates origin() const {return origin_;}
		Coordinates target() const {return target_;}

	private:
		Coordinates origin_; // coordinata di origine del comando
		Coordinates target_; // coordinata target del comando
	};


} // namespace battle_ships

#endif // command_h

