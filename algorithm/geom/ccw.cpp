#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;

// vector cross product.
static inline ll __pi_cross(const pi& a, const pi& b)
{
	return (ll) a.first*b.second - (ll) a.second*b.first;
}

// orientation of 3 points: -1 (clockwise), 0 (linear), 1 (counterclockwise)
static inline int __pi_ort(const pi& a, const pi& b, const pi& c)
{
	return __reduce(__pi_cross(ab_vector, bc_vector));
}

// convex hull algorithm (graham scan method).
int cvx_hull(vector<pi>& coords, int n)
{
	pi pivot = pi(INT_MAX, INT_MAX);
	int __pivot_idx;

	for (int i = 0; i < n; i++)
	{
		if (coords[i] < pivot)
		{
			pivot = coords[i];
			__pivot_idx = i;
		}
	}

	swap(coords[0], coords[__pivot_idx]);
	sort(coords.begin()+1, coords.end(), [&pivot](const pi& a, const pi& b)
	{
		int ort = __pi_ort(pivot, a, b);

		if (ort > 0)
			return true;

		if (ort < 0)
			return false;
		
		// 'dist' must be defined separately.
		return dist(pivot, a) < dist(pivot, b);
	});

	vector<pi> res;
	res.push_back(coords[0]);
	res.push_back(coords[1]);

	for (int i = 2; i < n; i++)
	{
		while (res.size() > 1 && __pi_ort(res.end()[-2], res.end()[-1], coords[i]) <= 0)
			res.pop_back();

		res.push_back(coords[i]);
	}

	return res.size();
}

// line segment intersection check.
bool sgmt_check(ppi l1, ppi l2)
{
	pi a = l1.first;
	pi b = l1.second;
	pi c = l2.first;
	pi d = l2.second;

	int ab = __pi_ort(a, b, c) * __pi_ort(a, b, d);
	int cd = __pi_ort(c, d, a) * __pi_ort(c, d, b);

	if (ab == 0 && cd == 0)
	{
		if (a > b) swap(a, b);
		if (c > d) swap(c, d);
		return a <= d && b >= c;
	}

	return ab <= 0 && cd <= 0;
}
