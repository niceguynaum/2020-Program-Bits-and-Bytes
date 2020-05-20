// ProbCalc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Calculate.h"
#include <iostream>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

// Calculator that takes in input probability and time then outputs a result

// Tag list:
/*
		-ip = input percentage
		-it = input time

*/

// PsudoCode:
/*
	Binomial Probability Calculation (time is constant 1):

	User input: -ip 1 4 67 5~
	Data collected Input percentages 1%, 4%, 67%, and 5%.
	Probability is calculated
	Probability is output.

	Binomial Probability Calculation (time is variable):

	example, percentages are calculated on a per day basis
	where the user inputs a value, then a set amount of days.
	the program then outputs the percentage with those days implemented.

	User input: -ip 20 4 67 5~ -it 7
	Data collected Input percentages 20%, 4%, 67%, and 5%. Time Input factor is 7.
	Probability is calculated
	Probability is output for each time factor.

*/

int main()
{
	std::string Input = "";
	std::cout << "Please Enter specifying tags followed by Data Values. To complete an input, end the data input with the character '~'.\n" << std::endl;
	std::cout << "Enter 'help' For a list of tags" << std::endl;
	std::getline(std::cin, Input);
	Calculate::TagParse(Input);
	Calculate::EquationOutput();
}
