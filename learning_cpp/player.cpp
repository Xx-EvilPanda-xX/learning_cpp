#include <iostream>
#include <random>
#include <ctime>
#include "tictactoe.h"
#include "player.h"
#include "getinput.h"
#include "strings.h"

namespace player
{
	Player::Player(tictactoe::TicTacToe* instance, PlayerType playerType, bool isBot, const int difficulty) : m_Instance{ instance }, m_PlayerType{ playerType }, m_IsBot{ isBot }, m_Difficulty{ difficulty }
	{
		rand = std::mt19937{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
		die = std::uniform_int_distribution<>{ 0, m_Instance->getSize() - 1 };
		dieOther = std::uniform_int_distribution<>{ 0, m_Instance->getSize() * m_Instance->getSize() };

		botOffence = nullptr;
	}

	Player::~Player()
	{
		if (botOffence != nullptr)
		{
			delete botOffence;
			botOffence = nullptr;
		}
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

			index += m_Instance->getSize() * numVal;
			index += charVal - asciia;

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

		for (int i{}; i < m_Instance->getSize(); ++i)
		{
			int xRowCount{}, oRowCount{}, noneRowCount{};
			int xColumnCount{}, oColumnCount{}, noneColumnCount{};
			int xDiagonalCount{}, oDiagonalCount{}, noneDiagonalCount{};

			m_Instance->getRowSlotCounts(i, xRowCount, oRowCount, noneRowCount);
			m_Instance->getColumnSlotCounts(i, xColumnCount, oColumnCount, noneColumnCount);

			if (i < 2)
			{
				m_Instance->getDiagonalSlotCounts(i, xDiagonalCount, oDiagonalCount, noneDiagonalCount);
			}
			else
			{
				xDiagonalCount = -1;
				oDiagonalCount = -1;
				noneDiagonalCount = -1;
			}

			int opponentRowSlots{ m_PlayerType == PlayerType::x ? oRowCount : xRowCount };
			int opponentColumnSlots{ m_PlayerType == PlayerType::x ? oColumnCount : xColumnCount };
			int opponentDiagonalSlots{ m_PlayerType == PlayerType::x ? oDiagonalCount : xDiagonalCount };

			int ownRowSlots{ m_PlayerType == PlayerType::x ? xRowCount : oRowCount };
			int ownColumnSlots{ m_PlayerType == PlayerType::x ? xColumnCount : oColumnCount };
			int ownDiagonalSlots{ m_PlayerType == PlayerType::x ? xDiagonalCount : oDiagonalCount };
			
			if (ownRowSlots == 0 && opponentRowSlots >= m_Instance->getSize() - (m_Instance->getSize() / 2) && (opponentRowSlots >= opponentColumnSlots && opponentRowSlots >= opponentDiagonalSlots))
			{
				while (true)
				{
					if (isFullRow(i)) 
						break;

					PlayerInput input;
					if (m_Difficulty < 1)
					{
						input = PlayerInput{ dieOther(rand), m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
					}
					else
					{
						input = PlayerInput{ (i * m_Instance->getSize()) + die(rand), m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
					}
					

					if (m_Instance->getGrid()[input.index] != tictactoe::SlotState::none)
					{
						continue;
					}

					return input;
				}
			}

			if (ownColumnSlots == 0 && opponentColumnSlots >= m_Instance->getSize() - (m_Instance->getSize() / 2) && (opponentColumnSlots >= opponentRowSlots && opponentColumnSlots >= opponentDiagonalSlots))
			{
				while (true)
				{
					if (isFullColumn(i))
						break;

					PlayerInput input;
					if (m_Difficulty < 1)
					{
						input = PlayerInput{ dieOther(rand), m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
					}
					else
					{
						input = PlayerInput{ i + (m_Instance->getSize() * die(rand)), m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
					}

					if (m_Instance->getGrid()[input.index] != tictactoe::SlotState::none)
					{
						continue;
					}

					return input;
				}
			}

			if (i < 2)
			{
				if (ownDiagonalSlots == 0 && opponentDiagonalSlots >= m_Instance->getSize() - (m_Instance->getSize() / 2) && (opponentDiagonalSlots >= opponentRowSlots && opponentDiagonalSlots >= opponentColumnSlots))
				{
					while (true)
					{
						if (isFullDiagonal(i))
							break;

						PlayerInput input;
						if (i == 0)
						{
							if (m_Difficulty < 1)
							{
								input = PlayerInput{ dieOther(rand), m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
							}
							else
							{
								int random{ die(rand) };
								input = PlayerInput{ (m_Instance->getSize() * random) + random, m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
							}
						}
						else if (i == 1)
						{
							if (m_Difficulty < 1)
							{
								input = PlayerInput{ dieOther(rand), m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
							}
							else
							{
								int random{ die(rand) };
								input = PlayerInput{ (m_Instance->getSize() * (random + 1)) - (random + 1), m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
							}
						}

						if (m_Instance->getGrid()[input.index] != tictactoe::SlotState::none)
						{
							continue;
						}

						return input;
					}
				}
			}
		}

		while (true)
		{
			checkForOffenceTarget();

			PlayerInput input;
			if (botOffence == nullptr || m_Difficulty < 2)
			{
				input = PlayerInput{ dieOther(rand), m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };
			}
			else
			{
				int xCount{}, oCount{}, noneCount{};
				switch (botOffence->currentOffenceType)
				{
				case 0:
					m_Instance->getRowSlotCounts(botOffence->currentOffenceIndex, xCount, oCount, noneCount);
					break;
				case 1:
					m_Instance->getColumnSlotCounts(botOffence->currentOffenceIndex, xCount, oCount, noneCount);
					break;
				case 2:
					m_Instance->getDiagonalSlotCounts(botOffence->currentOffenceIndex, xCount, oCount, noneCount);
					break;
				}

				if ((xCount > 0 && oCount > 0) || noneCount == 0)
				{
					delete botOffence;
					botOffence = nullptr;
					continue;
				}

				int index{};
				tictactoe::SlotState slot{ m_PlayerType == PlayerType::x ? tictactoe::SlotState::x : tictactoe::SlotState::o };

				switch (botOffence->currentOffenceType)
				{
				case 0:
					index = (m_Instance->getSize() * botOffence->currentOffenceIndex) + die(rand);
					break;
				case 1:
					index = (m_Instance->getSize() * die(rand)) + botOffence->currentOffenceIndex;
					break;
				case 2:
					if (botOffence->currentOffenceIndex == 0)
					{
						int random{ die(rand) };
						index = (m_Instance->getSize() * random) + random;
					}
					else if (botOffence->currentOffenceIndex == 1)
					{
						int random{ die(rand) };
						index = (m_Instance->getSize() * (random + 1)) - (random + 1);
					}
					break;
				}

				input = PlayerInput{ index, slot };
			}

			if (m_Instance->getGrid()[input.index] != tictactoe::SlotState::none)
			{
				continue;
			}

			return input;
		}
	}

	void Player::checkForOffenceTarget()
	{
		int xRowCount{}, oRowCount{}, noneRowCount{};
		int xColumnCount{}, oColumnCount{}, noneColumnCount{};
		int xDiagonalCount{}, oDiagonalCount{}, noneDiagonalCount{};
		
		int index{ die(rand) };
		for (int i{}; i < m_Instance->getSize(); ++i)
		{
			if (index == m_Instance->getSize()) index = 0;

			m_Instance->getRowSlotCounts(index, xRowCount, oRowCount, noneRowCount);
			m_Instance->getColumnSlotCounts(index, xColumnCount, oColumnCount, noneColumnCount);
			if (index < 2)
			{
				m_Instance->getDiagonalSlotCounts(index, xDiagonalCount, oDiagonalCount, noneDiagonalCount);
			}
			else
			{
				xDiagonalCount = -1;
				oDiagonalCount = -1;
				noneDiagonalCount = -1;
			}

			int opponentRowSlots{ m_PlayerType == PlayerType::x ? oRowCount : xRowCount };
			int opponentColumnSlots{ m_PlayerType == PlayerType::x ? oColumnCount : xColumnCount };
			int opponentDiagonalSlots{ m_PlayerType == PlayerType::x ? oDiagonalCount : xDiagonalCount };

			if (botOffence == nullptr)
			{
				if (opponentRowSlots == 0)
				{
					botOffence = new BotOffence{ index, 0 };
				}
				else if (opponentColumnSlots == 0)
				{
					botOffence = new BotOffence{ index, 1 };
				}
				else if (opponentDiagonalSlots == 0)
				{
					botOffence = new BotOffence{ index, 2 };
				}
			}
			++index;
		}
	}

	bool Player::isFullRow(int index)
	{
		tictactoe::SlotState* row{ m_Instance->getRow(index) };

		for (int i{}; i < m_Instance->getSize(); ++i)
		{
			if (row[i] == tictactoe::SlotState::none)
			{
				delete[] row;
				return false;
			}
		}
		delete[] row;
		return true;
	}

	bool Player::isFullColumn(int index)
	{
		tictactoe::SlotState* column{ m_Instance->getColumn(index) };

		for (int i{}; i < m_Instance->getSize(); ++i)
		{
			if (column[i] == tictactoe::SlotState::none)
			{
				delete[] column;
				return false;
			}
		}
		delete[] column;
		return true;
	}

	bool Player::isFullDiagonal(int index)
	{
		tictactoe::SlotState* diagonal{ m_Instance->getDiagonal(index) };

		for (int i{}; i < m_Instance->getSize(); ++i)
		{
			if (diagonal[i] == tictactoe::SlotState::none)
			{
				delete[] diagonal;
				return false;
			}
		}
		delete[] diagonal;
		return true;
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
