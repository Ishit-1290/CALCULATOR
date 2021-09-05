#include "Logic.h"
#include <string>
using namespace std;
Logic::Logic() {

}

Logic::~Logic() {

}

double Logic::Calculate(std::string equation) {
	for (int i = 0; i < equation.length(); i++) {
		if (equation[i] == ')') {
			int j;
			for (j = i - 1; j >= 0; j--) {
				if (equation[j] == '(') {
					break;
				}
			}
			BracketSolver(equation, j + 1, i - 1);
		}
	}
	for (int i = 0; i < equation.length(); i++) {
		if (equation[i] == '(' || equation[i] == ')') {
			
			equation[i] = ' ';
		}
	}

	Division(equation, 0, equation.length());
	Multiplication(equation, 0, equation.length());
	double result = 0;
	for (int i = 0; i < equation.length(); ) {
		if (equation[i] >= '0' && equation[i] <= '9' || equation[i] == '.') {
			result = ConsecNum(equation, i);
			i++;
			while ((equation[i] >= '0' && equation[i] <= '9') || equation[i] == ' ' || equation[i] == '.') {
				i++;
				if (i == equation.length()) {
					break;
				}
			}
		}
		else if (equation[i] == '+') {
			result = result + ConsecNum(equation, i + 1);
			i++;
			while ((equation[i] >= '0' && equation[i] <= '9') || equation[i] == ' ' || equation[i] == '.') {
				i++;
				if (i == equation.length()) {
					break;
				}
			}
		}
		else if (equation[i] == '-') {
			result = result - ConsecNum(equation, i + 1);
			i++;
			while ((equation[i] >= '0' && equation[i] <= '9') || equation[i] == ' ' || equation[i] == '.') {
				i++;
				if (i == equation.length()) {
					break;
				}
			}
		}
		else {
			i++;
		}
	}
	return result;
}

void Logic::BracketSolver(std::string& eq, int start, int end) {
	float result = 0;  
	bool Found = false;  

	Division(eq, start, end);
	Multiplication(eq, start, end);
	for (int i = start; i <= end; ) {
		if (eq[i] >= '0' && eq[i] <= '9') {
			result = ConsecNum(eq, i);
			i++;
			while ((eq[i] >= '0' && eq[i] <= '9') || eq[i] == ' ' || eq[i] == '.') {
				i++;
				if (i == end) {
					i++;
					break;
				}
			}

		}
		else if (eq[i] == '+') {
			Found = true;
			result = result + ConsecNum(eq, i + 1);
			i++;
			while ((eq[i] >= '0' && eq[i] <= '9') || eq[i] == ' ' || eq[i] == '.') {
				i++;
			}
		}
		else if (eq[i] == '-') {
			Found = true;
			result = result - ConsecNum(eq, i + 1);
			i++;
			while ((eq[i] >= '0' && eq[i] <= '9') || eq[i] == ' ' || eq[i] == '.') {
				i++;
			}
		}
		else {
			i++;
		}
	}
	if (!Found) {
		return;
	}
	result = roundoff(result, 2);
	std::string resString = std::to_string(result);
	std::string Res = "";
	for (int x = 0; x < resString.length() - 4; x++) {
		Res = Res + resString[x];
	}
	bool oneTime = true;
	for (int i = start; i <= end; i++) {
		int index = 0;
		while (index < Res.length() && oneTime) {
			eq[i] = Res[index];
			index++;
			i++;
		}
		oneTime = false;
		if (i <= end) {
			eq[i] = ' ';
		}
	}
}

