#pragma once
#include <iostream>
class Logic
{
public:
	Logic();
	~Logic();

	double Calculate(std::string equation);
	double BracketSolver(std::string& eq, int start, int end);
	double ConsecNum(std::string eq, int n);
	void Division(std::string& eq, int start, int end);
	void Multiplication(std::string& eq, int start, int end);
	float roundoff(float value, unsigned char prec);
};

