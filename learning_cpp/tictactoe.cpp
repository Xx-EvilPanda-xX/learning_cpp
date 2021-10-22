#include <iostream>
#include <cassert>
#include "tictactoe.h"
#include "player.h"
#include "strings.h"
#include "getinput.h"

namespace tictactoe
{
	TicTacToe::TicTacToe(const int size) : m_Size{ size }
	{
		if (size > 26 || size < 0)
		{
			std::cout << "Size must be greater than 0 and 26 or less";
			std::exit(-1);
		}

		m_Grid = new SlotState[m_Size * m_Size]{};
		for (int i{}; i < m_Size * m_Size; ++i)
		{
			m_Grid[i] = SlotState::none;
		}

		char* type;
		player::PlayerType playerType1{};
		player::PlayerType playerType2{};
		bool invalid{ true };

		while (invalid)
		{
			type = input::getStringInput("\n\nPlayer 1, please enter a character ('x' or 'o') for your player type: ");

			switch (*type)
			{
			case 'x':
				playerType1 = player::PlayerType::x;
				playerType2 = player::PlayerType::o;
				invalid = false;
				break;
			case 'o':
				playerType1 = player::PlayerType::o;
				playerType2 = player::PlayerType::x;
				invalid = false;
				break;
			default:
				std::cout << "Invalid input!\n";
				invalid = true;
				break;
			}

			delete[] type;
		}

		bool isBot1{ input::getBoolInput("\nIs player 1 a bot? (bool): ") };
		bool isBot2{ input::getBoolInput("Is player 2 a bot? (bool): ") };
		int difficulty1{};
		int difficulty2{};
		if (isBot1) difficulty1 = input::getIntInput("\nWhat is player 1's difficulty level? (0, 1, or 2): ");
		if (isBot2) difficulty2 = input::getIntInput("\nWhat is player 2's difficulty level? (0, 1, or 2): ");
		
		if (difficulty1 > 2 || difficulty1 < 0)
		{
			std::cout << "Difficulty must and integer of value 0, 1, or 2!";
			std::exit(-1);
		}

		if (difficulty2 > 2 || difficulty2 < 0)
		{
			std::cout << "Difficulty must and integer of value 0, 1, or 2!";
			std::exit(-1);
		}
		m_Player1 = new player::Player{ this, playerType1, isBot1, difficulty1 };
		m_Player2 = new player::Player{ this, playerType2, isBot2, difficulty2 };

		const char* playerOrBot1{ m_Player1->isBot() ? "bot" : "human" };
		const char* type1{ m_Player1->getPlayerType() == player::PlayerType::x ? "x's\n" : "o's\n" };

		std::cout << "\nPlayer 1 will be a " << playerOrBot1 << " playing as " << type1;

		const char* playerOrBot2{ m_Player2->isBot() ? "bot" : "human" };
		const char* type2{ m_Player2->getPlayerType() == player::PlayerType::x ? "x's\n" : "o's\n" };

		std::cout << "Player 2 will be a " << playerOrBot2 << " playing as " << type2 << "\n\n";

		m_State = GameState::playing;
	}

	TicTacToe::~TicTacToe()
	{
		delete[] m_Grid;
		delete m_Player1;
		delete m_Player2;
	}

	void TicTacToe::start()
	{
		printGrid();

		while (true)
		{
			if (!m_Player1->isBot())
			{
				player::PlayerInput playerInput1{ m_Player1->getPlayerInput("Player 1, enter a set of coords (i.e. 'a0'): ") };
				updateGrid(playerInput1);
			}
			else
			{
				player::PlayerInput playerInput1{ m_Player1->getBotInput("Player 1 (bot) is thinking...") };
				updateGrid(playerInput1);
			}
			printGrid();
			updateState();
			if (m_State != GameState::playing) break;

			if (!m_Player2->isBot())
			{
				player::PlayerInput playerInput2{ m_Player2->getPlayerInput("Player 2, enter a set coords (i.e. 'a0'): ") };
				updateGrid(playerInput2);
			}
			else
			{
				player::PlayerInput playerInput2{ m_Player2->getBotInput("Player 2 (bot) is thinking...") };
				updateGrid(playerInput2);
			}
			printGrid();
			updateState();
			if (m_State != GameState::playing) break;
		}

		if (m_State == GameState::player1win)
		{
			std::cout << "\n--------------------------------------------\nPlayer 1 Wins!!!\n--------------------------------------------\n\n";
			return;
		}

		if (m_State == GameState::player2win)
		{
			std::cout << "\n--------------------------------------------\nPlayer 2 Wins!!!\n--------------------------------------------\n\n";
			return;
		}

		if (m_State == GameState::catsGame)
		{
			std::cout << "\n--------------------------------------------\nCats game!\n--------------------------------------------\n\n";
			return;
		}
	}

