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
#include <stack>
#include <queue>
#include <functional>

using namespace std;

//////////////////// auxiliary functions /////////////////////
class UnionFind
{
public:
	UnionFind(int count);
	int Find(int key);
	void Union(int key1, int key2);
	bool IsSameComponent(int key1, int key2);
private:
	vector<int> parent;
	vector<int> rank;
};

char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

void algorithm()
{
	int test_count = 0;
	scanf("%d", &test_count);

	for (int test_index = 0; test_index < test_count; test_index++)
	{
		string line = "";

		UnionFind union_find(26);

		while (getline(cin, line), line[0] != '*')
		{
			// no edge
			if (line[0] != '(')
				continue;

			char vertex1;
			char vertex2;
			sscanf(line.c_str(), "(%c,%c)\n", &vertex1, &vertex2);
			union_find.Union(vertex1 - 'A', vertex2 - 'A');
		}

		int count[26];
		memset(&count, 0, sizeof(int) * 26);
		char vertex;
		scanf("%c", &vertex);
		count[union_find.Find(vertex - 'A')]++;

		while (scanf(",%c", &vertex) == 1)
			count[union_find.Find(vertex - 'A')]++;

		scanf("\n");

		int acorn_count = 0;
		int tree_count = 0;
		for (int i = 0; i < 26; i++)
			if (count[i] > 1)
				tree_count++;
			else if (count[i] == 1)
				acorn_count++;

		printf("There are %d tree(s) and %d acorn(s).\n", tree_count, acorn_count);
	}
}

int main()
{
	//extern void UnitTest();
	//UnitTest();
	algorithm();
	return 0;
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

UnionFind::UnionFind(int count) : parent(vector<int>(count, 0)), rank(vector<int>(count, 0)) 
{
	for (int i = 0; i < count; i++)
		parent[i] = i;
}

int UnionFind::Find(int key)
{
	if (parent[key] != key)
		parent[key] = Find(parent[key]);

	return parent[key];
}
	
void UnionFind::Union(int key1, int key2)
{
	int u1 = Find(key1);
	int u2 = Find(key2);

	if (rank[u1] > rank[u2])
	{
		parent[u2] = u1;
	}
	else
	{
		parent[u1] = u2;
		if (rank[u1] == rank[u2])
			rank[u2]++;
	}
}

bool UnionFind::IsSameComponent(int key1, int key2)
{
	return parent[key1] == parent[key2];
}