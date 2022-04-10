#include <iostream>
#include "getinput.h"
#include "logger.h"
#include "constants.h"
#include "arrays.h"
#include "tictactoe.h"

void test();
void intOperations();
void floatOperations();
void boolOperations();

int main()
{
    int size{ input::getIntInput("Enter a width/height for the tictactoe grid (int): ") };
    tictactoe::TicTacToe tictactoe{ size };
    tictactoe.start();

    test();
    arrays::arrayCalculation();

    intOperations();
    floatOperations();
    boolOperations();
}

void test()
{
    std::cout << "constants::pi = " << constants::pi << "\n";
    std::cout << "constants::e = " << constants::e << "\n";
    std::cout << "constants::gravity = " << constants::gravity << "\n\n";
}

void intOperations()
{
    int intInput_a{ input::getIntInput("Please enter an integer value for operand 1: ") };
    int intInput_b{ input::getIntInput("Please enter an integer value for operand 2: ") };

    while (intInput_b == 0) 
    {
        std::cout << "Operand 2 must be non zero (divsion by zero). Please try again.\n";
        intInput_b = input::getIntInput("Please enter an integer value for operand 2: ");
    }

    logger::IntResult* intResult{ new logger::IntResult{} };

    intResult->product = intInput_a * intInput_b;
    intResult->sum = intInput_a + intInput_b;
    intResult->quotient = intInput_a / intInput_b;
    intResult->difference = intInput_a - intInput_b;

    std::cout << "\nint input 1 = " << intInput_a << "\n";
    std::cout << "\nint input 2 = " << intInput_b << "\n";

    logger::printResults(intResult);
    delete intResult;
    intResult = nullptr;
}

void floatOperations()
{
    float floatInput_a{ input::getFloatInput("Please enter a floating point value for operand 1: ") };
    float floatInput_b{ input::getFloatInput("Please enter a floating point value for operand 2: ") };

    while (floatInput_b == 0.0f) 
    {
        std::cout << "Operand 2 must be non zero (divsion by zero). Please try again.\n";
        floatInput_b = input::getFloatInput("Please enter a floating point value for operand 2: ");
    }

    logger::FloatResult* floatResult{ new logger::FloatResult{} };

    floatResult->product = floatInput_a * floatInput_b;
    floatResult->sum = floatInput_a + floatInput_b;
    floatResult->quotient = floatInput_a / floatInput_b;
    floatResult->difference = floatInput_a - floatInput_b;

    std::cout << "\nfloat input 1 = " << floatInput_a << "\n";
    std::cout << "\nfloat input 2 = " << floatInput_b << "\n";

    logger::printResults(floatResult);
    delete floatResult;
    floatResult = nullptr;
}

void boolOperations()
{
    bool boolInput_a{ input::getBoolInput("Please enter a boolean value for operand 1: ") };
    bool boolInput_b{ input::getBoolInput("Please enter a boolean value for operand 2: ") };

    bool boolAnd{ boolInput_a && boolInput_b };
    bool boolOr{ boolInput_a || boolInput_b };
    bool boolEqu{ boolInput_a == boolInput_b };

    logger::BoolResult* boolResult{ new logger::BoolResult{ boolAnd, boolOr, boolEqu} };

    std::cout << "\nbool input 1 = " << boolInput_a << "\n";
    std::cout << "\nbool input 2 = " << boolInput_b << "\n";

    logger::printResults(boolResult);
    delete boolResult;
    boolResult = nullptr;
}