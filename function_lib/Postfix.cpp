#include "Postfix.h"
#include <iostream>
#include <vector>

using namespace std;

Par::Par(string inf = "a + b")
{
	if (!Right(inf)) 
		throw " Ne correctno";
	for (int i = 0; i < inf.length(); i++)
		stand += inf[i];
	if (stand.length() < 1) 
		throw "Ne correctno";
}

bool Par::Right(string str)
{
	string symbols_z = "!@#$%^&№<>{}[]_=,.";// строка запрещенных символов
	int count = 0,  length = str.length();// счетчик скобок 
	for (int i = 0; i < length; i++)
	{
		if (symbols_z.find(str[i]) != string::npos)
			return false;
		if (str[i] == '(') count++;
		if (str[i] == ')') count--;
		}
	if (count != 0)
		throw (" many brackets");
	return true;
}

string Par::_Postfix()
{
	Stack<char> stack_s(MAX_SIZE);//символьный стак
	string t_symbols = "+-*/()";
	int length = stand.length();//Передаем размер строки инфикс
	for (int i = 0; i < length; i++)
	{
		if (t_symbols.find(stand[i]) == string::npos)
			postfix += stand[i];
		if (operands.find(stand[i + 1]) != string::npos)
			if (i != length)
				postfix += ' ';
		if (stand[i] == '(') stack_s.push(stand[i]);
		if (stand[i] == ')')
		{
			char t = stack_s.pop();
			while (t != '(')
			{
				postfix += t;
				t = stack_s.pop();
			}
		}
		if (operands.find(stand[i]) != string::npos)
		{
			if (stack_s.isEmpty())
				stack_s.push(stand[i]);
			else
			{
				int _index = operands.find(stand[i]);
				while (!stack_s.isEmpty())
				{
					char t = stack_s.pop();
					if (t == '(')
					{
						stack_s.push(t);
						break;
					}
					int t_index = operands.find(t);
					if (pr[t_index] >= pr[_index])
						postfix += t;
					else
					{
						stack_s.push(t);
						break;
					}
				}
				stack_s.push(stand[i]);
		
			}
			
		}
	}
	while (!stack_s.isEmpty())
		postfix += stack_s.pop();
	postfix += " ";
	return postfix;
		}

double Par::Calculate()
{
	if (stand.length() == 0) _Postfix();
	int lenght = postfix.length();
	Stack<double> result(MAX_SIZE);
	string Values;
	double* values = new double[lenght];
	for (int i = 0; i < lenght; i++)
	{
		if (operands.find(postfix[i]) == string::npos)
		{
			double t;
			//if ((postfix[i] < 48) || (postfix[i] > 57))
			if ((postfix[i] < '0') || (postfix[i] > '9'))
			{
				if (postfix[i] != ' ')
				{
					if (Values.find(postfix[i]) == string::npos)
					{
						Values += postfix[i];
						cout << "Enter the value of " << postfix[i] << ": ";
						cin >> t;
						values[Values.length() - 1] = t;
					}
					else
						t = values[Values.find(postfix[i])];
				}
				else
					continue;
			}
			else
			{
				string numb;
				while (postfix[i] != ' ')
				{
					numb += postfix[i];
					if (operands.find(postfix[i + 1]) != string::npos)
						break;
					i++;
				}
				t = stoi(numb);// извлекаем число из строки
			}
			result.push(t);
		}
		else
		{
			double o_Value, t_Value, th_Value;
			t_Value = result.pop();
			o_Value = result.pop();
			switch (postfix[i])
			{
			case '+':
				th_Value = o_Value + t_Value;
				break;
			case '-':
				th_Value = o_Value - t_Value;
				break;
			case '*':
				th_Value = o_Value * t_Value;
				break;
			case '/':
				th_Value = o_Value / t_Value;
				break;
			}
			result.push(th_Value);
		}
	}
	delete[] values;
	return result.pop();
}