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
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 rnd(seed);
    uniform_int_distribution<ll> randInt(1,100);
    uniform_real_distribution<double> randFlo(0,100);
    for(int i = 0; i < 100; i++) cout << randInt(rnd) << ' ';
    for(int i = 0; i < 100; i++) cout << randFlo(rnd) << ' ';

    vector<ll> vec(100);
    iota(vec.begin(),vec.end(),1); //배열엘 1~100값을 순차적으로 채움
    for(auto c :vec) cout << c << ' ';
    shuffle(vec.begin(),vec.end(),rnd); //셔플, 랜덤엔진을 인자로
    for(auto c :vec) cout << c << ' ';
    
	set<pos> test1;
	unordered_set<pos, pos_hash> test2;

	pos p1(10, 20);
	pos p2(30, 30);

	test1.insert(p1);
	test2.insert(p2);
}
