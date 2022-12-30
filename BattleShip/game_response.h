// GameResponse Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef game_response_h
#define game_response_h

#include "naval_unit.h"

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {


	class GameResponse {

	public:
		GameResponse(bool status, string content, bool next_shift = true) : 
			status_{ status },
			content_{ content }, 
			next_shift_{ next_shift }{}
		
		// Getters
		string& content() { return content_; }
		bool& status() { return status_; }
		bool& next_shift() { return next_shift_; }

		
	private:
		bool next_shift_;
		bool status_;
		string content_;
		
	};


} // namespace battle_ships

#endif // game_response_h

