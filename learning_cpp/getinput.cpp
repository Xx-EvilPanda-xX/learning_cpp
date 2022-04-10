#include <iostream>
#include <limits>
#include "getinput.h"

namespace input
{
    static void clearInputBuffer();
    static constexpr int maxStingInput{ 255 };

    int getIntInput(const char* message)
    {
        int input{};
        bool failed{ false };

        do
        {
            std::cout << message;
            std::cin >> input;
           
            if (std::cin.fail())
            {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                failed = true;
            }
            else
                failed = false;

            clearInputBuffer();
        } while (failed);

        return input;
    }

    float getFloatInput(const char* message)
    {
        float input{};
        bool failed{ false };

        do
        {
            std::cout << message;
            std::cin >> input;

            if (std::cin.fail())
            {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                failed = true;
            }
            else
                failed = false;

            clearInputBuffer();
        } while (failed);

        return input;
    }

    bool getBoolInput(const char* message)
    {
        bool input{};
        bool failed{ false };

        do
        {
            std::cout << message;
            std::cin >> input;

            if (std::cin.fail())
            {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                failed = true;
            }
            else
                failed = false;

            clearInputBuffer();
        } while (failed);

        return input;
    }

    char* getStringInput(const char* message)
    {
        char input[maxStingInput]{};

        std::cout << message;
        std::cin >> input;
        clearInputBuffer();

        int strSize{};
        for (int i{}; input[i] != '\0'; ++i)
        {
            ++strSize;
        }

        char* string{ new char[strSize + 1] {} };

        for (int i{}; input[i] != '\0'; ++i)
        {
            string[i] = input[i];
        }

        string[strSize] = '\0';
        return string;
    }

    static void clearInputBuffer()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
