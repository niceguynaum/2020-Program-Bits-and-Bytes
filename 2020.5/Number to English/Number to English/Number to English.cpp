/*
Write a program that takes an integer and displays the English name of that value.

You should support both positive and negative numbers, in the range 
supported by a 32-bit integer (approximately -2 billion to 2 billion).

*/

#include <iostream>
#include <string.h>

// first input: 1024

std::string sEnglishOut;
std::string sOneToTen[] = { "",
	"one", "two", "three", "four", "five",
	"six", "seven", "eight", "nine", "ten",
	"eleven", "twelve", "thirteen", "fourteen",
	"fifteen", "sixteen", "seventeen", "eighteen",
	"nineteen" };

std::string sTensToHundred[] = { "",
	"twenty", "thirty", "fourty", "fifty",
	"sixty", "seventy", "eighty", "ninety" };

std::string sPowerOfTen[] = {
	"", "thousand", "million", "billion" };

std::string padIfNeeded(std::string output)
{
	if (output == "") {
		return "";
	}
	return " " + output;
}
std::string translateHundred(int hundred_chunk) // Method to handle cases in the teens up to 100
{
	if (hundred_chunk < 20) {
		return sOneToTen[hundred_chunk];
	}
	int tens = hundred_chunk / 10;
	int ones = hundred_chunk % 10;
	return sTensToHundred[tens] + padIfNeeded(sOneToTen[ones]);
}

std::string translateThousand(int thousand_chunk)
{
	if (thousand_chunk < 100) {
		return translateHundred(thousand_chunk);
	}
	else {
		int hundreds = thousand_chunk / 100;
		int hundred_chunk = thousand_chunk % 100;
		return sOneToTen[hundreds]
			+ " hundred"
			+ padIfNeeded(translateHundred(hundred_chunk));
	}
}

int main()
{
	int iNumberInput = 0;
	std::string sNumber;
	bool is_negative = false;
	std::cout << "Please enter a positive or negative number (2 billion is the max): " << std::endl;
	std::cin >> iNumberInput;
	if (iNumberInput < 0) {
		is_negative = true;
		iNumberInput *= -1;
	}
	int chunk_count = 0;
	while (iNumberInput > 0) {
		if (iNumberInput % 1000 != 0) {
			sNumber = translateThousand(iNumberInput % 1000)
				+ padIfNeeded(sPowerOfTen[chunk_count]
				+ padIfNeeded(sNumber));
		}
		iNumberInput /= 1000;
		chunk_count++;
	}
	if (sNumber == "") {
		sNumber = "zero";
	}
	if (is_negative) {
		sNumber = "negative " + sNumber;
	}
	printf("%s\n", sNumber.c_str());
}