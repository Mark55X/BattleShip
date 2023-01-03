#include "grid.h"

namespace battle_ships {

	Grid::Grid()
	{
		for (int i = 0; i < kGridSize; i++)
		{
			for (int j = 0; j < kGridSize; j++)
			{
				grid_[i][j] = ' ';
			}
		}
	}

	bool Grid::AddRangeCells(char value, const Coordinates& start, const Coordinates& finish)
	{
		if (!CheckRangeCoordinates(start,finish)) {
			return false;
		}
		
		int grid_start_x = GetCellCoordinateX(start);
		int grid_start_y = GetCellCoordinateY(start);

		int grid_finish_x = GetCellCoordinateX(finish);
		int grid_finish_y = GetCellCoordinateY(finish);

		if (grid_start_x == grid_finish_x) {

			if (grid_start_y > grid_finish_y) {
				int temp = grid_finish_y;
				grid_finish_y = grid_start_y;
				grid_start_y = temp;
			}

			for (int i = grid_start_y; i <= grid_finish_y; i++)
			{
				grid_[i][grid_start_x] = value;
			}
		}
		else {

			if (grid_start_x > grid_finish_x) {
				int temp = grid_finish_x;
				grid_finish_x = grid_start_x;
				grid_start_x = temp;
			}

			for (int i = grid_start_x; i <= grid_finish_x; i++)
			{
				grid_[grid_start_y][i] = value;				
			}
		}

		return true;
	}

	bool Grid::RemoveRangeCells(const Coordinates& start, const Coordinates& finish)
	{
		int grid_start_x = GetCellCoordinateX(start);
		int grid_start_y = GetCellCoordinateY(start);

		int grid_finish_x = GetCellCoordinateX(finish);
		int grid_finish_y = GetCellCoordinateY(finish);

		if (grid_start_x == grid_finish_x) {

			if (grid_start_y > grid_finish_y) {
				int temp = grid_finish_y;
				grid_finish_y = grid_start_y;
				grid_start_y = temp;
			}

			for (int i = grid_start_y; i <= grid_finish_y; i++)
			{
				grid_[i][grid_start_x] = ' ';
			}
		}
		else {

			if (grid_start_x > grid_finish_x) {
				int temp = grid_finish_x;
				grid_finish_x = grid_start_x;
				grid_start_x = temp;
			}
			for (int i = grid_start_x; i <= grid_finish_x; i++)
			{
				grid_[grid_start_y][i] = ' ';
			}
		}

		return true;
	}

	bool Grid::EditCell(char value, const Coordinates& cell)
	{
		ValidateCoordinates(cell);

		int grid_x = GetCellCoordinateX(cell);
		int grid_y = GetCellCoordinateY(cell);

		grid_[grid_y][grid_x] = value;
		return true;
	}

	char Grid::GetCellValue(const Coordinates& coordinates)
	{
		ValidateCoordinates(coordinates);
		/*if ((coordinates.x() <= 0 || coordinates.x() > kGridSize)
			&& (coordinates.y() < 'A' || coordinates.y() > ('A' + kGridSize)))
			 throw InvalidCellGridException("InvalidCellGridException - Coordinata non valida per la griglia");*/

		int grid_x = GetCellCoordinateX(coordinates);
		int grid_y = GetCellCoordinateY(coordinates);

		return grid_[grid_y][grid_x];
	}

	string Grid::Display() const
	{
		string str_grid = "    -------------------------------------------------\n";
		constexpr int cell_width = 4;
		for (int i = 0; i <= kGridSize; i++)
		{
			if (i != kGridSize)
			{
				str_grid += "  ";
				str_grid += static_cast<char>('A' + i);
				str_grid += " ";
			}
			else
			{
				str_grid += "     ";
			}
			
			for (int j = 0; j < kGridSize; j++)
			{
				if (i != kGridSize)
				{
					str_grid += "| ";
					str_grid += grid_[i][j];
					str_grid += " ";
				}
				else
				{
					int number_of_spaces = cell_width - (std::to_string(j + 1)).length();
					for(int k = 0; k < number_of_spaces/2; k++)
						str_grid += " ";
					str_grid += std::to_string(j+1);
					for (int k = 0; k < cell_width - (std::to_string(j + 1)).length() - number_of_spaces / 2; k++)
						str_grid += " ";
				}
			}
			if (i != kGridSize)
			{
				str_grid += "|\n";
				str_grid += "    -------------------------------------------------\n";
			}
			else
				str_grid += "\n";
		}

		return str_grid;
	}

	void Grid::ValidateCoordinates(const Coordinates& coordinates) const
	{
		if (!(coordinates.x() >= 1 &&
			coordinates.x() <= kGridSize &&
			coordinates.y() >= 'A' &&
			coordinates.y() <= 'A' + kGridSize)) {
			throw InvalidCellGridException("InvalidCellGridException - Coordinata non valida per la griglia [X: 1-12, Y: A-N]");
		}	
	}

	bool Grid::CheckRangeCoordinates(const Coordinates& start, const Coordinates& finish) const
	{
		ValidateCoordinates(start);
		ValidateCoordinates(finish);

		int grid_start_x = GetCellCoordinateX(start);
		int grid_start_y = GetCellCoordinateY(start);

		int grid_finish_x = GetCellCoordinateX(finish);
		int grid_finish_y = GetCellCoordinateY(finish);

		if (grid_start_x != grid_finish_x && grid_start_y != grid_finish_y)
			return false;

		if (grid_start_x == grid_finish_x) {

			if (grid_start_y > grid_finish_y) {
				int temp = grid_finish_y;
				grid_finish_y = grid_start_y;
				grid_start_y = temp;
			}

			for (int i = grid_start_y; i <= grid_finish_y; i++)
			{
				if (grid_[i][grid_start_x] != ' ')
					return false;
			}
		}
		else {

			if (grid_start_x > grid_finish_x) {
				int temp = grid_finish_x;
				grid_finish_x = grid_start_x;
				grid_start_x = temp;
			}
			for (int i = grid_start_x; i <= grid_finish_x; i++)
			{
				if (grid_[grid_start_y][i] != ' ')
					return false;
			}
		}

		return true;
	}

	int Grid::GetCellCoordinateX(const Coordinates& coordinates) const
	{
		return coordinates.x() - 1;
	}

	int Grid::GetCellCoordinateY(const Coordinates& coordinates) const
	{
		return coordinates.y() - 'A';
	}

}

