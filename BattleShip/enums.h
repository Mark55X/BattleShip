#ifndef enums_h
#define enums_h

// Namespace battle_ships
// Contiene i componenti principali del gioco Battaglia Navale
namespace battle_ships {

	// Enum PlayerNumber
	// Descrizione del numero dei giocatori
	enum PlayerNumber
	{
		PlayerOne = 1,
		PlayerTwo
	};

	// Enum NavalUnitType
	// Contiene la lista del tipo delle unità navali
	// disponibili per il gioco con il relativo carattere nella griglia di difesa
	enum class NavalUnitType
	{
		BattleShip = 'C',
		SupportShip = 'S',
		Submarine = 'E'
	};
}
#endif // enums_h