void Logic::Multiplication(std::string& eq, int start, int end) {
	for (int i = start; i <= end; i++) {
		if (eq[i] == '*' || eq[i] == 'x') {
			eq.append(" ");
			double multiplier = this->ConsecNum(eq, i + 1);
			int endMultiplyIndex = 0;
			for (int j = i + 1; j <= end; j++) {
				if ((eq[j] >= '0' && eq[j] <= '9') ||  eq[j] == '.') {
					endMultiplyIndex = j;
				}
				else {
					break;
				}
			}
			double multiplicand = 0.0;
			int startMultiplyIndex;
			for (startMultiplyIndex = i - 1; startMultiplyIndex >= 0; startMultiplyIndex--) {
				if ((eq[startMultiplyIndex] >= '0' && eq[startMultiplyIndex] <= '9') || eq[startMultiplyIndex] == ' ' || eq[startMultiplyIndex] == '.') {
					continue;
				}
				else {
					multiplicand = ConsecNum(eq, startMultiplyIndex+1);
					startMultiplyIndex++;
					break;
				}
			}
			if (multiplicand == 0) {
				startMultiplyIndex = 0;
				multiplicand = ConsecNum(eq, 0);
			}
			double product = multiplicand * multiplier;
			string Product = to_string(product);
			Product.resize(Product.length() - 4);
			string copyEQ = eq;
			
			if (endMultiplyIndex + 1 != eq.length()-1) {
				eq[endMultiplyIndex + 1] = ' ';
			} 
			
			for (int x = endMultiplyIndex + 2; x < copyEQ.length(); x++) {
				eq[x] = copyEQ[x - 1];	
			}
			for (int x = startMultiplyIndex; x <= endMultiplyIndex; x++) {
				eq[x] = ' ';
			}
			for (int x = 0; x < Product.length(); x++) {
				eq[x + startMultiplyIndex] = Product[x];
			}
		}
	}
}


void Logic::Division(std::string& eq, int start, int end) {
	for (int i = start; i <= end; i++) {
		if (eq[i] == '/' ) {
			eq.append(" ");
			double divisor = this->ConsecNum(eq, i + 1);
			int endDivisionIndex = 0;
			for (int j = i + 1; j <= end; j++) {
				if ((eq[j] >= '0' && eq[j] <= '9') || eq[j] == '.') {
					endDivisionIndex = j;
				}
				else {
					break;
				}
			}
			double Dividend = 0.0;
			int startMultiplyIndex;
			for (startMultiplyIndex = i - 1; startMultiplyIndex >= 0; startMultiplyIndex--) {
				if ((eq[startMultiplyIndex] >= '0' && eq[startMultiplyIndex] <= '9') || eq[startMultiplyIndex] == ' ' || eq[startMultiplyIndex] == '.') {
					continue;
				}
				else {
					Dividend = ConsecNum(eq, startMultiplyIndex + 1);
					startMultiplyIndex++;
					break;
				}
			}
			if (Dividend == 0) {
				startMultiplyIndex = 0;
				Dividend = ConsecNum(eq, 0);
			}
			if (divisor == 0) {
				eq = "inf";
				return;
			}
			double product = Dividend / divisor;
			string Product = to_string(product);
			Product.resize(Product.length() - 4);
			string copyEQ = eq;

			if (endDivisionIndex + 1 != eq.length() - 1) {
				eq[endDivisionIndex + 1] = ' ';
			}

			for (int x = endDivisionIndex + 2; x < copyEQ.length(); x++) {
				eq[x] = copyEQ[x - 1];
			}
			for (int x = startMultiplyIndex; x <= endDivisionIndex; x++) {
				eq[x] = ' ';
			}
			for (int x = 0; x < Product.length(); x++) {
				eq[x + startMultiplyIndex] = Product[x];
			}
		}
	}
}
double Logic::ConsecNum(const std::string& eq, int n) {
	double result = 0;
	bool decimal = false;
	double a = 10.0;
	
	for (int i = n; i < eq.length(); i++) {
		if (eq[i] >= '0' && eq[i] <= '9' && !decimal) {
			result = result * 10 + (eq[i] - 48.0);
		}
		else if (eq[i] == '.') {
			decimal  = true;
		}
		else if (eq[i] >= '0' && eq[i] <= '9' && decimal) {
			result = result + ((eq[i] - 48) /a);
			a = a * 10.0;
		}
		else if (eq[i] == ' ') {
			continue;
		}
		else {
			break;
		}
	}
	return result;
}
float Logic::roundoff(float value, unsigned char prec) {
	float pow_10 = pow(10.0f, (float)prec);
	return round(value * pow_10) / pow_10;
}