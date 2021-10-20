#ifndef PLAYER_H
#define PLAYER_H
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

	public:
		Player(tictactoe::TicTacToe* instance, PlayerType playerType, bool isBot);

		PlayerInput getPlayerInput(const char* message);

		PlayerInput getBotInput(const char* message);

		PlayerType getPlayerType();

		bool isBot();
	};
}

#endif
