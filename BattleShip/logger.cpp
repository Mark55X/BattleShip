// Logger Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#include "logger.h"

#include<ctime>
#include <sys/stat.h>

using std::ifstream;

namespace battle_ships {

	Logger::Logger(const string& base_path) 
	{
		if(!CheckPath(base_path))
			throw IllegalPathException("IllegalPathException - BasePath non corretta");

		std::time_t timestamp = std::time(nullptr);
		string path = base_path + "log-BattleShip" + std::to_string(timestamp) + ".txt";
		file_.open(path);
	}

	Logger::~Logger()
	{
		if (file_.good()) {
			file_.flush();
			file_.close();
		}
	}

	bool Logger::Log(const string& log_str)
	{
		if (!file_.good()) return false;
			
		try {
			file_ << log_str << "\n";
			file_.flush();
		}
		catch (ifstream::failure& ex) {
			return false;
		}

		return true;
	}

	bool Logger::CheckPath(const string& path) {
		struct stat buffer;
		return path == "" || stat(path.c_str(), &buffer) == 0;
	}
}
