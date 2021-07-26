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
			bool removeBracket = BracketSolver(equation, j + 1, i - 1);
			equation[j] = ' ';
			if (!removeBracket)
				equation[i] = ' ';
		}
	}

	//Division
	Division(equation, 0, equation.length());
	//Multiplication
	Multiplication(equation, 0, equation.length());
	double result = 0;
	for (int i = 0; i < equation.length(); ) {
		if (equation[i] >= '0' && equation[i] <= '9') {
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
bool Logic::BracketSolver(std::string& eq, int start, int end) {
	double result = 0;

	bool removeBracket = Division(eq, start, end);
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
			result = result + ConsecNum(eq, i + 1);
			i++;
			while ((eq[i] >= '0' && eq[i] <= '9') || eq[i] == ' ' || eq[i] == '.') {
				i++;
			}
		}
		else if (eq[i] == '-') {

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
	result = roundoff(result, 2);
	std::string resString = std::to_string(result);
	std::string Res = "";
	for (int x = 0; x < resString.length() - 4; x++) {
		Res = Res + resString[x];
	}
	for (int i = start; i <= end; i++) {
		int index = 0;
		while (index <= Res.length()) {
			eq[i] = Res[index];
			index++;
			i++;
		}
	
		if (i <= end) {
			eq[i] = ' ';
		}
	}
	return removeBracket;
}

void Logic::Multiplication(std::string& eq, int start, int end) {
	eq.resize(eq.length()+1, ' ');
	for (int i = start; i <= end; i++) {
		if (eq[i] == '*' || eq[i] == 'x') {
			double multiplier = ConsecNum(eq, i + 1);
			int endpoint = 0;
			for (int x = i + 1; x < eq.length(); x++) {
				if ((eq[x] >= '0' && eq[x] <= '9') || eq[x] == ' ' || eq[x] == '.') {
					continue;
				}
				endpoint = x - 1;
				break;
			}
			if (endpoint == 0) {
				endpoint = end;
			}
			int j;
			for (j = i - 1; j >= 0; j--) {
				if ((eq[j] >= '0' && eq[j] <= '9') || eq[j] == ' ' || eq[j] == '.') {
					continue;
				}
				break;
			}
			double multiplicand = ConsecNum(eq, j + 1);
			double product = multiplicand * multiplier;
			product = roundoff(product, 2);
			std::string tempProduct = std::to_string(product);
			std::string Product = "";
			for (int i = 0; i < tempProduct.length() - 4; i++) {
				Product = Product + tempProduct[i];
			}
			bool found = true;
			for (int x = (j + 1); x <= endpoint; x++) {
				int index = 0;
				while (index < Product.length() && found) {
					eq[x] = Product[index];
					x++;
					index++;
				}
				found = false;
				if (x <= endpoint) {
					eq[x] = ' ';
				}
			}
		}
	}
}

bool Logic::Division(std::string& eq, int start, int end) {
	eq.resize(eq.length() + 1, ' ');
	for (int i = start; i <= end; i++) {
		if (eq[i] == '/') {
			double divisor = ConsecNum(eq, i + 1);
			int endpoint = 0;
			for (int x = i + 1; x < eq.length(); x++) {
				if ((eq[x] >= '0' && eq[x] <= '9') || eq[x] == ' ' || eq[x] == '.') {
					continue;
				}
				endpoint = x - 1;
				break;
			}
			if (endpoint == 0) {
				endpoint = end;
			}
			int j;
			for (j = i - 1; j >= 0; j--) {
				if ((eq[j] >= '0' && eq[j] <= '9') || eq[j] == ' ' || eq[j] == '.') {
					continue;
				}
				break;
			}
			
			double dividend = ConsecNum(eq, j + 1);
			double quotient = dividend / divisor;
			quotient = roundoff(quotient, 2);
			std::string tempQuotient = to_string(quotient);
			std::string Quotient = "";
			for (int i = 0; i < tempQuotient.length() - 4; i++) {
				Quotient = Quotient + tempQuotient[i];
			}

			bool found = true;
			for (int x = (j + 1); x <= endpoint; x++) {
				int index = 0;
				while (index < Quotient.length() && found) {
					
					eq[x] = Quotient[index];
					if (x == end+1) {
						return true;
					}
					x++;
					index++;

				}
				found = false;
				if (x <= endpoint) {
					eq[x] = ' ';
				}
			}
		}
	}
	return false;
}
double Logic::ConsecNum(std::string eq, int n) {
	double result = 0;
	bool decimal = false;
	double a = 10.0;
	eq = eq;
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