	void TicTacToe::updateGrid(player::PlayerInput input)
	{
		m_Grid[input.index] = input.slot;
	}

	void TicTacToe::updateState()
	{
		for (int i{}; i < m_Size; ++i)
		{
			int xRowCount{}, oRowCount{}, noneRowCount{};
			int xColumnCount{}, oColumnCount{}, noneColumnCount{};

			getRowSlotCounts(i, xRowCount, oRowCount, noneRowCount);
			getColumnSlotCounts(i, xColumnCount, oColumnCount, noneColumnCount);

			if (xRowCount == m_Size || xColumnCount == m_Size)
			{
				m_State = m_Player1->getPlayerType() == player::PlayerType::x ? GameState::player1win : GameState::player2win;
				return;
			}
			if (oRowCount == m_Size || oColumnCount == m_Size)
			{
				m_State = m_Player1->getPlayerType() == player::PlayerType::o ? GameState::player1win : GameState::player2win;
				return;
			}

			if (i < 2)
			{
				int xDiagonalCount{}, oDiagonalCount{}, noneDiagonalCount{};
				getDiagonalSlotCounts(i, xDiagonalCount, oDiagonalCount, noneDiagonalCount);

				if (xDiagonalCount == m_Size)
				{
					m_State = m_Player1->getPlayerType() == player::PlayerType::x ? GameState::player1win : GameState::player2win;
					return;
				}
				if (oDiagonalCount == m_Size)
				{
					m_State = m_Player1->getPlayerType() == player::PlayerType::o ? GameState::player1win : GameState::player2win;
					return;
				}
			}
		}

		bool tieGame{ true };
		for (int i{}; i < m_Size * m_Size; ++i)
		{
			if (m_Grid[i] == SlotState::none)
			{
				tieGame = false;
				break;
			}
		}

		if (tieGame)
		{
			m_State = GameState::catsGame;
			return;
		}

		m_State = GameState::playing;
	}

	void TicTacToe::printGrid()
	{
		char* maxCoordLenStr{ strings::toString(m_Size - 1) };
		int maxCoordsLen{};
		for (int i{}; maxCoordLenStr[i] != '\0'; ++i)
		{
			++maxCoordsLen;
		}
		delete[] maxCoordLenStr;

		char* string{ new char[maxCoordsLen + 1] {} };

		for (int i{}; i < maxCoordsLen; ++i)
		{
			string[i] = ' ';
		}
		string[maxCoordsLen] = '\0';

		for (int i{}; i < m_Size; ++i)
		{
			char letter[]{ static_cast<char>(97 + i), '\0' };
			const char* cat1[]{ string, "   ",  letter, };
			catAndDelete(string, cat1, 3);
		}

		const char* cat2[]{ string, "\n\n" };
		catAndDelete(string, cat2, 2);

		for (int i{}; i < m_Size; ++i)
		{
			char* itr{ strings::toString(i) };
			int coordsLen{};
			for (int j{}; itr[j] != '\0'; ++j)
			{
				++coordsLen;
			}

			char* spaces{ new char[(maxCoordsLen - coordsLen) + 1]{} };
			for (int j{}; j < maxCoordsLen - coordsLen; ++j)
			{
				spaces[j] = ' ';
			}
			spaces[maxCoordsLen - coordsLen] = '\0';

			const char* cat3[]{ string, spaces, itr, "   "};
			catAndDelete(string, cat3, 4);
			delete[] itr;
			delete[] spaces;

			for (int j{}; j < m_Size; ++j)
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

				const char* cat4[]{ string, slot, j != (m_Size - 1) ? " | " : "" };
				catAndDelete(string, cat4, 3);
			}

			const int dashesSize{ m_Size * 4 };
			char* dashes{ new char[dashesSize]{} };
			char* dashSpaces{ new char[maxCoordsLen + 1]{} };
			for (int i{}; i < dashesSize - 1; ++i)
			{
				dashes[i] = '-';
			}
			for (int i{}; i < maxCoordsLen - 1; ++i)
			{
				dashSpaces[i] = ' ';
			}
			
			dashes[dashesSize - 1] = '\0';
			dashSpaces[maxCoordsLen] = '\0';

			const char* cat5[]{ string, "\n   ", dashSpaces, i != m_Size - 1 ? dashes : "", "\n" };
			catAndDelete(string, cat5, 5);
			delete[] dashes;
			delete[] dashSpaces;
		}

