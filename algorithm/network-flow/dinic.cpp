#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge { // u -> v
    int v,cap,ref; //ref 는 역간선 ?
    Edge(int v,int cap,int ref) :v(v),cap(cap),ref(ref) {}
}; 

class Dinic {
    int S,T;
    vector<vector<Edge>> edges; //그래프
    vector<int> level, next_v; //레벨그래프, flow계산시 역추적 사용.
public:
    Dinic(int MAX_V, int S,int T) : S(S),T(T) {
        edges.resize(MAX_V);
        level.resize(MAX_V);
        next_v.resize(MAX_V);
    } //역방향 간선 있으면 추가.
    void addEdge(int u,int v,int cap,bool inv) {
        edges[u].emplace_back(v,cap,(int)edges[v].size());
        edges[v].emplace_back(u,inv?cap : 0, (int) edges[u].size()-1);
    } //  이 간선의 역방향 간선이 v의 인접 리스트에서 어떤 위치에 있는지 저장.
    void reset_next_v() {
        fill(next_v.begin(),next_v.end(),0);
    }
    bool bfs() {
        fill(level.begin(),level.end(),-1);
        queue<int> Q;
        level[S] = 0;
        Q.push(S);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            for(auto edge: edges[u]) {
                int v = edge.v, cap = edge.cap;
                if(level[v]==-1 && cap > 0) {
                    level[v] = level[u] + 1;
                    Q.push(v);
                }
            }
        }
        return level[T] != -1;//sink T 에 도달가능여부.
    }
    int dfs(int u,int max_flow) {
        if(u==T) return max_flow; //싱크에 도달
        for(int &i = next_v[u]; i<edges[u].size(); i++) {
            int v = edges[u][i].v, cap = edges[u][i].cap;
            if(level[u]+1 == level[v] && cap > 0) { //level satisfy
                int flow = dfs(v,min(max_flow,cap));
                if(flow>0) {
                    edges[u][i].cap -= flow;//유량갱신
                    edges[v][edges[u][i].ref].cap += flow;//역간선용량증가
                    return flow;
                }
            }
        }
        return 0;
    }
};
int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    Dinic netflow(58,0,25);
    int tt; cin >> tt;
    while(tt--) {
        int cap;
        char a,b; cin >> a >> b >> cap;
        a -= 'A';
        b -= 'A';
        netflow.addEdge(a,b,cap,true);
    }
    int result = 0;
    while(netflow.bfs()) {
        netflow.reset_next_v();
        while(true) {
            int flow = netflow.dfs(0,INT_MAX);
            if(!flow) break;
            result += flow;
        }
    }
    cout << result;
}