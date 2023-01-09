// Logger Header
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#ifndef logger_h
#define logger_h

#include <string>
#include <fstream>

#include "player.h"

using std::string;
using std::ofstream;

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Classe Logger
	// All'inizializzazione gestisce un file di log
	// Invarianti:
	// 1. Il nome di un file di log contiene il timestamp del momento in cui è stato creato l'oggetto
	//    in modo da avere nella stessa cartella più file di diverse giocate
	class Logger {

	public:
		// Costruttore Logger
		// Accetta un argomento string che corrisponde al base_path dove verrebbe creato il file di log
		// Se non esiste viene lanciata una IllegalPathException
		Logger(bool enable_logging = true, 
			   const string& base_path = "");

		// Distruttore Logger
		// Chiude lo steam sul file
		~Logger();

		// Funzione Log
		// Si occupa di stampare su file la stringa passata come parametro 
		// seguito da un carattere di escape di nuova linea (\n)
		bool Log(const string& log_str);

		// setter
		void set_enable_logging(bool enable) { enable_logging_ = enable; }
		string file_path() { return log_path_; }

		// Eccezione IllegalPathException
		// Descrive l'evento di 'Percorso non disponibile/non esistente' nel
		// caso di creazione di file di log su tale percorso
		class IllegalPathException : public std::invalid_argument {
		public:
			IllegalPathException(string msg) : std::invalid_argument(msg) {}
		};

		
	private:
		// Stream verso il file di log
		ofstream file_;
		bool enable_logging_;
		string log_path_;

		// Funzione CheckPath
		// Verifica che il Path passato come argomento esista
		bool CheckPath(const string& path);

	};


} // namespace battle_ships

#endif // logger_h

