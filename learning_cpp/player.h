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

	struct BotOffence
	{
		int currentOffenceIndex;
		int currentOffenceType;
	};

	class Player
	{
	private:
		tictactoe::TicTacToe* m_Instance;
		PlayerType m_PlayerType;
		BotOffence* botOffence;
		bool m_IsBot;
		const int m_Difficulty;
		std::mt19937 rand;
		std::uniform_int_distribution<> sizeDie;
		std::uniform_int_distribution<> areaDie;

		bool isFullRow(int index);

		bool isFullColumn(int index);

		bool isFullDiagonal(int index);

		void checkForOffenceTarget();

		PlayerInput doOffence();

		PlayerInput doRowDefence(int row);

		PlayerInput doColumnDefence(int column);
		
		PlayerInput doDiagonalDefence(int diagonal);

	public:
		Player(tictactoe::TicTacToe* instance, PlayerType playerType, bool isBot, const int difficulty);

		~Player();

		PlayerInput getPlayerInput(const char* message);

		PlayerInput getBotInput(const char* message);

		PlayerType getPlayerType();

		bool isBot();
	};
}

#endif
