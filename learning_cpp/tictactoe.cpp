#include "tictactoe.h"

namespace tictactoe
{
	TicTacToe::TicTacToe(bool multiPlayer = false, int difficulty = 1, int size = 3) : multiPlayer{ multiPlayer }, difficulty{ difficulty }, size{ size }
	{
		grid = new SlotState[size * size];
	}

	void TicTacToe::start()
	{
		while (state == GameState::playing)
		{

		}
	}

	void TicTacToe::updateGrid(PlayerInput input)
	{

	}

	PlayerInput TicTacToe::getPlayerInput()
	{

	}

	void TicTacToe::printGrid()
	{

	}

	SlotState* TicTacToe::getRow(int rowIndex)
	{
		SlotState* row{ new SlotState[size] };

		for (int i{}; i < size; ++i)
		{
			row[i] = grid[(size * rowIndex) + i];
		}

		return row;
	}

	SlotState* TicTacToe::getColumn(int columnIndex)
	{
		SlotState* column{ new SlotState[size] };

		for (int i{}; i < size; ++i)
		{
			column[i] = grid[(size * i) + columnIndex];
		}

		return column;
	}

	//returns an array of slots representing either the 
	//slots from the top left to bottom right or top right to bottom left
	SlotState* TicTacToe::getDiagonal(int diagonalIndex)
	{
		SlotState* diagonal{ new SlotState[size] };

		if (diagonal)
		{
			for (int i{}; i < size; ++i)
			{
				diagonal[i] = grid[(size * i) + i];
			}
		}
		else
		{
			for (int i{}; i < size; ++i)
			{
				diagonal[i] = grid[((size - 1) * i) - i];
			}
		}
	}
}