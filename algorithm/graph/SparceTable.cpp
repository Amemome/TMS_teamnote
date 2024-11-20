const int siz = 100005;
int n;
vector<int> ed[siz];
int sp[20][100005];
int vis[siz];
void dfs(int v){
	vis[v] = 1;
	for(auto i : ed[v]){
		if(!vis[i]){
			sp[0][i]=v;
			dfs(i.X);
		}
	}
}
void make_sparse()
{
	for(int p=1; p<20; p++)
	{
		for(int i=1; i<=n; i++)
		{
			sp[p][i]=sp[p-1][sp[p-1][i]];
		}
	}
}
int f(int v, int k)
{
	for(int i=19; i>=0; i--)
	{
		if(k&(1<<i))
		{
			v=sp[i][v];
		}
	}
	return v;
}
