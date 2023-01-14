// Player
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Marco Stefani

#include "player.h"

#include <algorithm>

namespace battle_ships {

    GameResponse Player::AddNavalUnit(const Coordinates& start, 
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
            centre_y = (start.y() + finish.y()) / 2;
            centre_x = start.x();
            cell_length = abs(start.y() - 'A' - finish.y() + 'A') + 1;
        }

        if (!CheckCellLength(unit_type, cell_length))
            return GameResponse(false, "Errore! Il numero di celle per la nave inserita e' sbagliato. Ritenta" , false);
            
        if (!defence_grid_.AddRangeCells(static_cast<char>(unit_type), start, finish))
            return GameResponse(false, "Errore! Tra poppa e prua sono presenti altre navi. Ritenta", false);
    
        Coordinates centre(centre_x, centre_y);
        switch (unit_type) {
        case NavalUnitType::BattleShip :
            naval_units_.emplace_back(new BattleShip(centre, direction));
            break;
        case NavalUnitType::Submarine:
            naval_units_.emplace_back(new Submarine(centre, direction));
            break;
        case NavalUnitType::SupportShip:
            naval_units_.emplace_back(new SupportShip(centre, direction));
            break;
        }

        return GameResponse(true);
    }

    bool Player::IsLoser() const
    {
        return naval_units_.empty();
    }

    string Player::Display() const
    {
        string str_grids = "";

        // stampa dei titoli
        constexpr int cell_width = 4;
        const int grid_width = Grid::kGridSize * cell_width; // kGridSize * cell_width
        string title_defence = "Griglia di difesa";
        string title_attack = "Griglia di attacco";

        int number_of_spaces = grid_width - title_defence.length();
        str_grids += "    "; 
        for (int k = 0; k < number_of_spaces / 2; k++)
            str_grids += " ";
        str_grids += title_defence;
        for (int k = 0; k < number_of_spaces - number_of_spaces / 2; k++)
            str_grids += " ";
        str_grids += "\t      ";

        number_of_spaces = grid_width - title_attack.length();
        for (int k = 0; k < (number_of_spaces / 2); k++)
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


    bool Player::CheckCellLength(const NavalUnitType unit_type, int cell_length) {
        switch (unit_type) {
        case NavalUnitType::BattleShip:
            return cell_length == BattleShip::kSize;
        case NavalUnitType::Submarine:
            return cell_length == Submarine::kSize;
        case NavalUnitType::SupportShip:
            return cell_length == SupportShip::kSize;
        }
        return false;
    }

    GameResponse ExecActionCommand(const Command& command, Player& current_player, Player& enemy_player)
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

        string str_origin = "";
        str_origin += static_cast<char>((origin.y() >= 'J') ? (origin.y() + 2) : origin.y());
        str_origin += std::to_string(origin.x());

        return GameResponse(false, "Coordinata origin [" + str_origin + "] non "
            "corrisponde ad una cella centrale di una nave", false, "", GameResponse::kIncorrectOrigin);
    }

    GameResponse Player::EraseSymbol(char character)
    {
        for (int i = 0; i < Grid::kGridSize; i++)
        {
            for (int j = 0; j < Grid::kGridSize; j++)
            {
                Coordinates coordinates = Coordinates(i + 1, j + 'A');
                if (attack_grid_.GetCellValue(coordinates) == character)
                    attack_grid_.EditCell(' ', coordinates);
            }
        }
        return GameResponse(true, std::string("Sono stati eliminati tutti i caratteri '") + character +
                                  std::string("' dalla griglia di attacco"), false);
    }

}