		std::cout << "\n\n" << string;
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
		if (rowIndex > m_Size)
		{
			std::cout << "Invalid row index! (returning nullptr)\n";
			return nullptr;
		}

		SlotState* row{ new SlotState[m_Size] };

		for (int i{}; i < m_Size; ++i)
		{
			row[i] = m_Grid[(m_Size * rowIndex) + i];
		}

		return row;
	}

	SlotState* TicTacToe::getColumn(int columnIndex)
	{
		if (columnIndex > m_Size)
		{
			std::cout << "Invalid column index! (returning nullptr)\n";
			return nullptr;
		}

		SlotState* column{ new SlotState[m_Size] };

		for (int i{}; i < m_Size; ++i)
		{
			column[i] = m_Grid[(m_Size * i) + columnIndex];
		}

		return column;
	}

	//returns an array of slots representing either the 
	//slots from the top left to bottom right or top right to bottom left
	SlotState* TicTacToe::getDiagonal(int diagonalIndex)
	{
		if (diagonalIndex >= 2)
		{
			std::cout << "Invalid diagonal index! (returning nullptr)\n";
			return nullptr;
		}

		SlotState* diagonal{ new SlotState[m_Size] };

		if (diagonalIndex == 0)
		{
			for (int i{}; i < m_Size; ++i)
			{
				diagonal[i] = m_Grid[(m_Size * i) + i];
			}
		}
		else if (diagonalIndex == 1)
		{
			for (int i{}; i < m_Size; ++i)
			{
				diagonal[i] = m_Grid[(m_Size * (i + 1)) - (i + 1)];
			}
		}

		return diagonal;
	}

	void TicTacToe::getRowSlotCounts(int index, int& o_xCount, int& o_oCount, int& o_noneCount)
	{
		SlotState* row{ getRow(index) };

		o_xCount = 0;
		o_oCount = 0;
		o_noneCount = 0;
		for (int j{}; j < m_Size; ++j)
		{
			switch (row[j])
			{
			case SlotState::x:
				++o_xCount;
				break;
			case SlotState::o:
				++o_oCount;
				break;
			case SlotState::none:
				++o_noneCount;
				break;
			}
		}
		delete[] row;
	}

	void TicTacToe::getColumnSlotCounts(int index, int& o_xCount, int& o_oCount, int& o_noneCount)
	{
		SlotState* column{ getColumn(index) };

		o_xCount = 0;
		o_oCount = 0;
		o_noneCount = 0;
		for (int j{}; j < m_Size; ++j)
		{
			switch (column[j])
			{
			case SlotState::x:
				++o_xCount;
				break;
			case SlotState::o:
				++o_oCount;
				break;
			case SlotState::none:
				++o_noneCount;
				break;
			}
		}
		delete[] column;
	}

	void TicTacToe::getDiagonalSlotCounts(int index, int& o_xCount, int& o_oCount, int& o_noneCount)
	{
		SlotState* diagonal{ getDiagonal(index) };

		o_xCount = 0;
		o_oCount = 0;
		o_noneCount = 0;
		for (int j{}; j < m_Size; ++j)
		{
			switch (diagonal[j])
			{
			case SlotState::x:
				++o_xCount;
				break;
			case SlotState::o:
				++o_oCount;
				break;
			case SlotState::none:
				++o_noneCount;
				break;
			}
		}
		delete[] diagonal;
	}

	int TicTacToe::getSize()
	{
		return m_Size;
	}

	SlotState* TicTacToe::getGrid()
	{
		return m_Grid;
	}

	GameState TicTacToe::getState()
	{
		return m_State;
	}
}