#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/*
scc 는 사이클의 더 확장된 개념이라고 볼 수 있다. 유향 그래프에서, 모든 정점에 대해서 서로도달가능한
최대부분 그래프를 의미한다. 방향 비순환 그래프로 그래프를 압축할 수 있음.*/

//정점x부터 dfs하면서 scc 찾기.
int findscc(int x, int &id,int (& P)[], bool (& finished)[],
stack<int> &S, vector<vector<int>> &adj,vector<vector<int>> &scc) {
    P[x] = ++id;  S.push(x);  int parent = P[x];
    //정점x와 인접한 정점들의 부모노드를결정. 사이클이 돌면 호출멈추기.
    for(auto y : adj[x]) { 
        if(P[y]==0) parent = min(parent,findscc(y,id,P,finished,S,adj,scc));
        else if(!finished[y]) parent = min(parent,P[y]);
    } //같은 scc들을 가장작은 정점의 값으로 같은 소속임을 나타냄.
    if(parent == P[x]) {
        vector<int> SCC;
        while(true) {
            int y = S.top(); //타잔 알고리즘에 scc 저장되는 순서는
            S.pop();         //위상정렬의 역순이라고 보면 됨.
            SCC.push_back(y);
            finished[y] = true;
            if(y==x) break;
        }
        scc.push_back(SCC);
    } //P[x] 을 업데이트 함으로써 P배열을 확인하면 같은 scc에 속한 것들을 알 수 있다.
    return P[x] = parent; //원래는 parent 만 있음
} //P[x] == 0인 정점에 대해서만 탐색을 실시

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt; cin >> tt;
    while(tt--) {
        int n,m; 
        cin >> n >> m;
        int id = 0; int P[n+1] = {0};//id:정점번호,부모체크
        bool finished[n+1] = {0};//scc에 속한 정점체크
        vector<vector<int>> adj(n+1); //정점x 인접그래프
        vector<vector<int>> pressedadj(n+1);
        stack<int> S; //dfs에 사용하는 스택
        vector<vector<int>> scc; //scc 저장.

        for(int i = 0; i < m; i++) {
            int u,v; cin >> u >> v;
            adj[u].push_back(v);
        }
        for(int i = 1; i <= n; i++) {
            if(P[i]==0) findscc(i,id,P,finished,S,adj,scc);
        }
        sort(scc.begin(),scc.end());
        cout << scc.size() << '\n';
        for(int a = 1; a <= n; a++) {
            for(auto x : adj[a]) {
                pressedadj[P[a]].push_back(P[x]);
            }
        }
        for(int a = 1; a <= n; a++) {
            cout << a << ":";
            for(auto x : pressedadj[a]) {
                cout << x << ' ';
            }
        } 
    }    
    return 0;
}