#include <bits/stdc++.h>
using namespace std;

void solve(int n, const vector<int>& time, const vector<vector<int>>& adj, vector<int>& res)
{
	vector<int> start(n+1);
	vector<int> indeg(n+1);
	queue<int> tsort_queue;

	// pre-compute indegree.
	for (int i = 1; i <= n; i++)
	{
		for (int j : adj[i])
			indeg[j]++;
	}

	// search starting positions;
	for (int i = 1; i <= n; i++)
	{
		if (!indeg[i])
			tsort_queue.push(i);
	}

	while (!tsort_queue.empty())
	{
		int cur = tsort_queue.front(); tsort_queue.pop();
		res[cur] = start[cur] + time[cur];

		for (int i : adj[cur])
		{
			indeg[i]--;
			start[i] = max(start[i], res[cur]);

			if (!indeg[i])
				tsort_queue.push(i);
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<int> time(n+1);
	vector<vector<int>> adj(n+1);

	for (int i = 1; i <= n; i++)
	{
		int pre;
		cin >> time[i] >> pre;

		while (pre != -1)
		{
			adj[pre].push_back(i);
			cin >> pre;
		}
	}

	vector<int> res(n+1);
	solve(n, time, adj, res);

	for (int i = 1; i <= n; i++)
		cout << res[i] << '\n';

	return 0;
}
