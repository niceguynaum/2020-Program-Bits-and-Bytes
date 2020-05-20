#pragma once
#include <vector>
#include <string>

std::vector<double> vdInputPercent;
std::vector<double> vdInputTime(1, 1);

struct Calculate
{
	void vInputParseP(std::string input);
	void vInputParseT(std::string input);
	static void TagParse(std::string Input);
	static double EquationOutput();
};