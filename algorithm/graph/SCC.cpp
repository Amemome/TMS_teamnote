#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
scc 는 사이클의 더 확장된 개념이라고 볼 수 있다. 유향 그래프에서, 모든 정점에 대해서 서로도달가능한
최대부분 그래프를 의미한다. 방향 비순환 그래프로 그래프를 압축할 수 있음.
*/

#define MAX 10001
int id; //정점번호
int P[MAX]; //부모?
bool finished[MAX];
vector<vector<int>> adj(MAX);
stack<int> S;
vector<vector<int>> scc;

//정점x부터 dfs하면서 scc 찾기.
int findscc(int x, int &id,int (& P)[MAX], bool (& finished)[MAX],
stack<int> &S, vector<vector<int>> &adj,vector<vector<int>> &scc) {
    P[x] = ++id;
    S.push(x);
    //정점x와 인접한 정점들의 부모노드를결정. 사이클이 돌면 호출멈추기.
    int parent = P[x];
    for(auto y : adj[x]) {
        if(P[y]==0) parent = min(parent,findscc(y,id,P,finished,S,adj,scc));
        else if(!finished[y]) parent = min(parent,P[y]);
    }
    if(parent == P[x]) {
        vector<int> SCC;
        while(true) {
            int y = S.top();
            S.pop();
            SCC.push_back(y);
            finished[y] = true;
            if(y==x) break;
        }
        sort(SCC.begin(),SCC.end());
        scc.push_back(SCC);
    }
    return parent;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int v,e; cin >> v >> e;
    while(e--) {
        int f,t; cin >> f >> t;
        adj[f].push_back(t);
    }

    for(int i = 1; i <= v; i++) {
        if(P[i]==0) findscc(i,id,P,finished,S,adj,scc);
    }
    cout << scc.size() << '\n';
    sort(scc.begin(),scc.end());
    for(auto s : scc) {
        for(int c : s) {
            cout << c << ' ';
        }
        cout << -1 << '\n';
    }
    

    return 0;
}