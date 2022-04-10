#include "strings.h"
#include <cstddef>

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

        char* newString{ new char[newLength + static_cast<size_t>(1)] };
        int ptr{};

        for (int i{}; i < numStrings; ++i)
        {
            int j{};
            for (const char* str = *(strings + i); *(str + j) != '\0'; ++j)
            {
                *(newString + ptr) = *(str + j);
                ++ptr;
            }
        }

        *(newString + newLength) = '\0';

        return newString;
    }

    char* toString(int val)
    {
        int len{};
        int divisor{};
        bool negative{};

        if (val < 0)
        {
            val = abs(val);
            negative = true;
        }

        for (int i{}; len == 0; ++i)
        {
            divisor = pow(10, i);
            if ((val / divisor) == 0)
            {
                len = i;
            }
        }

        char* string{ new char[len + static_cast<size_t>(1)]{} }; // +1 for null terminator

        for (int i{}; i < len; ++i)
        {
            int power{ pow(10, i + 1) };
            int numVal{ val % power };
            numVal /= (power / 10);

            switch (numVal)
            {
            case 0:
                *(string + (len - static_cast<size_t>(1)) - i) = '0';
                break;
            case 1:
                *(string + (len - static_cast<size_t>(1)) - i) = '1';
                break;
            case 2:
                *(string + (len - static_cast<size_t>(1)) - i) = '2';
                break;
            case 3:
                *(string + (len - static_cast<size_t>(1)) - i) = '3';
                break;
            case 4:
                *(string + (len - static_cast<size_t>(1)) - i) = '4';
                break;
            case 5:
                *(string + (len - static_cast<size_t>(1)) - i) = '5';
                break;
            case 6:
                *(string + (len - static_cast<size_t>(1)) - i) = '6';
                break;
            case 7:
                *(string + (len - static_cast<size_t>(1)) - i) = '7';
                break;
            case 8:
                *(string + (len - static_cast<size_t>(1)) - i) = '8';
                break;
            case 9:
                *(string + (len - static_cast<size_t>(1)) - i) = '9';
                break;
            default:
                *(string + (len - static_cast<size_t>(1)) - i) = 'e';
            }
        }

        *(string + len) = '\0';

        if (negative)
        {
            int negLen{ len + 1 }; // +1 for "-" negative indicator at the front
            char* temp{ new char[negLen + static_cast<size_t>(1)] }; // +1 for null terminator
            temp[0] = '-';
            for (int i{}; i < len; ++i)
            {
                *(temp + (i + static_cast<size_t>(1))) = *(string + i);
            }
            *(temp + negLen) = '\0';

            delete[] string;
            string = temp;
        }

        return string;
    }

    int abs(int value)
    {
        if (value >= 0)
        {
            return value;
        }
        else
        {
            value -= value * 2;
            return value;
        }
    }

    int pow(int base, int exp)
    {
        if (exp < 0)
        {
            return 0;
        }

        int result = 1;
        for (int i{}; i < exp; ++i)
        {
            result *= base;
        }

        return result;
    }
}
