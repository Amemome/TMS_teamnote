#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/*
scc 는 사이클의 더 확장된 개념이라고 볼 수 있다. 유향 그래프에서, 모든 정점에 대해서 서로도달가능한
최대부분 그래프를 의미한다. 방향 비순환 그래프로 그래프를 압축할 수 있음.*/

//정점x부터 dfs하면서 scc 찾기.
int findscc(int x, int &id,int (& P)[], bool (& finished)[],
stack<int> &S, vector<vector<int>> &adj,vector<vector<int>> &scc,
vector<int> &sccID, int &sccCnt) {
    P[x] = ++id;  S.push(x);  int parent = P[x];
    //정점x와 인접한 정점들의 부모노드를결정. 사이클이 돌면 호출멈추기.
    for(auto y : adj[x]) { 
        if(P[y]==0) parent = min(parent,findscc(y,id,P,finished,S,adj,scc,sccID,sccCnt));
        else if(!finished[y]) parent = min(parent,P[y]);
    } //같은 scc들을 가장작은 정점의 값으로 같은 소속임을 나타냄.
    if(parent == P[x]) {
        vector<int> SCC;
        while(true) {
            int y = S.top();
            S.pop();
            SCC.push_back(y);
            finished[y] = true;
            sccID[y] = sccCnt;
            if(y==x) break;
        }
        sccCnt++;
        scc.push_back(SCC);
    } 
    return parent; //P[x]에 부모 넣어서 scc 까지 확인하기 <- 반례가 나오긴 했는데 약한 데이터에서는 괜찮을수도
} //P[x] == 0인 정점에 대해서만 탐색을 실시 

int main(void)
{
    int n,m; 
    cin >> n >> m;
    int id = 0, sccCnt = 0; //sccID 로 그 노드들이 같은 scc인지 확인
    int P[2*n+1] = {0};//id:정점번호,부모체크
    vector<int> sccID(2*n+1);
    bool finished[2*n+1] = {0};//scc에 속한 정점체크
    vector<vector<int>> adj(2*n+1); //정점x 인접그래프
    stack<int> S; //dfs에 사용하는 스택
    vector<vector<int>> scc; //scc 저장.

    for(int i = 0; i < m; i++) {
        int u,v; cin >> u >> v;
        if(u<0) u = n-u;
        if(v<0) v = n-v;
        if(u<=n) u += n; else u -= n;
        adj[u].push_back(v);
        if(u<=n) u += n; else u -= n;
        if(v<=n) v += n; else v -= n;
        adj[v].push_back(u);
    }
    for(int i = 1; i <=2*n; i++) {
        if(P[i]==0) findscc(i,id,P,finished,S,adj,scc,sccID,sccCnt);
    }    
    for(int i = 1; i <= n; i++) {
        if(sccID[i] == sccID[n+i]) {
            cout << 0;
            return 0;
        }
    }
    cout << 1;

}