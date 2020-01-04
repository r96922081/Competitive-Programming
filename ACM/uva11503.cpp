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
	virtual void AddCount(int adding_count);
private:
	vector<int> parent;
	vector<int> rank;
};

class SegmentTree
{
public:
	SegmentTree(const vector<int>& orignal_array);
	int Min(int left, int right);
	void Update(int index, int key);

private:
	int BuildTree(int index, int left, int right);
	int Min(int index, int q_l, int q_r, int l, int r);

	vector<int> A;
	vector<int> tree;
	int tree_node_count;
};

char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

class UnionFind2 : public UnionFind
{
public:
	UnionFind2(int count) : UnionFind(count), size(vector<int>(count, 1)) {}

	int Union2(int key1, int key2) 
	{
		if (Find(key1) == Find(key2))
			return size[Find(key1)];

		int size1 = size[Find(key1)];
		int size2 = size[Find(key2)];
		Union(key1, key2);
		size[Find(key1)] = size1 + size2;
		return size[Find(key1)];
	}

	virtual void AddCount(int adding_count)
	{
		size.push_back(1);
		UnionFind::AddCount(adding_count);
	}

	vector<int> size;
};

void algorithm()
{
	int test_count = 0;
	scanf("%d", &test_count);

	for (int test_count_index = 0; test_count_index < test_count; test_count_index++)
	{
		int relation_count = 0;
		scanf("%d", &relation_count);
		map<string, int> name_map;
		UnionFind2 uf(0);

		for (int i = 0; i < relation_count; i++)
		{
			char name1[21];
			char name2[21];
			scanf("%s %s\n", name1, name2);

			if (name_map.find(name1) == name_map.end())
			{
				name_map.insert(pair<string, int>(name1, name_map.size()));
				uf.AddCount(1);
			}
			if (name_map.find(name2) == name_map.end())
			{
				name_map.insert(pair<string, int>(name2, name_map.size()));
				uf.AddCount(1);
			}

			cout << uf.Union2(name_map[name1], name_map[string(name2)]) << endl;

		}
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
	//extern void TestSegmentTree();
	//TestSegmentTree();
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
	for (size_t i = 0; i < s.size(); i++)
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
	return Find(key1) == Find(key2);
}

void UnionFind::AddCount(int adding_count)
{
	for (int i = 0; i < adding_count; i++)
	{
		rank.push_back(0);
		parent.push_back(parent.size());
	}
}

SegmentTree::SegmentTree(const vector<int>& orignal_array)
{
	A = orignal_array;
	tree = vector<int>(A.size() * 4);

	BuildTree(1, 0, pow(2, ceil(log2(A.size()))) - 1);
}

int SegmentTree::Min(int left, int right)
{
	return Min(1, left, right, 0, pow(2, ceil(log2(A.size()))) - 1);
}

void SegmentTree::Update(int index, int key)
{
	A[index] = key;
	int tree_i = index + pow(2, ceil(log2(A.size())));
	tree_i /= 2;

	while (tree_i > 0)
	{
		int l_min = tree[tree_i * 2];
		int r_min = tree[tree_i * 2 + 1];

		if (r_min == -1)
			tree[tree_i] = l_min;
		else
		{
			if (A[l_min] <= A[r_min])
				tree[tree_i] = l_min;
			else
				tree[tree_i] = r_min;
		}

		tree_i /= 2;
	}
}

int SegmentTree::BuildTree(int index, int left, int right)
{
	if (left == right)
	{
		tree[index] = left;
		return left;
	}

	size_t left_min = BuildTree(index * 2, left, (left + right) / 2);
	size_t right_min = BuildTree(index * 2 + 1, (left + right) / 2 + 1, right);

	int min = -1;
	if (right_min >= A.size())
	{
		min = left_min;
	}
	else
	{
		if (A[left_min] <= A[right_min])
			min = left_min;
		else
			min = right_min;
	}

	tree[index] = min;
	return min;
}

int SegmentTree::Min(int index, int q_l, int q_r, int l, int r)
{
	if (r < q_l || l > q_r)
		return -1;

	if (q_l <= l && r <= q_r)
		return tree[index];

	int l_min = Min(index * 2, q_l, q_r, l, (l + r) / 2);
	int r_min = Min(index * 2 + 1, q_l, q_r, (l + r) / 2 + 1, r);

	if (r_min == -1)
		return l_min;
	else if (l_min == -1)
		return r_min;

	if (A[l_min] <= A[r_min])
		return l_min;
	else
		return r_min;
}