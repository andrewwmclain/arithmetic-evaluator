// Title: Lab 1 - main.cpp
//
// Purpose: Practice the methods offered by the C++ standard library string class by writing a C++ program
// that reads in an arithmetic expression and prints out a step by step evaluation of the expression.
//
// Class: CSC 2430 Winter 2020
// Author: Max Benson

#include "evalsteps.h"

//
// Main program:
//
// Repeatedly prompts the user to enter an expression
// and it will call the student's function that
// returns the evaluation steps as a string.
// Prints the string that is returned.
//
int main() {
    string expression;
    string evalSteps;

    cout << "Expression? ";
    while (getline(cin, expression) && expression.length() > 0)
    {
        cout << "Evaluation Steps:" << endl;
        evalSteps = GetEvalSteps(expression);
        cout << evalSteps << endl;
        cout << "Expression? ";
    }

    return 0;
}

