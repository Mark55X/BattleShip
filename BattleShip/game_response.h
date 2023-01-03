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
		GameResponse(bool status,
					string content = "", 
					bool next_shift = true, 
					string performed_action_ = "", 
					string error_type = "") :
			status_{ status },
			content_{ content }, 
			next_shift_{ next_shift },
			performed_action_{ performed_action_ },
			error_type_{ error_type }{}
		
		GameResponse(GameResponse&& response) = default;
		GameResponse& operator=(GameResponse&& response) = default;

		// Getters
		string& content() { return content_; }
		string& performed_action() { return performed_action_; }
		string& error_type() { return error_type_; }
		bool& status() { return status_; }
		bool& next_shift() { return next_shift_; }

		static constexpr const char* kIncorrectOrigin = "IncorrectOrigin";

		static constexpr const char* kFireAction = "FireAction";
		static constexpr const char* kMoveExploreAction = "MoveExploreAction";
		static constexpr const char* kMoveRepairAction = "MoveRepairAction";

	private:
		bool next_shift_;
		bool status_;
		string content_;
		string performed_action_;
		string error_type_;
	};


} // namespace battle_ships

#endif // game_response_h

