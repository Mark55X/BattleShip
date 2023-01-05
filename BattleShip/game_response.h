// GameResponse Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Anna Albertin

#ifndef game_response_h
#define game_response_h

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe GameResponse
	// Descrive la risposta del gioco elabora dopo l'esecuzione di un comando
	// Contiene:
	// - status : Lo Stato d'esecuzione del comando
	// - content: Il contenuto della risposta (quasi tutti i comandi hanno un particolare contenuto)
	// - next_shift : Se, dopo l'esecuzione dle comando, è il turno del giocatore successivo
	// - performed_action : Tipo di Azione svolta (FACOLTATIVA)
	// - error_type : Tipo di errore (FACOLTATIVO)
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
		
		// Costruttore di spostamento
		GameResponse(GameResponse&& response) = default;
		GameResponse& operator=(GameResponse&& response) = default;

		// Getters
		string& content() { return content_; }
		string& performed_action() { return performed_action_; }
		string& error_type() { return error_type_; }
		bool& status() { return status_; }
		bool& next_shift() { return next_shift_; }

		// Error Type
		static constexpr const char* kIncorrectOrigin = "IncorrectOrigin";

		// Action Permormed
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

