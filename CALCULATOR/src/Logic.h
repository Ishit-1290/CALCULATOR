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
	void BracketSolver(std::string& eq, int start, int end);
	double ConsecNum(const std::string& eq, int n);
	void Division(std::string& eq, int start, int end);
	void Multiplication(std::string& eq, int start, int end);
};

