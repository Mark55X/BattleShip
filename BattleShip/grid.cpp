// Grid
// Style Guide: https://google.github.io/styleguide/cppguide.html
// Author: Giulia Selvestrel

#include "grid.h"

#include <iostream>

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

	void Grid::RemoveRangeCells(const Coordinates& start, const Coordinates& finish)
	{
		ValidateCoordinates(start);
		ValidateCoordinates(finish);

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

	}

	bool Grid::MoveRangeCells(const Coordinates& origin_start, const Coordinates& origin_finish, 
							  const Coordinates& target_start, const Coordinates& target_finish)
	{
		ValidateCoordinates(origin_start);
		ValidateCoordinates(origin_finish);
		
		if (origin_start.x() != origin_finish.x() && origin_start.y() != origin_finish.y()) // non esiste move in obliquo
			return false;
	
		if (origin_start.y() == origin_finish.y()) // orizzontale
		{
			if (!CheckRangeCoordinates(target_start, target_finish, origin_start.x(), origin_finish.x(), origin_start.y())) {
				return false;
			}

			if (target_start.y() != target_finish.y())
				return false;
			int length = abs(origin_start.x() - origin_finish.x()) + 1;
			if ((abs(target_start.x() - target_finish.x()) + 1) != length)
				return false;

			char value = ' ';
			if (origin_start.x() > origin_finish.x()) {

				for (int i = 0; i < length; i++)
				{
					value = GetCellValue(Coordinates(origin_start.x() - i, origin_start.y()));
					EditCell(value, Coordinates(target_start.x() - i, target_start.y()));
					if (origin_start != target_start) {
						EditCell(' ', Coordinates(origin_start.x() - i, origin_start.y()));
					}
				}

			}
			else {
				for (int i = 0; i < length; i++)
				{
					value = GetCellValue(Coordinates(origin_start.x() + i, origin_start.y()));
					EditCell(value, Coordinates(target_start.x() + i, target_start.y()));
					if (origin_start != target_start) {
						EditCell(' ', Coordinates(origin_start.x() + i, origin_start.y()));
					}
				}
			}		
		}
		else // verticale
		{
			if (!CheckRangeCoordinates(target_start, target_finish, origin_start.y(), origin_finish.y(), origin_start.x())) {
				return false;
			}

			if (target_start.x() != target_finish.x())
				return false;
			int length = abs(origin_start.y() - origin_finish.y()) + 1;
			if ((abs(target_start.y() - target_finish.y()) + 1) != length)
				return false;

			char value = ' ';
			if (origin_start.y() > origin_finish.y()) {

				for (int i = 0; i < length; i++)
				{
					value = GetCellValue(Coordinates(origin_start.x(), origin_start.y() - i));
					EditCell(value, Coordinates(target_start.x(), target_start.y() - i));				
					if (origin_start != target_start) {
						EditCell(' ', Coordinates(origin_start.x(), origin_start.y() - i));
					}
				}

			}
			else {

				for (int i = 0; i < length; i++)
				{
					value = GetCellValue(Coordinates(origin_start.x(), origin_start.y() + i));
					EditCell(value, Coordinates(target_start.x(), target_start.y() + i));
					if (origin_start != target_start) {
						EditCell(' ', Coordinates(origin_start.x(), origin_start.y() + i));
					}
				}

			}

			
		}

		return true;
	}

	void Grid::EditCell(char value, const Coordinates& cell)
	{
		ValidateCoordinates(cell);

		int grid_x = GetCellCoordinateX(cell);
		int grid_y = GetCellCoordinateY(cell);

		grid_[grid_y][grid_x] = value;
	}

	char Grid::GetCellValue(const Coordinates& coordinates)
	{
		ValidateCoordinates(coordinates);
		
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
				if (i >= 9) {
					str_grid += static_cast<char>('A' + i + 2);
				}
				else {
					str_grid += static_cast<char>('A' + i);
				}
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
		char y = coordinates.y();
		char x = coordinates.x();

		if (!(x >= 1 &&
			x <= kGridSize &&
			y >= 'A' &&
			y < 'A' + kGridSize )) {
			
			string str_coordinates = "";
			str_coordinates += static_cast<char>((coordinates.y() >= 'J') ? (coordinates.y() + 2) : coordinates.y());
			str_coordinates += std::to_string(coordinates.x());

			throw InvalidCellGridException("Coordinata [" + str_coordinates + "] non valida per la griglia [X: 1-12, Y: A-N]");
		}	
	}

	bool Grid::CheckRangeCoordinates(const Coordinates& start, const Coordinates& finish, 
									  int ignore_start,  int ignore_finish, int fixed_coordinate) const
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

				temp = ignore_start;
				ignore_start = ignore_finish;
				ignore_finish = temp;
			}

			for (int i = grid_start_y; i <= grid_finish_y; i++)
			{
				if (grid_[i][grid_start_x] != ' ') {
					if (fixed_coordinate == -1)
						return false;

					if(!(grid_start_x == (fixed_coordinate - 1) && i >= (ignore_start - 'A') && i <= (ignore_finish - 'A')))
						return false;
				}
			}
		}
		else {

			if (grid_start_x > grid_finish_x) {
				int temp = grid_finish_x;
				grid_finish_x = grid_start_x;
				grid_start_x = temp;

				temp = ignore_start;
				ignore_start = ignore_finish;
				ignore_finish = temp;
			}
			for (int i = grid_start_x; i <= grid_finish_x; i++)
			{
				if (grid_[grid_start_y][i] != ' ') {
					if (fixed_coordinate == -1)
						return false;

					if (!(grid_start_y == (fixed_coordinate - 'A') && i >= (ignore_start - 1) && i <= (ignore_finish - 1)))
						return false;
				}

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

