#include "game_manager.h"

#include <regex> 

using std::regex;

namespace battle_ships {

	GameResponse GameManager::AddNavalUnit(const string& coordinates, 
										   const NavalUnitType unit_type, 
										   const PlayerNumber player)
	{
		try {

			if (!ValidateCommand(coordinates)) {
				return GameResponse(false, "Comando non valido. Deve essere del formato: XN XN," 
					"dove X � l'ordinata della griglia (carattere), e N � l'ascissa della griglia (numero)", false);
			}

			int whitespace_index = coordinates.find(" ");
			Coordinates start(coordinates.substr(0, whitespace_index));
			Coordinates finish(coordinates.substr(whitespace_index + 1, coordinates.length() - 1));

			switch (player) {
			case PlayerOne: return first_player_.AddNavalUnit(start, finish, unit_type);
			case PlayerTwo: return second_player_.AddNavalUnit(start, finish, unit_type);
			}
		}
		catch (std::exception ex) {
			return GameResponse(false, ex.what(), false);
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
			return (player == PlayerOne) ? first_player_.EraseChar(kSonarCharacter) : second_player_.EraseChar(kSonarCharacter);
		}
		else if (cmd_str == kCommandEraseHit) {
			return (player == PlayerOne) ? first_player_.EraseChar(kHitCharacter) : second_player_.EraseChar(kHitCharacter);
		}
		else if (cmd_str == kCommandEraseMiss) {
			return (player == PlayerOne) ? first_player_.EraseChar(kMissCharacter) : second_player_.EraseChar(kMissCharacter);
		}

		if (!ValidateCommand(cmd_str)) {
			return GameResponse(false, "Comando non valido.", false);
		}

		try {
			int whitespace_index = cmd_str.find(" ");
			Coordinates origin(cmd_str.substr(0, whitespace_index));
			Coordinates target(cmd_str.substr(whitespace_index + 1, cmd_str.length() - 1));

			GameResponse response(true);
			switch (player) {
			case PlayerOne: response = battle_ships::ExecCommand(Command(origin, target), first_player_, second_player_);
				break;
			case PlayerTwo: response = battle_ships::ExecCommand(Command(origin, target), second_player_, first_player_);
				break;
			}

			if (response.status()) {
				// TODO LOGGER DA SBLOCCARE
			    string str_log = "Player" + std::to_string(player) + ":" + cmd_str;
				logger_.Log(str_log);
			}

			return response;
		}
		catch (std::exception exception) {
			return GameResponse(false, exception.what(), false);

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
