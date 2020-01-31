// Title: Lab 1 - evalsteps.cpp
//
// Purpose: Complete the implementation for function GetEvalSteps, which accepts a mathematical expression as
// a parameter and returns a formatted string containing the step-by-step order of operations to solve it.
//
// Class: CSC 2430 Winter 2020 w/ Dr. Arias
// Author: Andrew McLain

#include <assert.h>
#include "evalsteps.h"
#include <string>
#include <iomanip>

// Forward declarations of sub-functions used to implement "GetEvalSteps"

string CalcResult(const string&, const string&, const char&);
bool NotComplete(const string&, const string&, int&);
void GenerateSteps(string&, ostringstream&, const string&, bool&, const int);

// CalcResult accepts two operands as strings and a valid operation as a character and returns the result
// of the expression composed of those three parameters as a string.
// Parameters:
//           operand1 - first number in the two-number expression
//           operand2 - second number in the two-number expression
//           operation - operation between the two given operands
// Returns:
//          result - value of the evaluated expression as a string
// Possible Errors:
//          If the function were to somehow get passed a non-digit operand, there would be a runtime error
//          If the function were to somehow get passed an invalid operation, the result would falsely be "0"
//          If the expression contains division by 0, there will be a runtime error.

string CalcResult(const string& operand1, const string& operand2, const char& operation){
    string result;

    switch(operation){
        case '*':
        result = to_string(stoi(operand1) * stoi(operand2));
        break;

        case '/':
            result = to_string(stoi(operand1) / stoi(operand2));
            break;

        case '%':
            result = to_string(stoi(operand1) % stoi(operand2));
            break;

        case '+':
            result = to_string(stoi(operand1) + stoi(operand2));
            break;

        case '-':
            result = to_string(stoi(operand1) - stoi(operand2));
            break;

        default:
            result = "0";
            break;
    }

    return result;
}

// NotComplete returns a boolean value indicating whether any additional operations can be done
// on the remaining expression given a set of possible operators.
// Parameters:
//           temp - modified copy of the user-inputted expression
//           operators - string containing the type of operations that can be done
//           operatorIndex - index of the operator from the previously completed calculation and
//           starting point from which the expression is evaluated
// Returns:
//          true or false value depending on completion status
// Possible Errors:
//          Would not evaluate to false even if the only remaining operation was division by 0

bool NotComplete(const string& temp, const string& operators, int& operatorIndex){
    while(operatorIndex < temp.size() - 1){
        if(temp.find_first_of(operators, operatorIndex) < temp.size() - 1 &&
            temp.find_first_of(operators, operatorIndex) != string::npos &&
            isdigit(temp.at(temp.find_first_of(operators, operatorIndex) - 1)) &&
            isdigit(temp.at(temp.find_first_of(operators, operatorIndex) + 1))){
            operatorIndex = temp.find_first_of(operators, operatorIndex);
            return true;
        }
        else{
            operatorIndex++;
        }
    }
    return false;
}

// GenerateSteps inputs the formatted solution steps for the expression into the ostringstream outSS,
// given a temporary string copy of the user inputted expression, the length of the original expression,
// a string containing the type of operations that can be done, and a boolean value to indicate whether
// any of the first set of operators ("*/%") has been used (for formatting purposes).
// Parameters:
//           temp - modified copy of the user-inputted expression
//           outSS - ostringstream to hold each iteration of temp as it is modified step-by-step
//           operators - string containing the type of operations that can be done
//           expressionLength- length of the original user expression
//           hasChanged - boolean value which evaluates to true if any of the operators "*/%" is used
// Returns:
//          GenerateSteps does not return anything
// Possible Errors:
//          I have not yet identified any errors.

void GenerateSteps(string& temp, ostringstream& outSS, const string& operators,
                   bool& hasChanged, const int expressionLength){
    int operatorIndex = 1;
    int operand1_index;
    int operand2_index;
    string result;
    string operand1;
    string operand2;
    char operation;
    //Loop continues while operations remain to be done
    while(NotComplete(temp, operators, operatorIndex) && operatorIndex < temp.size()){
        hasChanged = true;
        operand1_index = operatorIndex - 1;
    //Determine substring for first operand
        while (isdigit(temp.at(operand1_index))) {
            operand1_index--;
            if (operand1_index < 0) {
                break;
            }
        }
        operand1 = temp.substr(operand1_index + 1, (operatorIndex - (operand1_index + 1)));
    //Determine substring for second operand
        operand2_index = operatorIndex + 1;
        while (isdigit(temp.at(operand2_index))) {
            operand2_index++;
            if (operand2_index > temp.size() - 1) {
                break;
            }
        }
        operand2 = temp.substr(operatorIndex + 1, ((operand2_index - 1) - operatorIndex));
        //Replace substring containing operand1, operation, and operand 2 with result
        operation = temp.at(operatorIndex);
        result = CalcResult(operand1, operand2, operation);
        temp.replace(operand1_index + 1, (operand2_index) - (operand1_index + 1), result);
        outSS << temp;
        //If operations remain to be done, generate formatting
        if (NotComplete(temp, operators, operatorIndex)){
            outSS << "\n" << setw(expressionLength + 3) << " = ";
        }
        operatorIndex = operand1_index + 1;
    }
}

// GetEvalSteps accepts a mathematical expression as a string and returns another string containing each
// intermediate step to solve the expression following the order of operations.
// Parameters:
//          expression - mathematical expression originated from user keyboard input then passed
//                       from main function
// Returns:
//          completedSteps - string containing step-by-step solution to the expression
// Possible Errors:
//          I have not yet identified any errors.

string GetEvalSteps(const string& expression) {
    ostringstream outSS;
    string temp(expression);
    string completedSteps;
    int expressionLength = expression.size();
    int operatorIndex = 1;
    bool hasChanged = false;

    outSS << temp;
//If there are no operations to be done, return the original expression
    if (!NotComplete(temp, "*/%+-", operatorIndex)){
        completedSteps = outSS.str();
        return outSS.str();
    }
    else {
        outSS << " = ";
        //Do *, /, and % operations
        GenerateSteps(temp, outSS, "*/%", hasChanged, expressionLength);
        operatorIndex = 0;
        //If any *, /, or % operations have been done and + or - operations can be done, generate formatting
        if (hasChanged && NotComplete(temp, "+-", operatorIndex)){
            outSS << "\n" << setw(expressionLength + 3) << " = ";
        }
        //Do + and - operations
        GenerateSteps(temp, outSS, "+-", hasChanged, expressionLength);

        completedSteps = outSS.str();
        return completedSteps;
    }
}