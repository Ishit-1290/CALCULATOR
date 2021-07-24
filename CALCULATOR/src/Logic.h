#pragma once
#include <iostream>
class Logic
{
public:
	Logic();
	~Logic();

	int Calculate(std::string equation);
	int BracketSolver(std::string& eq, int start, int end);
	int ConsecNum(std::string eq, int n);
	void Division(std::string& eq, int start, int end);
	void Multiplication(std::string& eq, int start, int end);
};

