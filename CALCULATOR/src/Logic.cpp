#include "Logic.h"
#include <string>
using namespace std;
Logic::Logic() {

}

Logic::~Logic() {

}

int Logic::Calculate(std::string equation) {
	for (int i = 0; i < equation.length(); i++) {
		if (equation[i] == ')') {
			int j;
			for (j = i - 1; j > 0; j--) {
				if (equation[j] == '(') {
					break;
				}
			}
			BracketSolver(equation, j + 1, i - 1);
			equation[j] = ' ';
			equation[i] = ' ';
		}
	}

	//Division
	Division(equation, 0, equation.length());
	//Multiplication
	Multiplication(equation, 0, equation.length());

	std::cout << equation << "\n\n";
	int result = 0;
	for (int i = 0; i < equation.length(); ) {

		if (equation[i] >= '0' && equation[i] <= '9') {
			result = ConsecNum(equation, i);
			i++;
			while ((equation[i] >= '0' && equation[i] <= '9') || equation[i] == ' ') {
				i++;
			}

		}
		else if (equation[i] == '+') {
			result = result + ConsecNum(equation, i + 1);
			i++;
			while ((equation[i] >= '0' && equation[i] <= '9') || equation[i] == ' ') {
				i++;
			}
		}
		else if (equation[i] == '-') {
			result = result - ConsecNum(equation, i + 1);
			i++;
			while ((equation[i] >= '0' && equation[i] <= '9') || equation[i] == ' ') {
				i++;
			}
		}
	}
	return result;
}
int Logic::BracketSolver(std::string& eq, int start, int end) {
	int result = 0;

	Division(eq, start, end);
	Multiplication(eq, start, end);
	return result;
}

void Logic::Multiplication(std::string& eq, int start, int end) {
	for (int i = start; i <= end; i++) {
		if (eq[i] == '*') {
			int multiplier = ConsecNum(eq, i + 1);
			int endpoint = 0;
			for (int x = i + 1; x < eq.length(); x++) {
				if ((eq[x] >= '0' && eq[x] <= '9') || eq[x] == ' ') {
					continue;
				}
				endpoint = x - 1;
				break;
			}
			int j;
			for (j = i - 1; j > 0; j--) {
				if ((eq[j] >= '0' && eq[j] <= '9') || eq[j] == ' ') {
					continue;
				}
				break;
			}
			int multiplicand = ConsecNum(eq, j + 1);
			int product = multiplicand * multiplier;
			std::string strquotient = to_string(product);
			bool found = true;
			for (int x = (j + 1); x <= endpoint; x++) {
				int index = 0;
				while (index < strquotient.length() && found) {
					eq[x] = strquotient[index];
					x++;
					index++;
				}
				found = false;
				eq[x] = ' ';
			}
		}
	}
}

void Logic::Division(std::string& eq, int start, int end) {
	for (int i = start; i <= end; i++) {
		if (eq[i] == '/') {
			int divisor = ConsecNum(eq, i + 1);
			int endpoint = 0;
			for (int x = i + 1; x < eq.length(); x++) {
				if ((eq[x] >= '0' && eq[x] <= '9') || eq[x] == ' ') {
					continue;
				}
				endpoint = x - 1;
				break;
			}
			int j;
			for (j = i - 1; j > 0; j--) {
				if ((eq[j] >= '0' && eq[j] <= '9') || eq[j] == ' ') {
					continue;
				}
				break;
			}
			int dividend = ConsecNum(eq, j + 1);
			int quotient = dividend / divisor;
			std::string strquotient = to_string(quotient);
			bool found = true;
			for (int x = (j + 1); x <= endpoint; x++) {
				int index = 0;
				while (index < strquotient.length() && found) {
					eq[x] = strquotient[index];
					x++;
					index++;
				}
				found = false;
				eq[x] = ' ';
			}
		}
	}
}
int Logic::ConsecNum(std::string eq, int n) {
	int result = 0;
	for (int i = n; i < eq.length(); i++) {
		if (eq[i] >= '0' && eq[i] <= '9') {
			result = result * 10 + (eq[i] - 48);
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