#include "game_manager.h"

#include <regex> 

using std::regex;

namespace battle_ships {

	bool GameManager::AddNavalUnit(const string& coordinates, 
								   const NavalUnitType unit_type, 
								   const PlayerNumber player)
	{

		if (!ValidateCommand(coordinates)) return false;
		int whitespace_index = coordinates.find(" ");
		Coordinates start(coordinates.substr(0, whitespace_index));
		Coordinates finish(coordinates.substr(whitespace_index + 1, coordinates.length() - 1));

		switch (player) {
			case PlayerOne: return first_player_.AddNavalUnit(start,finish, unit_type);
			case PlayerTwo: return second_player_.AddNavalUnit(start, finish, unit_type);
		}

	}

	GameResponse GameManager::ExecCommand(const string& command, const PlayerNumber player)
	{
		string cmd_str = command;
		cmd_str = std::regex_replace(cmd_str, std::regex("\\s+$"), std::string(""));
		cmd_str = std::regex_replace(cmd_str, std::regex("^\\s+"), std::string(""));

		if (cmd_str == kCommandDisplay) {
			 string conf = (player == PlayerOne) ? first_player_.Display() : second_player_.Display();
			 return GameResponse(true, conf, false);
		}
		else if (cmd_str == kCommandEraseSonar) {
			return GameResponse(true, "", false);
		}
		else if (cmd_str == kCommandEraseHit) {
			return GameResponse(true, "", false);
		}
		else if (cmd_str == kCommandEraseMiss) {
			return GameResponse(true, "", false);
		}

		// TODO: O uso GameResponse oppure Ecezzione
		if (!ValidateCommand(cmd_str)) return GameResponse(false, "Il Comando non è valido", false);
	
		int whitespace_index = cmd_str.find(" ");
		Coordinates origin(cmd_str.substr(0, whitespace_index));
		Coordinates target(cmd_str.substr(whitespace_index + 1, cmd_str.length() - 1));
		
		bool statusExecution = true;
		switch (player) {
		case PlayerOne: statusExecution = battle_ships::ExecCommand(Command(origin, target), first_player_, second_player_ );
				break;
		case PlayerTwo: statusExecution = battle_ships::ExecCommand(Command(origin, target), second_player_, first_player_);
				break;
		}	

		if (statusExecution) {
			// TODO LOGGER DA SBLOCCARE
		/*	string str_log = "Player" + std::to_string(player) + ":" + cmd_str;
			logger_.Log(str_log);*/
		}

		return GameResponse(statusExecution, "sos", true);
	}

	bool GameManager::IsWinner(const PlayerNumber player)
	{
		switch (player) {
			case PlayerOne: return second_player_.IsLoser();
			case PlayerTwo: return first_player_.IsLoser();
		}
	}

	bool GameManager::ValidateCommand(const string& command) {
		if (command.empty()) return false;
		return regex_match(command, std::regex(R"~([a-zA-Z][0-9]+\s[a-zA-Z][0-9]+)~"));
	}
}
