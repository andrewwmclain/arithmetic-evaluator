# LAB 1 - Evaluation Steps

## Goal
Practice the methods offered by the C++ standard library string class by writing a C++ program that reads in an arithmetic expression and prints out a step by step evaluation of the expression.

## Sample Run

Here's a screen shot of a sample run:

![Sample Run](/images/EvaluationStepsScreenShot-1.png)

The main program runs in a loop.  On each iteration of the loop, the user enters an expression. The program will print out a step by step simplification of the expression until no more simplification can be done.  When a blank line is entered for the expression, the program ends.

## Files you are given
In this lab, you are given all the files you will need for your CLion project.  

* **CMakeLists.txt** - This contains the information necessary to build the project.  This file should not be modified.

*	**main.cpp** – This file has been completed for you.  It has the source for a simple main program that consists of a loop.  On each iteration of the loop, it prompts the user to enter an arithmetic expression.  If a blank line was entered, the loop terminates, and the program ends.  Otherwise, the string that was entered is passed to the function `GetEvalSteps`.  The main program then prints the return values from `GetEvalSteps`, and the loop repeats.  This file should not be modified.

*	**evalsteps.h** – This file has been completed for you as well.  It declares the function `GetEvalSteps`.  This file should not be modified.

*	**evalsteps.cpp** – This file contains a skeleton of the function of `GetEvalSteps`.  It’s your job to fill the missing parts of the file, including

    *	The header comment for the file,
    *	The header comment for the function
    *	The function implementation.  

The starter project does compile, and you can produce an executable, but the executable will assert after you enter an arithmetic expression to remind you that the function `GetEvalSteps` is not implemented.  You will want to remove the assert statement when you implement the function.


## What the function `GetEvalSteps` should do

When passed an arithmetic expression containing numbers and the binary operators `+`, `-`, `*`, `/`, and `%`, it will return a string that displays a step-by-step simplification of the expression, until you are left with the numerical result.   

For instance, when the string `2+3\*4-5` in the run captured in the previous screenshot was passed to `GetEvalSteps`, the function returned <pre>"2+3*4-5 = 2+12-5\n        = 14-5\n        = 9"</pre>  Note how extra blank characters are inserted into the string so that when it is output, the equal signs of each simplification step line up.

#### Important things to note about the format of the string returned by your function:

*	The string returned normally contains end of line characters (`\n`) so that when it is output to the console, the evaluation steps appear on separate lines.

*	The first line should start with the expression entered.  
  *	If no simplification can be done, your function should return the original expression.
  *	If just one simplification can be done, your function returns a string which is the concatenation of the original expression, a blank, an =, another blank, and then the simplified expression.
  *	If two simplifications can be done, then the string will start with the original expression, a blank, an =, another blank, and then the simplified expression.  Next comes \n, a series of blank characters, an = sign, and then the final simplification.
  *	If more than two simplifications can be done, continue as above appending more lines.
  *	Note that the string returned will **NOT** end in `\n`.

*	Exactly one addition, subtraction, multiplication, division or mod operation is handled on each step.   Follow the standard precedence and left -to-right evaluation rules.  In other words, `*`, `/`, and `%` are evaluated before `+` and `-`.  If there are multiple `*`, `/`, and `%` operations, go left to right.  When all the `*`, `/`, and `%` operators have been simplified out, then perform the `+` and `–` operations left to right.  All operations are to be integer operations.

*	All numbers appearing in the expression are non-negative integers, even though the result of the computation might be a negative integer.  You can assume that the numbers are small enough that they fit into the C++ integer type, and you can ignore the possibility of overflow when performing operations.

*	You are NOT supposed to handle a unary minus sign (or unary plus sign for that matter).  Just ignore it `–` for instance:

![Ignore Unary Operators](/images/EvaluationStepsScreenShot-2.png)

*	Characters appearing in the string that are neither digits nor one of the operators `+`, `-`, `*`, `/`, and `%` are to be ignored.  Just perform the operations that can be performed, and leave any other character where it is:

![Ignore Other Characters](/images/EvaluationStepsScreenShot-3.png)

*	The only situation where your function will be allowed to generate an exception (i.e. crash) is division by zero.  No points will be deducted if the program crashes in this situation.

![Division by zero](/images/EvaluationStepsScreenShot-4.png)

•	Do NOT try to “improve” on the above specification so that the output produced deviates from what is described above.  That will mean your program fails our testing, and you will lose correctness points.

## Some expectations for how you write the function GetEvalSteps

If you do not follow these expectations, you may have points deducted from your lab grade.

1.	_Good design_

    `GetEvalSteps` could be implemented with one single humongous, complicated single function, but you should NOT pursue that approach.  As you look at the problem, you will see that you will need to repeat some very similar logic two times because the five different operators cannot be handled at the same time.  You need to deal with `*`, `/`, `%` first, and then deal with `+`, `-`.  You SHOULD design a sub-function that you can call once for `*`, `/`, `%`, and then for `+`, `-`.   If you do this, the actual code for `GetEvalSteps` can be relatively short, and very easy to understand.

    This sub-function will likely involve a loop.  Inside the loop will be a complicated set of logic.  If you were to leave it as one function, it would still be complicated and difficult for another person to read.   You should move this inner logic into a second sub-function, so you have a clean loop that is easy to read.

    This kind of refinement is an important skill that needs to be developed.  “Clean”, understandable logic is essential so other programmers can understand your code, and verify it is correct.

    Since you will be creating a couple sub-functions, make sure any `string` parameters are passed by reference.  If a `string` parameter is not to be modified by the function, be sure to declare it `const`.

