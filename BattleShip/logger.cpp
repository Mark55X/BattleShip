// Logger Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#include "logger.h"

#include<ctime>
#include <sys/stat.h>
#include <stdlib.h>

using std::ifstream;

namespace battle_ships {

	Logger::Logger(bool enable_logging, 
		           const string& base_path) : enable_logging_ {enable_logging}
	{
		
		if(!CheckPath(base_path))
			throw IllegalPathException("IllegalPathException - BasePath non corretta");

		std::time_t timestamp = std::time(nullptr);
		string path = base_path + "log-BattleShip" + std::to_string(timestamp) + ".txt";

		log_path_ = path;
		if (enable_logging_) {
			file_.open(path);
		}		
	}

	Logger::~Logger()
	{
		if (file_.good() && file_.is_open()) {
			file_.flush();
			file_.close();
		}
	}

	bool Logger::Log(const string& log_str)
	{
		if (enable_logging_ == false) return true;
			
		try {

			if (!file_.is_open()) {
				file_.open(log_path_);
			}

			if (!file_.good()) return false;

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
