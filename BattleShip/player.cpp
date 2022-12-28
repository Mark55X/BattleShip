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
    string Player::Display() const
    {
        string str_grids = "";

        // stampa dei titoli
        constexpr int grid_width = 48; // kGridSize * cell_width
        string title_defence = "Griglia di difesa";
        string title_attack = "Griglia di attacco";

        int number_of_spaces = grid_width - title_defence.length();
        str_grids += "    "; 
        for (int k = 0; k < number_of_spaces / 2; k++)
            str_grids += " ";
        str_grids += title_defence;
        for (int k = 0; k < number_of_spaces - number_of_spaces / 2; k++)
            str_grids += " ";
        str_grids += "\t\t    ";

        number_of_spaces = grid_width - title_attack.length();
        for (int k = 0; k < number_of_spaces / 2; k++)
            str_grids += " ";
        str_grids += title_attack;
        str_grids += '\n';
        
        string str_defence_grid = defence_grid_.Display();
        string str_attack_grid = attack_grid_.Display();

        // stampa delle griglie

        // devo prendere la prima riga di str_defence_grid e sostituire il \n con
        // un tab seguito dalla prima riga di str_attack_grid (fino al |n compreso)
        // poi ripetere il processo per ogni riga, quindi in totale 13 volte (tutte
        // le righe di gioco più la riga degli indici x

        int pos_return_defence = -1;
        int pos_return_attack = -1;

        for (int i = 0; i <= 26; i++)
        {
            pos_return_defence = str_defence_grid.find('\n');
            str_grids += str_defence_grid.substr(0, pos_return_defence);
            str_defence_grid.erase(0, pos_return_defence + 1);

            str_grids += '\t';

            pos_return_attack = str_attack_grid.find('\n');
            str_grids += str_attack_grid.substr(0, pos_return_attack + 1);
            str_attack_grid.erase(0, pos_return_attack + 1);
        }

        return str_grids;
    }
}

