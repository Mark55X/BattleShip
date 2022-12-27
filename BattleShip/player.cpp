#include "player.h"

#include <memory>

namespace battle_ships {

    bool Player::AddNavalUnit(const Coordinates& start, 
                              const Coordinates& finish, 
                              const NavalUnitType unit_type)
    {
        if (defence_grid_.AddRangeCells(static_cast<char>(unit_type), start, finish) == false)
            return false;

        bool direction = start.y() == finish.y();
        int centre_x;
        char centre_y;
        if (direction) {
            centre_x = (start.x() + finish.x())/2;
            centre_y = start.y();
        }         
        else {
            centre_x = (start.y() + finish.y()) / 2;
            centre_y = start.x();
        }

        Coordinates centre(centre_x, centre_y);
        switch (unit_type) {
        case NavalUnitType::BattleShip :
            naval_units_.emplace_back(std::make_unique<BattleShip>(centre, direction));
            break;
        case NavalUnitType::Submarine:
            naval_units_.emplace_back(std::make_unique<Submarine>(centre, direction));
            break;
        case NavalUnitType::SupportShip:
            naval_units_.emplace_back(std::make_unique<SupportShip>(centre, direction));
            break;
        }

        return true;
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

