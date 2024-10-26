#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;

struct pos
{
	int x, y;
	pos(): x(0), y(0) {}
	pos(int x, int y): x(x), y(y) {}

	// this comparator is analogous to std::less.
	bool operator<(const pos& another) const
	{
		if (x < another.x)
			return true;

		if (x > another.x)
			return false;

		if (y < another.y)
			return true;

		return false;
	}

	bool operator==(const pos& another) const
	{
		return x == another.x && y == another.y;
	}
};

hash<ull> ull_hash;

struct pos_hash
{
	size_t operator()(const pos& p) const
	{
		return ull_hash(((ull) p.y << 32) | (uint) p.x);
	}
};

int main()
{
	set<pos> test1;
	unordered_set<pos, pos_hash> test2;

	pos p1(10, 20);
	pos p2(30, 30);

	test1.insert(p1);
	test2.insert(p2);

	return 0;
}
