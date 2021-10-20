#include <iostream>
#include <limits>
#include "getinput.h"

namespace input
{
    static void clearInputBuffer();
    static constexpr int maxStingInput{ 255 };

    int getIntInput(const char* message)
    {
        int* val{};
        bool failed{ false };

        do
        {
            std::cout << message;

            int input{};
            std::cin >> input;
            val = &input;
           
            if (std::cin.fail())
            {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                failed = true;
            }
            else
            {
                failed = false;
            }

            clearInputBuffer();
        } while (failed);

        return *val;
    }

    float getFloatInput(const char* message)
    {
        float* val{};
        bool failed{ false };

        do
        {
            std::cout << message;

            float input{};
            std::cin >> input;
            val = &input;

            if (std::cin.fail())
            {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                failed = true;
            }
            else
            {
                failed = false;
            }

            clearInputBuffer();
        } while (failed);

        return *val;
    }

    bool getBoolInput(const char* message)
    {
        bool* val{};
        bool failed{ false };

        do
        {
            std::cout << message;

            bool input{};
            std::cin >> input;
            val = &input;

            if (std::cin.fail())
            {
                std::cout << "Invalid input!\n";
                std::cin.clear();
                failed = true;
            }
            else
            {
                failed = false;
            }

            clearInputBuffer();
        } while (failed);

        return *val;
    }

    char* getStringInput(const char* message)
    {
        std::cout << message;

        char input[maxStingInput]{};
        std::cin >> input;
        clearInputBuffer();

        int strSize{};
        for (int i{}; input[i] != '\0'; ++i)
        {
            ++strSize;
        }

        char* finalString{ new char[strSize + 1] {} };

        for (int i{}; input[i] != '\0'; ++i)
        {
            finalString[i] = input[i];
        }

        finalString[strSize] = '\0';
        return finalString;
    }

    static void clearInputBuffer()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
