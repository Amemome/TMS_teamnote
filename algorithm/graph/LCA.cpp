const int siz = 1e5+10;
vector<int> ed[siz];
int depth[siz];
int dp[siz][30];
int vis[siz];
int n;

void dfs(int v, int d){
	vis[v] = 1;
	depth[v] = d;
	for(auto i : ed[v]){
		if(!vis[i]){
			dp[i][0] = v;
			dfs(i, d+1);
		}
	}
}

void make_table(){
	for(int j=1; j<30; j++){
		for(int i=1; i<=n; i++){
			dp[i][j] = dp[ dp[i][j-1] ][j-1];
		}
	}
}

int lca(int u, int v){
	if(depth[u] < depth[v]) swap(u, v);
	int diff = depth[u] - depth[v];
	for(int i=0; diff; i++){
		if(diff & 1) u = dp[u][i];
		diff >>= 1;
	}
	if(u == v) return u;

	for(int i=29; i>=0; i--){
		if(dp[u][i] != dp[v][i]) u = dp[u][i], v = dp[v][i];
	}
	return dp[u][0];
}

//간선 입력받은 후, dfs(root,0); make_table()로 LCA구축하기
