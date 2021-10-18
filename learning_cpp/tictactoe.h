#ifndef TICTACTOE_H
#define TICTACTOE_H

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
		won,
		lost,
		catsGame
	};

	struct PlayerInput
	{
		int index{};
		SlotState slot{};
	};

	class TicTacToe
	{
	private:
		bool multiPlayer;
		int difficulty;
		int size;
		SlotState* grid;
		GameState state;

		SlotState* getRow(int rowIndex);

		SlotState* getColumn(int columnIndex);

		SlotState* getDiagonal(int diagonalIndex);

		void updateGrid(PlayerInput input);

		PlayerInput getPlayerInput();

		void printGrid();

	public:
		TicTacToe(bool multiPlayer = false, int difficulty = 1, int size = 3);

		void start();

		bool getMultiPlayer();

		int getDifficulty();

		int getSize();

		GameState getState();
	};
}

#endif
