#include <iostream>
#include <string>
#include <vector>
#include "Stack.h"
#include "Postfix.h"

using namespace std;

int main()
{
	string nach;
	double result;
	cout << "Vvedite virazhenie: ";
	cin >> nach;
	try
	{
		Par parser(nach);
		cout << "Virazhenie: " << parser.getStand() << endl;
		parser._Postfix();
		cout << "Postfixnaya forma: " << parser.getPostfix() << endl;
		result = parser.Calculate();
		cout << "Resul'tat vichislenia: " << result << endl;
	}
	catch (const char* s)
	{
		cout << s;
	}
	return 0;
}