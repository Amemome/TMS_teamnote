vector<int> g[s], ans;
int order[s], par[s], low[s], t;

void dfs(int v){
	order[v] = t++;
	low[v] = t;
	int sub = 0; //자식 수
	for(auto i : g[v]){
		if(i == par[v]) continue;

		if(!order[i]){
			par[i] = v;
			sub++;
			dfs(i);
			if(!par[v] && sub > 1) ans.push_back(v); //루트 노드
			else if(par[v] && low[i] >= order[v]) ans.push_back(v);

			low[v] = min(low[v], low[i]);
		}
		else low[v] = min(low[v], order[i]);
	}
}
//단절점
//ans에 있음

vector<int> g[100010];
int order[100010]; //발견 순서
int par[100010];  //부모
int low[100010]; //i를 루트로 하는 서브 트리에서 가장 위로 갈 수 있는 노드
vector<pair<int,int>> ans;
int t;

void dfs(int v){
	order[v] = t++;
	low[v] = t;

	for(auto i : g[v]){ //i : 다음에 갈 노드
		if(i == par[v]) continue; //내 부모 == 나 임면 스킵

		if(order[i] == 0){ //아직 발견이 안되었다면
			par[i] = v; //다음 노드의 붑모는 현재 노드
			dfs(i);

			if(low[i] > order[v]) ans.push_back({min(v, i), max(v, i)});
			/*서브 트리에서 위로 더 올라갈 수 없으면 단절점 확정*/

			low[v] = min(low[v], low[i]);
		}
		else low[v] = min(low[v], order[i]);
	}
}
//단절선
//ans에 있음
