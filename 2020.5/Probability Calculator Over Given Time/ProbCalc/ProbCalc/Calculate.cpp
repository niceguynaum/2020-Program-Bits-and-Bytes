#include "Calculate.h"
#include <math.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

static void TagParse(std::string Input) {
	std::string sTagParsep = ""; 
	std::string sTagParset = "";
	for (int i = 0; i < Input.size(); i++)
	{
		if (Input[i] == '-' && Input[i + 1] == 'i') { // parsing for the user input tag -Input or -i
			switch (Input[i + 2]) {
			case 'p': for (char c = Input[i]; c = '~'; ++i) {
				sTagParsep += c;
			} break;
			case 't': for (char c = Input[i]; c = '~'; ++i) {
				sTagParset += c;
			} break;
			default: break;
			}
		}
	}
	vInputParseP(sTagParsep);
	vInputParseT(sTagParset);
}

// '0' is ascii value 48

// parses input after tag selection. Ex: " 1 4 67 5"
void vInputParseP(std::string input){
	std::istringstream stm(input);
	double n;
	while (stm >> n) vdInputPercent.push_back(n);
}

// parses input after tag selection.
void vInputParseT(std::string input) {
	std::istringstream stm(input);
	double n;
	while (stm >> n) vdInputTime.push_back(n);
}

// Formula:
/*
	Binomial Probability Formula:
		n = total number of trials
		x = total number of successful trials
		p = probability of success in a single trial
		q = probability of failure in a single trial = 1-p
				// q is technically not necessary and can be easily replaced with (1-p)

		Probability(x) = ((n!) / (x! * (N - x)!) * (p^x) * ((q)^(n-x))
*/

double factorialCalc(double input){
	for (int i = 1; i <= input; ++i) {
		input *= i;
	}
}

static double EquationOutput(int success, double prob) {
	double value = 0.0;
	if (vdInputTime[0] != 1) {
		(factorialCalc(vdInputPercent.size()) / (factorialCalc(success) * factorialCalc(vdInputPercent.size() - success)) * pow(prob, vdInputPercent.size()) * pow((1 - prob), (vdInputPercent.size() - success)));

		return value;
	}
}