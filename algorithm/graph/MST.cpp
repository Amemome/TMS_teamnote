#include <bits/stdc++.h>
using namespace std;

struct itriple
{
	int x, y, z;
	
	itriple() {}
	itriple(int x, int y, int z): x(x), y(y), z(z) {}
	bool operator<(const itriple& a) const
	{
		if (x < a.x)
			return true;
		else if (x > a.x)
			return false;

		if (y < a.y)
			return true;
		else if (y > a.y)
			return false;

		if (z < a.z)
			return true;
		
		return false;
	}
};

int disjoint_root(vector<int>& forest, int a)
{
	if (forest[a] == a)
		return a;

	forest[a] = disjoint_root(forest, forest[a]);
	return forest[a];
}

int disjoint_merge(vector<int>& forest, vector<int>& __size, int a, int b)
{
	int root_a = disjoint_root(forest, a);
	int root_b = disjoint_root(forest, b);

	if (root_a == root_b)
		return 0;

	if (__size[root_a] < __size[root_b])
	{
		forest[root_a] = root_b;
		__size[root_b] += __size[root_a];
	}
	else
	{
		forest[root_b] = root_a;
		__size[root_a] += __size[root_b];
	}

	return 1;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int v, e;
	cin >> v >> e;

	vector<itriple> edges(e);
	for (int i = 0; i < e; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		edges[i] = itriple(c, a, b);
	}
	sort(edges.begin(), edges.end());

	vector<int> forest(v+1);
	vector<int> __size(v+1);
	for (int i = 1; i <= v; i++)
	{
		forest[i] = i;
		__size[i] = 1;
	}

	int ans = 0;
	for (const itriple& edge : edges)
		ans += disjoint_merge(forest, __size, edge.y, edge.z) * edge.x;
	
	cout << ans << '\n';
	return 0;
}