2.	_Use of `string` methods_ 

    One of the goals of this assignment is to learn how to use the methods of the `string` class.  Therefore, you should *use* them!  If you find yourself writing a loop to concatenate a lot of characters to the end of a string, to search for the position where a character occurs, or to replace some text in a string with some different text, you are doing something wrong.

    It is expected that you will make one or more uses of each of the following `string` class methods. See [C++ Reference](http://www.cplusplus.com/reference/string/string) for more information on the `string` class methods.

  * `string` fill constructor
  * `find_first_of` method
  * `replace` method
  * `substr` method

3.	_Other C++ library functionality you should take advantage of_

    It is also expected that you will use the following

  * `isdigit`   function
  * `stoi` function
  * `stringstream` class


4.	_Style_

    Your program needs to be orderly and readable.  If you are working a development team and don’t write clean looking code, you will be unpopular among your colleagues and may not work on that team very long.
    Because of this your program will be graded on style as well as correctness.  Please refer to the style guidelines discussed in class and in reading assignments concerning

  *	Indention of code
  *	Consistent use of {}, preferably Stroustrup style
  *	Meaningful names of identifiers
  *	Naming conventions for identifiers (camelCase for variables, CamelCase for function names. First word of a function name typically should be a verb.)
  *	No use of global variables. Global variables sometimes are appropriate, but not in the assignments we will be giving this quarter.
  *	Making sure object parameters are passed by reference (and declared const if appropriate)

5. _Documentation_

    At the start of your file you should have a header comment that gives the title of the assignment, the purpose, and your name.  Here is an example of what that could look like:

      ```
      /*
          Title:      Lab 1 – evalSteps.cpp
          Purpose:    implement the GetEvalSteps functions called by the main program to generate the evaluation
                      steps for an expression passed in as a parameter.
          Author:     Sally Johnson
          Date:       January 6, 2020
      */
      ```
    Each subordinate function should also start with a header that describes what it does, it’s parameters, what it returns, and how errors are handled.  Here is an example:

    ```
    // Produce a string of evaluation steps for simplifying an expression
    // For example:
    //      if “2+3*4-5”  is passed to this function, the string “2+3*4-5 = 2+12-5\n        = 14-5\n        = 9”
    //      would be returned
    // Parameters:
    //      expression - an arithmetic expression
    // Returns:
    //      a string consisting of the evaluation steps needed to simplify the expression
    // Possible Error Conditions:
    //      If evaluating the expression causes division by zero, this function crash.
    //      If evaluating the expression causes an overflow, the results may not be reliable.
    ```

    You should include additional comments in your code to describe what you are doing.   If it is hard to understand what a variable is for, add a comment after it.   It possible, though, to put in too many comments, so be judicious and make sure you have time left to do well in your other classes when it comes to commenting.

## Submitting your code
Your solution should be contained within a single C++ file, and that file must be named “evalsteps.cpp”. File names are case sensitive!

Make sure you test your code thoroughly.  We will run a series of tests on your function, and the strings you return must match character by character what is specified above.

Your code needs to be submitted through GitHub.  You will need to push your last version of your program before the lab deadline. As a good programming practice remember to commit frequently and to push every time you have a functioning version of your code.

## Grading
Correctness is essential.  Make sure your solution builds as described above and correctly handles the test cases displayed in the screen shot.  We will test on other input values as well. Your code must compile and should not have runtime errors (crash), except for the division by zero runtime error.

Even if your solution operates correctly, points will be taken off for:
- Not following the design described above
- Not adhering to style guidelines described above
- Using techniques not presented in class
- Programming error not caught by other testing
- Not following good programming practices

## Academic Integrity
This programming assignment is to be done on an individual basis. At the same time, it is understood that learning from your peers is valid and you are encouraged to talk among yourselves about programming in general and current assignments in particular.  Keep in mind, however, that each individual student must do the work in order to learn.  Hence, the following guidelines are established:
- Feel free to discuss any and all programming assignments but do not allow other students to look at or copy your code. Do not give any student an electronic or printed copy of any program you write for this class.
- Gaining the ability to properly analyze common programming errors is an important experience. Do not deprive a fellow student of his/her opportunity to practice problem solving: control the urge to show them what to do by writing the code for them.
- If you’ve given the assignment a fair effort and still need help, see the instructor or a lab assistant.
- **If there is any evidence that a program or other written assignment was copied from another student, neither student will receive any credit for it. This rule will be enforced.**
- Protect yourself: Handle throw-away program listings carefully, keep your repository private.

Refer to the ECS Department Policy on Academic Integrity that is included in the class syllabus.

## Grading Rubric Summary
The following aspects are going to be consider during grading. Make sure you comply with all of them.
- The program compiles (there will be **no partial credit** for programs that do not compile)
- Provides the correct output for the test cases
- Catches errors gracefully, the program does not crash on incorrect input
- The program outputs the information **in the specified format**
- The assignment follows all the instructions
- In general the program does not crash (except in when you enter an expression that causes zero division)
