#include "player.h"

#include <memory>

#include "battle_ship.h"
#include "submarine.h"
#include "support_ship.h"


namespace battle_ships {

    bool Player::AddNavalUnit(const Coordinates& start, 
                              const Coordinates& finish, 
                              const NavalUnitType unit_type)
    {
        bool direction = start.y() == finish.y();
        int centre_x, cell_length;
        char centre_y;
        if (direction) {
            centre_x = (start.x() + finish.x()) / 2;
            centre_y = start.y();
            cell_length = abs(start.x() - finish.x()) + 1;
        }
        else {
            centre_x = (start.y() + finish.y()) / 2;
            centre_y = start.x();
            cell_length = abs(start.y() - 'A' - finish.y() + 'A') + 1;
        }

        if (!CheckCellLength(unit_type, cell_length))
            return false;

        if (defence_grid_.AddRangeCells(static_cast<char>(unit_type), start, finish) == false)
            return false;
    
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

   /* bool Player::ExecCommand(const Command& command, Grid& enemy_defence_grid)
    {
        Coordinates origin = command.origin();         

        auto iter = std::find_if(naval_units_.begin(), naval_units_.end(),
             [origin] (const std::unique_ptr<NavalUnit>& a) {
                 return a->centre_coordinates() == origin;
             });
         
        if (iter != naval_units_.end()) {
            return (*iter)->Action(command, defence_grid_, enemy_defence_grid, attack_grid_, *this);
        }
         
        return false;
    }*/

    bool Player::IsLoser()
    {
        /*return submarines_.empty() &&
            battleships_.empty() &&
            supportships_.empty();*/
        return naval_units_.empty();
    }

    string Player::Display() const
    {
        return string();
    }

    bool Player::CheckCellLength(const NavalUnitType unit_type, int cell_length) {
        switch (unit_type) {
        case NavalUnitType::BattleShip:
            return cell_length == BattleShip::kSize;
        case NavalUnitType::Submarine:
            return cell_length == Submarine::kSize;
        case NavalUnitType::SupportShip:
            return cell_length == SupportShip::kSize;
        }
    }

    bool ExecCommand(const Command& command, Player& current_player, Player& enemy_player)
    {
        Coordinates origin = command.origin();

        auto& current_units = current_player.naval_units();
        auto iter = std::find_if(current_units.begin(), current_units.end(),
            [origin](const std::unique_ptr<NavalUnit>& unit) {
                return unit->centre_coordinates() == origin;
            });

        if (iter != current_units.end()) {
           return (*iter)->Action(command, current_player, enemy_player);
        }

        return false;
    }
}

