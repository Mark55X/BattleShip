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

	bool GameManager::ExecCommand(const string& command, const PlayerNumber player)
	{
		string cmd_str = command;
		cmd_str = std::regex_replace(cmd_str, std::regex("\\s+$"), std::string(""));
		cmd_str = std::regex_replace(cmd_str, std::regex("^\\s+"), std::string(""));

		// TODO LOGGER DA SBLOCCARE
	/*	string str_log = "Player" + std::to_string(player) + ":" + cmd_str;
		logger_.Log(str_log);*/

		if (cmd_str == kCommandDisplay) {
			return false;
		}
		else if (cmd_str == kCommandEraseSonar) {
			return false;
		}
		else if (cmd_str == kCommandEraseHit) {
			return false;
		}
		else if (cmd_str == kCommandEraseMiss) {
			return false;
		}

		if (!ValidateCommand(cmd_str)) return false;
		int whitespace_index = cmd_str.find(" ");
		Coordinates origin(cmd_str.substr(0, whitespace_index));
		Coordinates target(cmd_str.substr(whitespace_index + 1, cmd_str.length() - 1));
		
		switch (player) {
			case PlayerOne: return first_player_.ExecCommand(Command(origin, target));
			case PlayerTwo: return second_player_.ExecCommand(Command(origin, target));
		}	
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
