#include "computer_player.h"

namespace battle_ships
{
	// per aggiungere una nave nella griglia
	// con CoordinatesGenerator genero delle coordinate casuali nella griglia (poppa)
	// devo ricevere il tipo di nave e creare un vector di 4 elementi con le possibili
	// posizioni della prua della nave, tra cui si sceglie casualmente per poi mandarle a
	// AddNavalunit di GameManager. Questo processo deve cotninuare finch� non riesco ad
	// aggiungere la nave (AddNavalUnit restituisce true) e deve essere ripetuto
	// per tutte le navi da inserire

	int ComputerPlayer::NumberGenerator(const int n)
	{
		std::uniform_int_distribution<> dist(0, n - 1);
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine gen(seed);
		int random = dist(gen);

		return random;
	}

	Coordinates ComputerPlayer::CoordinatesGenerator(const int grid_size)
	{
		int x = NumberGenerator(grid_size) + 1;
		char y = static_cast<char>(NumberGenerator(grid_size)) + 'A';
		return Coordinates(x, y);
	}

	string ComputerPlayer::InsertCoordinatesGenerator(const NavalUnitType unit_type)
	{
		string couple_coordinates = "";

		Coordinates stern = CoordinatesGenerator(kGridSize);
		
		int ship_dimension = 0;

		switch (unit_type) {
		case NavalUnitType::BattleShip:
			ship_dimension = 5;
			break;
		case NavalUnitType::SupportShip:
			ship_dimension = 3;
			break;
		case NavalUnitType::Submarine:
			ship_dimension = 1;
			break;
		}

		// coordinate delle possibili prue data la poppa, sapendo la lunghezza della nave
		// caso 1: nave orizzontale, prua > poppa -> y_prua= y_poppa, x_prua = x_poppa + ship_dimension
		// caso 2: nave orizzontale, prua < poppa -> y_prua= y_poppa, x_prua = x_poppa - ship_dimension
		// caso 3: nave verticale, prua > poppa -> x_prua= x_poppa, y_prua = y_poppa + ship_dimension
		// caso 3: nave verticale, prua < poppa -> x_prua= x_poppa, y_prua = y_poppa - ship_dimension
		// alcune coppie di coordinate potrebbero non essere valide, ma in quel caso AddNavalUnit
		// restituisce false e si riprova

		vector<Coordinates> possible_bows = { Coordinates(stern.x() + (ship_dimension - 1), stern.y()),
								 Coordinates(stern.x() - (ship_dimension - 1), stern.y()),
								 Coordinates(stern.x(), static_cast<char>(stern.y() + (ship_dimension - 1))),
								 Coordinates(stern.x(), static_cast<char>(stern.y() - (ship_dimension - 1))) };

		int casual_index_bows = NumberGenerator(possible_bows.size());

		Coordinates bow = possible_bows[casual_index_bows];

		couple_coordinates += to_string(stern);
		couple_coordinates += " ";
		couple_coordinates += to_string(bow);

		return couple_coordinates;
	}

	// se l'inserimento va a buon fine (AddNavalUnit resituisce true) bisogna inserire le coordinate
	// del centro della nave nel vector ships_centre_coordinates_, che verr� poi usato quando sar� il
	// momento di giocare per scegliere casualmente una nave a cui far compiere la sua azione
	bool ComputerPlayer::MemorizeCentreCoordinates(string& couple_coordinates)
	{
		int whitespace_index = couple_coordinates.find(" ");
		Coordinates start(couple_coordinates.substr(0, whitespace_index));
		Coordinates finish(couple_coordinates.substr(whitespace_index + 1, couple_coordinates.length() - 1));
		
		int x_centre = (start.x() + finish.x())/2;
		char y_centre = (start.y() + finish.y())/2;

		Coordinates centre(x_centre, y_centre);

		ships_centre_coordinates_.push_back(centre);

		return true;
	}

	string ComputerPlayer::ActionCoordinatesGenerator()
	{
		string couple_coordinates = "";
		
		int num_ship_to_activate = NumberGenerator(ships_centre_coordinates_.size());
		Coordinates coord_ship_to_activate = ships_centre_coordinates_[num_ship_to_activate];

		Coordinates coord_target = CoordinatesGenerator(kGridSize);

		couple_coordinates += to_string(coord_ship_to_activate);
		couple_coordinates += " ";
		couple_coordinates += to_string(coord_target);

		return couple_coordinates;
	}

	bool ComputerPlayer::RemoveCoordinates(Coordinates& coordinates)
	{
		auto it = find(ships_centre_coordinates_.begin(), ships_centre_coordinates_.end(), coordinates);
		ships_centre_coordinates_.erase(it);
		return true;
	}

	bool ComputerPlayer::SetCoordinates(Coordinates& old_coordinates, Coordinates& new_coordinates)
	{
		RemoveCoordinates(old_coordinates);
		ships_centre_coordinates_.push_back(new_coordinates);
		return true;
	}

}
