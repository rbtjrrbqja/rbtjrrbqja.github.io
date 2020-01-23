// 2020-01-23
// algospot BRAKETS2
// https://algospot.com/judge/problem/read/BRACKETS2

#include <iostream>
#include <stack>

using namespace std;

const string yes = "YES";
const string no  = "NO";

bool check(string brakets)
{
	int len = brakets.length();

	stack<char> s;

	for (int i = 0; i < len; i++)
	{
		if (brakets[i] == '(' || brakets[i] == '{' || brakets[i] == '[')
			s.push(brakets[i]);
		else
		{
			if (s.empty())
				return false;
			else
			{
				if (brakets[i] == ')')
				{
					if (s.top() == '(')
						s.pop();
					else
						return false;
				}
				else if (brakets[i] == '}')
				{
					if (s.top() == '{')
						s.pop();
					else
						return false;
				}
				else if (brakets[i] == ']')
				{
					if (s.top() == '[')
						s.pop();
					else
						return false;
				}
			}
		}
	}

	return s.empty();
}

int main()
{
	int C;
	cin >> C;

	while (C--)
	{
		string brakets;
		cin >> brakets;

		if (check(brakets))
			cout << yes << endl;
		else
			cout << no << endl;
	}

	return 0;
}