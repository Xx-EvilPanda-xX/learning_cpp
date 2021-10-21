#include <iostream>
#include "tictactoe.h"
#include "player.h"
#include "getinput.h"
#include "strings.h"

namespace player
{
	Player::Player(tictactoe::TicTacToe* instance, PlayerType playerType, bool isBot) : m_Instance{ instance }, m_PlayerType{ playerType }, m_IsBot{ isBot }
	{
	}

	PlayerInput Player::getPlayerInput(const char* message)
	{
		while (true)
		{
			char* input{ input::getStringInput(message) };

			int lengthCheck{};
			for (int i{}; input[i] != '\0'; ++i)
			{
				++lengthCheck;
			}

			if (lengthCheck > 3)
			{
				std::cout << "Invalid input! (input must be 3 chars or less)\n";
				continue;
			}

			constexpr int ascii0{ 48 };
			constexpr int asciia{ 97 };

			int numVal{};
			bool invalid{};
			for (int i{ 1 }; i < lengthCheck; ++i)
			{
				char value{ input[(lengthCheck - 1) - (i - 1)] };
				if (value < '0' || value > '9')
				{
					std::cout << "Invalid input! (invalid numerical input)\n";
					invalid = true;
					break;
				}
				numVal += (value - ascii0) * strings::pow(10, (i - 1));
			}

			if (invalid) continue;

			char charVal{ input[0] };

			delete[] input;

			if (charVal < 'a' || charVal > 'z')
			{
				std::cout << "Invalid input! (invalid character input)\n";
				continue;
			}
			
			if (charVal - asciia > m_Instance->getSize() - 1 || numVal > m_Instance->getSize() - 1)
			{
				std::cout << "Invalid input! (out of range)\n";
				continue;
			}

			int index{};

			index += (m_Instance->getSize() * numVal) - 1;
			index += ((charVal - asciia) + 1);

			PlayerInput finalInput{ index, m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
			if (m_Instance->getGrid()[finalInput.index] != tictactoe::SlotState::none)
			{
				std::cout << "Invalid input! (slot already taken)\n";
				continue;
			}

			return finalInput;
		}
	}

	PlayerInput Player::getBotInput(const char* message)
	{
		std::cout << message;
		return PlayerInput{ 1, m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
	}

	PlayerType Player::getPlayerType()
	{
		return m_PlayerType;
	}

	bool Player::isBot()
	{
		return m_IsBot;
	}
}