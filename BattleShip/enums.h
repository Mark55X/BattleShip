#ifndef enums_h
#define enums_h

namespace battle_ships {
	enum PlayerNumber
	{
		PlayerOne = 1,
		PlayerTwo
	};

	enum class NavalUnitType
	{
		BattleShip = 'C',
		SupportShip = 'S',
		Submarine = 'E'
	};
}
#endif // enums_h
