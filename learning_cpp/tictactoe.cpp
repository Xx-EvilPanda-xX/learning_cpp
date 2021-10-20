#include <iostream>
#include "tictactoe.h"
#include "strings.h"
#include "getinput.h"

namespace tictactoe
{
	TicTacToe::TicTacToe(bool multiPlayer, int difficulty, int size) : multiPlayer{ multiPlayer }, difficulty{ difficulty }, size{ size }
	{
		grid = new SlotState[size * size] {};
		for (int i{}; i < size * size; ++i)
		{
			grid[i] = SlotState::none;
		}

		char* type;
		playerType = SlotState::none;

		while (playerType == SlotState::none)
		{
			type = { input::getStringInput("Please enter a character ('x' or 'o') for your player type: ") };

			switch (*type)
			{
			case 'x':
				playerType = SlotState::x;
				break;
			case 'o':
				playerType = SlotState::o;
				break;
			default:
				std::cout << "Invalid input!\n";
				playerType = SlotState::none;
				break;
			}
		}

		delete[] type;

		state = GameState::playing;
	}

	void TicTacToe::start()
	{
		//while (state == GameState::playing)
		//{
			PlayerInput playerInput{ getPlayerInput() };
			updateGrid(playerInput);

			PlayerInput botInput{ getBotInput() };
			updateGrid(botInput);

			printGrid();
		//}
	}

	void TicTacToe::updateGrid(PlayerInput input)
	{
		grid[input.index] = input.slot;
	}

	PlayerInput TicTacToe::getPlayerInput()
	{

		return PlayerInput{ 0, SlotState::o };
	}

	PlayerInput  TicTacToe::getBotInput()
	{
		return PlayerInput{ 1, SlotState::x };
	}

	void TicTacToe::printGrid()
	{
		char* string{ new char[] { " " } };
		for (int i{}; i < size; ++i)
		{
			char letter[]{ static_cast<char>(97 + i), '\0' };
			const char* cat1[]{ string, "   ",  letter, };
			catAndDelete(string, cat1, 3);
		}

		const char* cat2[]{ string, "\n\n" };
		catAndDelete(string, cat2, 2);

		for (int i{}; i < size; ++i)
		{
			char* itr{ strings::toString(i) };
			const char* cat3[]{ string, itr, "   "};
			catAndDelete(string, cat3, 3);
			delete[] itr;

			for (int j{}; j < size; ++j)
			{
				char slot[2]{};

				SlotState* row{ getRow(i) };
				switch (row[j])
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
				delete[] row;
				
				slot[1] = '\0';

				const char* cat4[]{ string, slot, j != (size - 1) ? " | " : "" };
				catAndDelete(string, cat4, 3);
			}

			const int dashesSize{ size * 4 };
			char* dashes{ new char[dashesSize]{} };
			for (int i{}; i < dashesSize - 1; ++i)
			{
				dashes[i] = '-';
			}
			dashes[dashesSize - 1] = '\0';

			const char* cat5[]{ string, "\n   ", i != size - 1 ? dashes : "", "\n"};
			catAndDelete(string, cat5, 4);
			delete[] dashes;
		}

		std::cout << string;
		delete[] string;
	}

	void TicTacToe::catAndDelete(char*& string, const char* cat[], int numStrings)
	{
		char* temp = strings::strCat(cat, numStrings);
		delete[] string;
		string = temp;
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