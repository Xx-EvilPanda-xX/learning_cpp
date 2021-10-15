#include "strings.h"
#include <iostream>

namespace strings
{
    char* strCat(const char* strings[], int numStrings)
    {
        int newLength{};

        for (int i{}; i < numStrings; ++i)
        {
            int j{};
            for (const char* str = *(strings + i); *(str + j) != '\0'; ++j)
            {
                ++newLength;
            }
        }

        char* finalStr{ new char[newLength + 1] };
        int ptr{};

        for (int i{}; i < numStrings; ++i)
        {
            int j{};
            for (const char* str = *(strings + i); *(str + j) != '\0'; ++j)
            {
                *(finalStr + ptr) = *(str + j);
                ++ptr;
            }
        }

        *(finalStr + newLength) = '\0';

        return finalStr;
    }

    char* toString(int val)
    {
        int len{};
        int divisor{};
        for (int i{}; len == 0; ++i)
        {
            divisor = (int)std::pow(10, i);
            if ((val / divisor) == 0)
            {
                len = i;
            }
        }

        char* string{ new char[len + 1]{} };

        for (int i{}; i < len; ++i)
        {
            int pow{ (int)std::pow(10, i + 1) };
            int numVal{ val % pow };
            numVal /= (pow / 10);

            switch (numVal)
            {
            case 0:
                string[(len - 1) - i] = '0';
                break;
            case 1:
                string[(len - 1) - i] = '1';
                break;
            case 2:
                string[(len - 1) - i] = '2';
                break;
            case 3:
                string[(len - 1) - i] = '3';
                break;
            case 4:
                string[(len - 1) - i] = '4';
                break;
            case 5:
                string[(len - 1) - i] = '5';
                break;
            case 6:
                string[(len - 1) - i] = '6';
                break;
            case 7:
                string[(len - 1) - i] = '7';
                break;
            case 8:
                string[(len - 1) - i] = '8';
                break;
            case 9:
                string[(len - 1) - i] = '9';
                break;
            default:
                string[(len - 1) - i] = 'e';
            }
        }

        string[len] = '\0';

        return string;
    }
}