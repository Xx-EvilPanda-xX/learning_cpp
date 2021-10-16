#include "arrays.h"
#include "strings.h"
#include "getinput.h"
#include <iostream>

namespace arrays
{
    void arrayCalculation()
    {
        int len = input::getIntInput("Please enter an integer value for the length of the array to sort: ");
        int* array{ getArray(len) };

        sortArray(array, len);
        printArray(array, len);

        delete[] array;
    }

    int* getArray(int length)
    {
        int* arr{ new int[length] };

        for (int i{}; i < length; ++i)
        {
            const char* iter{ strings::toString(i) };
            const char* strings[]{ "Enter an integer value for element #", iter, ": " };
            const char* str{ strings::strCat(strings, 3) };

            int element{ input::getIntInput(str) };
            delete[] str;
            delete[] iter;

            arr[i] = element;
        }

        return arr;
    }

    void sortArray(int* array, int arrayLength)
    {
        for (int i{}; i < arrayLength; ++i)
        { 
            for (int j{}; j < ((arrayLength - 1) - i); ++j)
            {
                if (array[j] > array[j + 1])
                {
                    int tempElement{ array[j] };

                    array[j] = array[j + 1];
                    array[j + 1] = tempElement;
                }
            }
        }
    }

    void printArray(int* array, int arrayLength)
    {
        std::cout << "\nSorted array:\n\n=================================================================\n\n[";

        for (int i{}; i < arrayLength; ++i)
        {
            std::cout << array[i];
            if (i != arrayLength - 1)
            {
                std::cout << ", ";
            }
        }

        std::cout << "]\n\n";
    }
}