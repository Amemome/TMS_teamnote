#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<pair<int,int>> adj[20005];
vector<pair<int,int>> reverseadj[20005];
int d[20005];
int sum[20005];
const int INF = INT_MAX;

int dike(int start,int v) {
    fill(d,d+v+1,INF);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    d[start] = 0;
    pq.push({d[start],start});
    while(!pq.empty()){
        auto [dist,cur] = pq.top(); pq.pop();
        if(d[cur] != dist) continue;
        for(auto[w,nxt] : adj[cur]) {
            if(d[nxt] > d[cur] + w) {
                d[nxt] = d[cur] + w;
                pq.push({d[nxt],nxt});
            }
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,x;
    cin >> n >> m >> x;
     
    while(m--) {
        int u , v , w;
        cin >> u >> v >> w;
        adj[u].push_back({w,v});
        reverseadj[v].push_back({w,u});
    }
    dike(x,n);
    for(int i = 1; i <= n; i++) {
        sum[i] = d[i];
    }
    swap(adj,reverseadj);
    dike(x,n);
    for(int i = 1; i <= n; i++) {
        sum[i] += d[i];
    }
    int mxm = 0;
    for(int i = 1; i <= n; i++) {
        mxm = max(mxm,sum[i]);
    }
    cout << mxm;
}
