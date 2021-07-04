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

struct SegmentTreeNode
{
	SegmentTreeNode() : left(0), right(0), min(0) {}
	SegmentTreeNode(int left, int right, int min) : left(0), right(0), min(0) {}
	int left;
	int right;
	int min;
};

class SegmentTree
{
public:
	SegmentTree(vector<int> orignal_array);
	int Min(int left, int right);
	void Update(int index, int key);

private:
	int Min(int left, int right, int index);
	void BuildTree();
	SegmentTreeNode BuildNode(int index);
	vector<int> A; // original_array
	vector<SegmentTreeNode> tree;
	int A_start_pos;
	int A_end_pos;
};


char to_lower(char c);
string to_lower2(string s);
//////////////////// auxiliary functions /////////////////////

void algorithm()
{
	int test_count = 0;
	scanf("%d", &test_count);

	for (int test_count_i = 0; test_count_i < test_count; test_count_i++)
	{
		if (test_count_i > 0)
			cout << endl;

		int max_number = 0;
		scanf("%d\n", &max_number);

		UnionFind union_find(max_number + 1);
		string line = "";
		int answer_is_connected = 0;
		int answer_is_disconnected = 0;

		while (getline(cin, line), line != "")
		{
			char op = ' ';
			int pc1 = 0;
			int pc2 = 0;
			sscanf(line.c_str(), "%c %d %d", &op, &pc1, &pc2);

			if (op == 'c')
			{
				union_find.Union(pc1, pc2);
			}
			else
			{
				if (union_find.IsSameComponent(pc1, pc2))
					answer_is_connected++;
				else
					answer_is_disconnected++;
			}
		}

		cout << answer_is_connected << "," << answer_is_disconnected << endl;
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


SegmentTree::SegmentTree(vector<int> orignal_array) :
	A(orignal_array)
{
	A_start_pos = (int)pow(2, ceil(log2(A.size())));
	tree = vector<SegmentTreeNode>(A_start_pos * 2, SegmentTreeNode());
	A_end_pos = A_start_pos + A.size() - 1;
	BuildTree();
}

void SegmentTree::BuildTree()
{
	BuildNode(1);
}

SegmentTreeNode SegmentTree::BuildNode(int index)
{
	if (A_start_pos <= index && index <= A_end_pos)
	{
		tree[index].min = index;
		tree[index].left = index - A_start_pos;
		tree[index].right = index - A_start_pos;
		return tree[index];
	}
	else if (A_end_pos < index)
	{
		return SegmentTreeNode();
	}
	else
	{
		SegmentTreeNode left_node = BuildNode(index * 2);
		SegmentTreeNode right_node = BuildNode(index * 2 + 1);

		int min = 0;

		if (left_node.min != 0 && right_node.min != 0)
		{
			if (A[left_node.min - A_start_pos] < A[right_node.min - A_start_pos])
				min = left_node.min;
			else
				min = right_node.min;
		}
		else if (left_node.min != 0)
			min = left_node.min;
		else
			min = right_node.min;

		tree[index].min = min;
		tree[index].left = left_node.left;
		tree[index].right = max(left_node.right, max(right_node.left, right_node.right));

		return tree[index];
	}
}

int SegmentTree::Min(int left, int right)
{
	return Min(left, right, 1);
}

int SegmentTree::Min(int left, int right, int index)
{
	SegmentTreeNode& n = tree[index];

	if (n.left == left && n.right == right)
	{
		return n.min - A_start_pos;
	}

	SegmentTreeNode& left_node = tree[index * 2];
	SegmentTreeNode& right_node = tree[index * 2 + 1];

	if (left_node.right < left)
	{
		return Min(left, right, index * 2 + 1);
	}
	else if (right <= left_node.right)
	{
		return Min(left, right, index * 2);
	}
	else
	{
		int l_min = Min(left, left_node.right, index * 2);
		int r_min = Min(left_node.right + 1, right, index * 2 + 1);

		if (A[l_min] < A[r_min])
			return l_min;
		else
			return r_min;
	}
}

void SegmentTree::Update(int index, int key)
{
	A[index] = key;

	int parent_index = (index + A_start_pos) / 2;

	while (parent_index >= 1)
	{
		if (A[tree[parent_index * 2].min - A_start_pos] < A[tree[parent_index * 2 + 1].min - A_start_pos])
			tree[parent_index].min = tree[parent_index * 2].min;
		else
			tree[parent_index].min = tree[parent_index * 2 + 1].min;

		parent_index /= 2;
	}
}