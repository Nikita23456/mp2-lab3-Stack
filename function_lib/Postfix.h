#pragma once
#include "Stack.h"
#include <vector>

using namespace std;

class Par
{
	string stand;
	string postfix;
	string operands = "+-*/";
	bool Right(string str);
public:
	Par(string inf);
	string getStand() { return stand; }
	string getPostfix() { return postfix; }
	string _Postfix();
	double Calculate();
};
