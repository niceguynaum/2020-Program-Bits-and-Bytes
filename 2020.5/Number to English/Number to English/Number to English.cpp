/*
Write a program that takes an integer and displays the English name of that value.

You should support both positive and negative numbers, in the range 
supported by a 32-bit integer (approximately -2 billion to 2 billion).

*/

#include <iostream>
#include <string.h>
#include <vector>
#include <array>
#include <cmath>

// first input: 1024

std::string sNumberOut(int iNumberInput)
{
	int iTensToHundred = 0;
	int iPowersOfTen = -1;
	std::vector<int> vStringArrayintStore;
	std::vector<std::string> vEnglishOut;
	std::string sEnglishOut;

	std::string sOneToTen[] = { "", 
		"one", "two", "three", "four", "five",
		"six", "seven", "eight", "nine", "ten",
		"eleven", "twelve", "thirteen", "fourteen",
		"fifteen", "sixteen", "seventeen", "eighteen",
		"nineteen" };

	std::string sTensToHundred[] = { "",
		"twenty", "thirty", "fourty", "fifty", 
		"sixty", "seventy", "eighty", "ninety"};

	std::string sPowerOfTen[] = {
		"", "hundred", "thousand", 
		"hundred thousand", "million", "billion"};

	for (int i = iNumberInput; i < 20;)
	{
		// a ternary operation that handles both power of ten size as well as 19 and below output.
		(i > 19) ? vStringArrayintStore.push_back(i%10), i/10, iPowersOfTen++: (iPowersOfTen = -1) ? vEnglishOut.push_back(sOneToTen[i]), i: i;
		if (i < 100 && i > 19) {

		}
	}

	//logic loop for output assembly
	for (int i = 0; i = vEnglishOut.size(); i++)
	{

		sEnglishOut = vEnglishOut[i] + " " + sEnglishOut;
	}

	if (iNumberInput < 0) sEnglishOut = "negative " + sEnglishOut;
	return sEnglishOut;
}


int main()
{
	int iNumberInput = 0;
	std::cout << "Please enter a number (2 billion is the max): " << std::endl;
	//std::cin >> iNumberInput;
	/*DEBUG*/ iNumberInput = 19;
	printf("%s\n", sNumberOut(iNumberInput).c_str());
	std::cout << iNumberInput;
}