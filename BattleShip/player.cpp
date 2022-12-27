#include "player.h";

namespace battle_ships {

    bool Player::ExecCommand(const Command& command)
    {
        Coordinates origin = command.origin();      
        //naval_units.emplace_back(std::make_unique<BattleShip>(origin, true));

        auto iter = std::find_if(naval_units.begin(), naval_units.end(),
             [origin] (const std::unique_ptr<NavalUnit>& a) { 
                 return a->centre_coordinates() == origin;
             });
         
        if (iter != naval_units.end()) {
            return  (*iter)->Action();
        }
         
        return false;
    }

    bool Player::IsLoser()
    {
        /*return submarines_.empty() &&
            battleships_.empty() &&
            supportships_.empty();*/
        return naval_units.empty();
    }
}

