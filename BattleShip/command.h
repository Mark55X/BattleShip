// Command Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef command_h
#define command_h

#include "coordinates.h"

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe Command
	class Command {

	public:
		Command(Coordinates origin, Coordinates target)
			: origin_{origin}, target_{target} {}

		//getters
		Coordinates origin() const {return origin_;}
		Coordinates target() const {return target_;}

	private:
		Coordinates origin_;
		Coordinates target_;
	};


} // namespace battle_ships

#endif // command_h

