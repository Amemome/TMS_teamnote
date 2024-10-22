typedef pair<int, int> pi;
typedef pair<pi, pi> ppi;

// orientation of 3 points: -1 (clockwise), 0 (linear), 1 (counterclockwise)
int pi_ort(const pi& a, const pi& b, const pi& c)
{
	return pi_cross(ab_vector, bc_vector));
}

// convex hull algorithm (graham scan method).
int cvx_hull(vector<pi>& coords, int n)
{
	pi pivot = pi(INT_MAX, INT_MAX);
	// find the left-most, bottom-most coordinate.
	// sort the coordinates in counter-clockwise order.

	vector<pi> res;
	res.push_back(coords[0]);
	res.push_back(coords[1]);

	for (int i = 2; i < n; i++)
	{
		while (res.size() > 1 && pi_ort(res.end()[-2], res.end()[-1], coords[i]) <= 0)
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

	int ab = pi_ort(a, b, c) * pi_ort(a, b, d);
	int cd = pi_ort(c, d, a) * pi_ort(c, d, b);

	if (ab == 0 && cd == 0)
	{
		if (a > b) swap(a, b);
		if (c > d) swap(c, d);
		return a <= d && b >= c;
	}

	return ab <= 0 && cd <= 0;
}
