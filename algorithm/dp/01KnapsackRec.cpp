#include <bits/stdc++.h>
using namespace std;

int knapsack(int i, int j, vector<int>& W, vector<int>& V, vector<vector<int>>& dp)
{
	if (i == 0)
		return 0;

	if (dp[i][j] != -1)
		return dp[i][j];

	int __cache = knapsack(i-1, j, W, V, dp);

	if (W[i] <= j)
		__cache = max(__cache, knapsack(i-1, j-W[i], W, V, dp) + V[i]);

	dp[i][j] = __cache;
	return __cache;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, K;
	cin >> N >> K;

	// weight, value.
	vector<int> W(N+1);
	vector<int> V(N+1);

	for (int i = 1; i <= N; i++)
		cin >> W[i] >> V[i];

	vector<vector<int>> dp(N+1, vector<int>(K+1, -1));
	cout << knapsack(N, K, W, V, dp) << '\n';
	return 0;
}
