#ifndef PLAYER_H
#define PLAYER_H
#include <random>

namespace tictactoe
{
	class TicTacToe;

	enum class SlotState;

	enum class GameState;
}

namespace player
{
	enum class PlayerType
	{
		x,
		o
	};

	struct PlayerInput
	{
		int index{};
		tictactoe::SlotState slot{};
	};

	class Player
	{
	private:
		tictactoe::TicTacToe* m_Instance;
		PlayerType m_PlayerType;
		bool m_IsBot;
		//int currentOffenceIndex;
		//int currentOffenceType;
		std::mt19937 rand;
		std::uniform_int_distribution<> die;
		std::uniform_int_distribution<> dieOther;

		bool isFullRow(int index);

		bool isFullColumn(int index);

		bool isFullDiagonal(int index);

	public:
		Player(tictactoe::TicTacToe* instance, PlayerType playerType, bool isBot);

		PlayerInput getPlayerInput(const char* message);

		PlayerInput getBotInput(const char* message);

		PlayerType getPlayerType();

		bool isBot();
	};
}

#endif
