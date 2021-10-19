#include <iostream>
#include "tictactoe.h"
#include "strings.h"

namespace tictactoe
{
	TicTacToe::TicTacToe(bool multiPlayer, int difficulty, int size) : multiPlayer{ multiPlayer }, difficulty{ difficulty }, size{ size }
	{
		grid = new SlotState[size * size] {};
		for (int i{}; i < size * size; ++i)
		{
			grid[i] = SlotState::x;
		}

		state = GameState::playing;
	}

	void TicTacToe::start()
	{
		//while (state == GameState::playing)
		//{
			printGrid();
		//}
	}

	void TicTacToe::updateGrid(PlayerInput input)
	{

	}

	PlayerInput TicTacToe::getPlayerInput()
	{
		return PlayerInput{};
	}

	PlayerInput  TicTacToe::getBotInput()
	{
		return PlayerInput{};
	}

	void TicTacToe::printGrid()
	{
		char* string{ new char[] { " " } };
		for (int i{}; i < size; ++i)
		{
			char letter[2]{};
			letter[0] = static_cast<char>(97 + i);
			letter[1] = '\0';

			const char* cat1[]{ string, "   ",  letter, };
			string = catAndDelete(string, cat1, 3);
		}

		const char* cat2[]{ string, "\n\n" };
		string = catAndDelete(string, cat2, 2);

		for (int i{}; i < size; ++i)
		{
			char* itr{ strings::toString(i) };
			const char* cat3[]{ string, itr, "   "};
			string = catAndDelete(string, cat3, 3);
			delete[] itr;

			for (int j{}; j < size; ++j)
			{
				char slot[2]{};

				switch (getRow(i)[j])
				{
				case SlotState::none:
					slot[0] = ' ';
					break;
				case SlotState::x:
					slot[0] = 'x';
					break;
				case SlotState::o:
					slot[0] = 'o';
					break;
				}
				
				slot[1] = '\0';

				const char* cat4[]{ string, slot, j != (size - 1) ? " | " : "" };
				string = catAndDelete(string, cat4, 3);
			}

			const int dashesSize{ size * 4 };
			char* dashes{ new char[dashesSize]{} };
			for (int i{}; i < dashesSize - 1; ++i)
			{
				dashes[i] = '-';
			}
			dashes[dashesSize - 1] = '\0';

			const char* cat5[]{ string, "\n   ", i != size - 1 ? dashes : "", "\n"};
			string = catAndDelete(string, cat5, 4);
			delete[] dashes;
		}

		std::cout << string;
		delete[] string;
	}

	char* TicTacToe::catAndDelete(char* string, const char* cat[], int numStrings)
	{
		char* temp = strings::strCat(cat, numStrings);
		delete[] string;
		string = temp;
		return string;
	}

	SlotState* TicTacToe::getRow(int rowIndex)
	{
		if (rowIndex > size)
		{
			std::cout << "Invalid row index! (returning nullptr)\n";
			return nullptr;
		}

		SlotState* row{ new SlotState[size] };

		for (int i{}; i < size; ++i)
		{
			row[i] = grid[(size * rowIndex) + i];
		}

		return row;
	}

	SlotState* TicTacToe::getColumn(int columnIndex)
	{
		if (columnIndex > size)
		{
			std::cout << "Invalid column index! (returning nullptr)\n";
			return nullptr;
		}

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
		if (diagonalIndex > 2)
		{
			std::cout << "Invalid diagonal index! (returning nullptr)\n";
			return nullptr;
		}

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
				diagonal[i] = grid[(size * (i + 1)) - (i + 1)];
			}
		}

		return diagonal;
	}
}