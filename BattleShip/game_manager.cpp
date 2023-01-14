// GameManager
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#include "game_manager.h"

#include <regex> 

using std::regex;

namespace battle_ships {

	GameManager::GameManager(bool enable_logging) : logger_{ enable_logging } {}

	GameResponse GameManager::AddNavalUnit(const string& coordinates,
										   const NavalUnitType unit_type, 
										   const PlayerNumber player)
	{
		try {

			if (!ValidateCommand(coordinates)) {
				return GameResponse(false, "Comando non valido. Deve essere del formato: XN XN," 
					"dove X e' l'ordinata della griglia (carattere), e N e' l'ascissa della griglia (numero)", false);
			}

			int whitespace_index = coordinates.find(" ");
			Coordinates start(coordinates.substr(0, whitespace_index));	
			Coordinates finish(coordinates.substr(whitespace_index + 1, coordinates.length() - 1));

			ParseCoordinate(start);
			ParseCoordinate(finish);

			GameResponse response(true);
			switch (player) {
			case PlayerOne: response = first_player_.AddNavalUnit(start, finish, unit_type);
				break;
			case PlayerTwo: response = second_player_.AddNavalUnit(start, finish, unit_type);
				break;
			}
			char type = (char)unit_type;
			if (response.status() == true) {
				string str_log = "ADD-";
				str_log.push_back(type);
				str_log += "|Player" + std::to_string(player) + ":" + coordinates;
				logger_.Log(str_log);
			}

			return response;
		}
		catch (const std::exception& ex) {
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
			return (player == PlayerOne) ? first_player_.EraseSymbol(kSonarCharacter) : second_player_.EraseSymbol(kSonarCharacter);
		}
		else if (cmd_str == kCommandEraseHit) {
			return (player == PlayerOne) ? first_player_.EraseSymbol(kHitCharacter) : second_player_.EraseSymbol(kHitCharacter);
		}
		else if (cmd_str == kCommandEraseMiss) {
			return (player == PlayerOne) ? first_player_.EraseSymbol(kMissCharacter) : second_player_.EraseSymbol(kMissCharacter);
		}

		if (!ValidateCommand(cmd_str)) {
			return GameResponse(false, "Comando non valido.", false);
		}

		try {
			int whitespace_index = cmd_str.find(" ");
			Coordinates origin(cmd_str.substr(0, whitespace_index));
			Coordinates target(cmd_str.substr(whitespace_index + 1, cmd_str.length() - 1));
			ParseCoordinate(origin);
			ParseCoordinate(target);

			GameResponse response(true);
			switch (player) {
			case PlayerOne: response = battle_ships::ExecActionCommand(Command(origin, target), first_player_, second_player_);
				break;
			case PlayerTwo: response = battle_ships::ExecActionCommand(Command(origin, target), second_player_, first_player_);
				break;
			}

			if (response.status()) {
			    string str_log = "EXEC|Player" + std::to_string(player) + ":" + cmd_str;
				logger_.Log(str_log);
			}

			return response;
		}
		catch (const std::exception& ex) {
			return GameResponse(false, ex.what(), false);
		}
		
	}

	bool GameManager::IsWinner(const PlayerNumber player)
	{
		switch (player) {
			case PlayerOne: return second_player_.IsLoser();
			case PlayerTwo: return first_player_.IsLoser();
		}
		return false;
	}

	string GameManager::GetLogFileName()
	{
		return logger_.file_path();
	}

	bool GameManager::ValidateCommand(const string& command) {
		if (command.empty()) return false;
		return regex_match(command, std::regex(R"~([a-zA-Z][0-9]+\s[a-zA-Z][0-9]+)~"));
	}

	void GameManager::ParseCoordinate(Coordinates& coordinates) {
		if (coordinates.y() >= 'L')
			coordinates.set_y(coordinates.y() - 2);
	}
}
