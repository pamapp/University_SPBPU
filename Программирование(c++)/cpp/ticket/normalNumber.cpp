#include <iostream>

using namespace std;

bool isNumber(const char* str, unsigned int& currentItem) {
	if (str[currentItem] >= '0' && str[currentItem] <= '9') {
		++currentItem;
		return true;
	}
	return false;
}

bool isLetter(const char* str, unsigned int& currentItem) {
	if (str[currentItem] >= 'a' && str[currentItem] <= 'e') {
		return true;
	}
	throw "false";
}

bool isIdentifier(const char* str, unsigned int& currentItem) {
	if (str[currentItem] == '*' or str[currentItem] == '/') return false;
	return isLetter(str, currentItem);
}
bool isUnsignedInteger(const char* str, unsigned int& currentItem) {
	if (isNumber(str, currentItem)) {
		if (isUnsignedInteger(str, currentItem)) {
			return true;
		}
		return true;
	}
	return false;
}

bool isMultiplier(const char* str, unsigned int& currentItem) {
	if (isUnsignedInteger(str, currentItem)) {
		if (isIdentifier(str, currentItem)) {
			return true;
		}
		return true;
	}
	else {
		if (isIdentifier(str, currentItem)) {
			return true;
		}
		return false;
	}
}
bool isTerm(const char* str, unsigned int& currentItem) {
	if (isMultiplier(str, currentItem)) {
		if (str[currentItem] == '*' || str[currentItem] == '/') {
			currentItem++;
			if (isTerm(str, currentItem)) {
				return true;
			}
		}
		return true;
	}
	return false;
}

bool isExpression(const char* str, unsigned int& currentItem) {
	if (isTerm(str, currentItem)) {
		if (str[currentItem] == '+' || str[currentItem] == '-') {
			currentItem++;
			if (isTerm(str, currentItem)) {
				return true;
			}
		}
		return true;
	}
	return false;
}
int main()
{
	try {
		// 11
		const int columns = 8;
		const int rows = 5;
		const char str[columns][rows] = { { '7', '*', 'b', '*', 'a' }, { '4', 'b', '+', '3', 'c' },
									   { '4', '5', '/', '3', 'a' }, { 'a', '-', '3', 'c', 'd' },
									   { '7', '/', '2', '*', 'a' }, { 'a', '/', 'b', '+', '6' },
									   { '7', '/', '5', '*', 'a' }, { '7', '2', 'b', '*', 'a' } };
		unsigned int currentItem = 0;
		for (int i = 0; i < columns; i++)
		{
			isExpression(str[i], currentItem) ? cout << "True" : cout << "False";
			currentItem = 0;
			cout << endl;

		}
	}
	catch (const char* message) {
		cerr << message << endl;
	}
}
