#include <cstdio>
#include "stdlib.h"
#include "string.h"
#include <limits>
#include <cstddef>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <tuple>
#include <sstream>
#include <cassert>
#include <bitset>

using namespace std;

//////////////////// auxiliary functions /////////////////////
char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////


int algorithm()
{
	int N = 0;
	while (true)
	{
		scanf("%d", &N);
		if (N == 0)
			break;

		while (true)
		{
			int n;
			scanf("%d", &n);
			if (n == 0)
				break;

			int biggest = n;
			int prev_n = n;

			string result = "Yes";

			for (int i = 1; i < N; i++)
			{
				scanf("%d", &n);

				if (result != "No")
				{
					if (n > biggest)
					{
						biggest = n;
						prev_n = n;
					}
					else
					{
						if (n > prev_n)
						{
							result = "No";
						}

						prev_n = n;
					}
				}
			}

			cout << result << endl;
		}

		cout << endl;
	}

	return 0;
}

int main()
{	
	//extern void UnitTest();
	//UnitTest();
	return algorithm();
}

void Check(bool expr)
{
	if (!expr)
	{
		int a = 1;
		int b = 2;
		int c = a / b;
		assert(false);
	}

}

///////////////////// UT //////////////////////

void UnitTest()
{

}

//////////////////// auxiliary functions /////////////////////

char to_lower(char c)
{
	if ('a' <= c && c <= 'z')
		return c;
	else
		return c - 'A' + 'a';
}

string to_lower2(string s)
{
	string ret = "";
	for (int i = 0; i < s.size(); i++)
	{
		ret += to_lower(s[i]);
	}

	return ret;
}