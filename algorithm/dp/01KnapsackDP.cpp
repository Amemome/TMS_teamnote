#include <bits/stdc++.h>
using namespace std;

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

	vector<vector<int>> dp(N+1, vector<int>(K+1));

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= K; j++)
		{
			// the value when the current item is ignored.
			dp[i][j] = dp[i-1][j];

			// the value when the current item is taken.
			if (W[i] <= j)
				dp[i][j] = max(dp[i][j], dp[i-1][j-W[i]] + V[i]);
		}
	}

	cout << dp[N][K] << '\n';
	return 0;
}
