#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N;
	cin >> N;

	// value collection.
	vector<pi> T;
	for (int i = 0; i < N; i++)
	{
		int e, x;
		cin >> e >> x;
		T.push_back(pi(e, 1)); // 1 marks an entry.
		T.push_back(pi(x, 0)); // 0 marks an exit.
	}
	sort(T.begin(), T.end());

	// value compression.
	int prev_val;
	vector<int> orig(T.size());
	orig[0] = T[0].first;
	prev_val = T[0].first;
	T[0].first = 0;

	int comp = 0; // compressed value.
	for (int i = 1; i < T.size(); i++)
	{
		if (T[i].first != prev_val)
		{
			orig[++comp] = T[i].first;
			prev_val = T[i].first;
		}

		T[i].first = comp;
	}

	// difference array construction.
	vector<int> diff(comp+1);
	for (pi& p : T)
	{
		if (p.second)
			diff[p.first]++;
		else
			diff[p.first]--;
	}

	for (int i = 1; i <= comp; i++)
		diff[i] += diff[i-1];

	// finally, we find the segment with the largest diff-value.
	int ans = diff[0];
	int seg_begin = 0;
	int seg_end = 1;

	for (int i = 1; i <= comp; i++)
	{
		if (diff[i] > ans)
		{
			ans = diff[i];
			seg_begin = i;
			seg_end = i+1;
		}
		else if (diff[i] == ans && i == seg_end)
			seg_end++;
	}

	cout << ans << '\n';
	cout << orig[seg_begin] << ' ' << orig[seg_end] << '\n';
	return 0;
}
