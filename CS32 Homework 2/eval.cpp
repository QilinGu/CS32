#include <iostream>
#include <string>
#include <cassert>
#include <stack>
using namespace std;

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
	postfix = "";
	stack<char> operatorStack;

	for (int k = 0; k < infix.length(); k++) //removing spaces
	{
		if (infix[k] == ' ')
		{
			infix.erase(infix.begin() + k);
			k--;
		}
	}

	if (infix.length() == 0)
		return 1;

	for (int i = 0; i < infix.length(); i++)
	{
		switch (infix[i])
		{
		case '0': case '1': case '2': case '3': case '4': case '5':case '6':case '7':case '8': case '9':
			postfix += infix[i];
			while (operatorStack.empty() == false && operatorStack.top() == '!')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			if ((i + 1) < infix.length() && !(infix[i + 1] == '&' || infix[i + 1] == '|' || infix[i + 1] == ')'))
				return 1;
			break;
		case '(':
			if ((i + 1) < infix.length() && !(infix[i + 1] >= '0' && infix[i + 1] <= '9' || infix[i + 1] == '(' || infix[i + 1] == '!'))
				return 1;
			operatorStack.push(infix[i]);
			break;
		case ')':
			if (i < 2)
				return 1;
			if ((i + 1) < infix.length() && !(infix[i + 1] == '&' || infix[i + 1] == '|' || infix[i + 1] == ')'))
				return 1;			
			while (operatorStack.empty() == false && operatorStack.top() != '(')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.pop();
			while (operatorStack.empty() == false && operatorStack.top() == '!')
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			break;
		case '&': case'|': 
			if (i == 0 || i == infix.length()-1)
				return 1;
			if ((i + 1) < infix.length() && !(infix[i + 1] >= '0' && infix[i + 1] <= '9' || infix[i + 1] == '(' || infix[i + 1] == '!'))
				return 1;
			while (operatorStack.empty() == false && operatorStack.top() != '(' && (infix[i] == operatorStack.top() || infix[i] == '|' || (infix[i] == '&' && operatorStack.top() != '|')))
			{
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(infix[i]);
			break;
		case '!':
			if ((i + 1) < infix.length() && !(infix[i + 1] >= '0' && infix[i + 1] <= '9' || infix[i + 1] == '(' || infix[i + 1] == '!'))
				return 1;
			operatorStack.push(infix[i]);
			break;
		}
	}
	while (operatorStack.empty() == false)
	{
		postfix += operatorStack.top();
		operatorStack.pop();
	}

	//cerr << postfix << endl;

	stack<bool> operandStack;
	bool operand1, operand2;
	for (int j = 0; j < postfix.length(); j++)
	{
		if (postfix[j] >= '0' && postfix[j] <= '9')
		{
			operandStack.push(values[postfix[j] - '0']);
		}
		else if (postfix[j] == '!')
		{
			operand1 = operandStack.top();
			operandStack.pop();
			operandStack.push(!operand1);
		}
		else if (postfix[j] == '&' || postfix[j] == '|')
		{
			operand2 = operandStack.top();
			operandStack.pop();
			operand1 = operandStack.top();
			operandStack.pop();
			switch (postfix[j])
			{
			case '&':
				operandStack.push(operand1 * operand2);
				//cerr << operand1 * operand2 << endl;
				break;
			case '|':
				operandStack.push(operand1 + operand2);
				//cerr << operand1 + operand2 << endl;
				break;
			}
		}
		else
			return 1;
	}
	result = operandStack.top();
	return 0;
}

int main()
{
	bool ba[10] = {
		//  0      1      2      3      4      5      6      7      8      9
		true, true, true, false, false, false, true, false, true, false
	};
	string pf;
	bool answer;
	assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" &&  answer);
	assert(evaluate("8|", ba, pf, answer) == 1);
	assert(evaluate("4 5", ba, pf, answer) == 1);
	assert(evaluate("01", ba, pf, answer) == 1);
	assert(evaluate("()", ba, pf, answer) == 1);
	assert(evaluate("2(9|8)", ba, pf, answer) == 1);
	assert(evaluate("2(&8)", ba, pf, answer) == 1);
	assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
	assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
		&& pf == "43!03&&|"  &&  !answer); 
	assert(evaluate("", ba, pf, answer) == 1); 
	assert(evaluate(" 9  ", ba, pf, answer) == 0 && pf == "9"  &&  !answer);
	ba[2] = false;
	ba[9] = true;
	assert(evaluate("((9))", ba, pf, answer) == 0 && pf == "9"  &&  answer);
	assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" &&  !answer);
	cout << "Passed all tests" << endl;
}

// Evaluates a boolean expression
// Postcondition: If infix is a syntactically valid infix boolean
//   expression, then postfix is set to the postfix form of that
//   expression, result is set to the value of the expression (where
//   in that expression, each digit k represents element k of the
//   values array), and the function returns zero.  If infix is not a
//   syntactically valid expression, the function returns 1.  (In that
//   case, postfix may or may not be changed, but result must be
//   unchanged.)
/*
int main()
{
	bool ba[10] = {
		// 0     1     2     3      4      5     6      7     8      9
		false, true, true, false, false, false, true, false, true, false
	};
	string postfix; bool result;
	string infix = "";
	cout << "Error code is " << evaluate(infix, ba, postfix, result) << endl;
	cout << "Result is " << result << endl;
} */