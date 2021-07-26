#pragma once
#include <iostream>
class Logic
{
public:
	Logic();
	~Logic();
public:
	double Calculate(std::string equation);
	float roundoff(float value, unsigned char prec);
private:
	bool BracketSolver(std::string& eq, int start, int end);
	double ConsecNum(std::string eq, int n);
	bool Division(std::string& eq, int start, int end);
	void Multiplication(std::string& eq, int start, int end);
};

