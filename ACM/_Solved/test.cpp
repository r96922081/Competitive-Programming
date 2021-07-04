#include <vector>

#include "helper.h"

int main2()
{
	return 0;
}

void Check(bool expr);

void TestSegmentTree()
{
	SegmentTree t(vector<int> {0});
	Check(t.Min(0, 0) == 0);

	t = SegmentTree(vector<int>{ 1, 0 });
	Check(t.Min(0, 1) == 1);

	t = SegmentTree(vector<int>{ 2, 0, 1 });
	Check(t.Min(0, 2) == 1);

	t = vector<int>{ 9, 7, 1, 3, 5 };
	Check(t.Min(0, 4) == 2);
	Check(t.Min(0, 2) == 2);
	Check(t.Min(1, 1) == 1);
	Check(t.Min(2, 4) == 2);
	Check(t.Min(3, 4) == 3);


	t = vector<int>{ 3, 0, 1, 2 };
	Check(t.Min(1, 3) == 1);
	Check(t.Min(0, 2) == 1);
	Check(t.Min(1, 2) == 1);
	t.Update(1, 2);
	Check(t.Min(1, 3) == 2);
	Check(t.Min(0, 2) == 2);
	Check(t.Min(0, 1) == 1);
	t.Update(1, 0);
	Check(t.Min(1, 3) == 1);
	Check(t.Min(0, 2) == 1);
	Check(t.Min(0, 1) == 1);
	t.Update(3, 0);
	Check(t.Min(2, 3) == 3);
	Check(t.Min(0, 3) == 3 || t.Min(0, 3) == 1);


	t = vector<int>{ 18, 17, 13, 19, 15, 11, 20 };
	Check(t.Min(0, 6) == 5);
	Check(t.Min(3, 4) == 4);
	Check(t.Min(0, 1) == 1);
	Check(t.Min(4, 6) == 5);
	Check(t.Min(1, 3) == 2);
	Check(t.Min(4, 6) == 5);
	t.Update(5, 99);
	Check(t.Min(0, 6) == 2);
	Check(t.Min(3, 4) == 4);
	Check(t.Min(4, 6) == 4);
	t.Update(6, 1);
	Check(t.Min(4, 6) == 6);

	t = vector<int>{ 0, 0, 0 };
	t.Update(0, 0);
	t.Update(1, 0);
	t.Update(2, 0);
}

void TestBinaryIndexTree()
{
	int f[] = { 2,4,5,5,6,6,6,7,7,8,9 };
	BinaryIndexTree fenwick_tree(10);

	for (int i = 0; i < sizeof(f) / sizeof(int); i++)
		fenwick_tree.Adjust(f[i], 1);

	Check(fenwick_tree.RangeSumQuery(1, 1) == 0);
	Check(fenwick_tree.RangeSumQuery(1, 2) == 1);
	Check(fenwick_tree.RangeSumQuery(1, 6) == 7);
	Check(fenwick_tree.RangeSumQuery(1, 10) == 11);
	Check(fenwick_tree.RangeSumQuery(3, 6) == 6);
	fenwick_tree.Adjust(5, 2);
	Check(fenwick_tree.RangeSumQuery(1, 10) == 13);
}