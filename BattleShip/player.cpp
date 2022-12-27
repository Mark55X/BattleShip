#include "player.h";

namespace battle_ships {

    bool Player::AddNavalUnit(const Coordinates& start, 
                              const Coordinates& finish, 
                              const NavalUnitType unit_type)
    {
        if (defence_grid_.AddRangeCells(unit_type, start, finish) == false)
            return false;

        switch (unit_type) {
        case NavalUnitType::BattleShip :
            naval_units_.emplace_back(std::make_unique<BattleShip>(origin, true));
            break;
        case NavalUnitType::Submarine:
            break;
        case NavalUnitType::SupportShip:
            break;
        }

        return false;
    }

    bool Player::ExecCommand(const Command& command)
    {
        Coordinates origin = command.origin();         

        auto iter = std::find_if(naval_units_.begin(), naval_units_.end(),
             [origin] (const std::unique_ptr<NavalUnit>& a) { 
                 return a->centre_coordinates() == origin;
             });
         
        if (iter != naval_units_.end()) {
            return  (*iter)->Action();
        }
         
        return false;
    }

    bool Player::IsLoser()
    {
        /*return submarines_.empty() &&
            battleships_.empty() &&
            supportships_.empty();*/
        return naval_units_.empty();
    }
}

