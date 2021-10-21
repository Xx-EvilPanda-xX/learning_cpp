#ifndef TICTACTOE_H
#define TICTACTOE_H
namespace player
{
	class Player;

	enum class PlayerType;

	struct PlayerInput;
}

namespace tictactoe
{
	enum class SlotState
	{
		x,
		o,
		none
	};

	enum class GameState
	{
		playing,
		player1win,
		player2win,
		catsGame
	};

	class TicTacToe
	{
	private:
		player::Player* m_Player1;
		player::Player* m_Player2;
		const int m_Difficulty;
		const int m_Size;
		SlotState* m_Grid;
		GameState m_State;

		void updateGrid(player::PlayerInput input);

		void updateState();

		void printGrid();

		void catAndDelete(char*& string, const char* cat[], int numStrings);

	public:
		TicTacToe(int difficulty = 1, int size = 3);

		void start();

		int getDifficulty();

		int getSize();

		SlotState* getGrid();

		GameState getState();

		SlotState* getRow(int rowIndex);

		SlotState* getColumn(int columnIndex);

		SlotState* getDiagonal(int diagonalIndex);

		void getRowSlotCounts(int index, int& o_xCount, int& o_oCount, int& o_noneCount);

		void getColumnSlotCounts(int index, int& o_xCount, int& o_oCount, int& o_noneCount);

		void getDiagonalSlotCounts(int index, int& o_xCount, int& o_oCount, int& o_noneCount);
	};
}

#endif
