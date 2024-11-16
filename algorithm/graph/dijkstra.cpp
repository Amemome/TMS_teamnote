vector<pair<int,int>> adj[20005];
int d[20005];
const int INF = INT_MAX;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int v,e,st; cin >> v >> e >> st;
    fill(d,d+v+1,INF);
    while(e--) {
        int u , v , w;
        cin >> u >> v >> w;
        adj[u].push_back({w,v});
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    d[st] = 0;
    pq.push({d[st],st});
    while(!pq.empty()){
        auto cur = pq.top(); pq.pop();
        if(d[cur.second]!= cur.first) continue; //가중치가 같지 않음?
        for(auto nxt : adj[cur.second]) {
            if(d[nxt.second] <= d[cur.second] + nxt.first) continue;
            d[nxt.second] = d[cur.second] + nxt.first;
            pq.push({d[nxt.second],nxt.second});
        }
    }
    for(int i = 1; i <= v; i++) {
        if(d[i] == INF) cout << "INF";
        else cout << d[i];
        cout << '\n';
    }
}
