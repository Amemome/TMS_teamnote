#include <bits/stdc++.h>

#define X first 
#define Y second 
#define all(v) v.begin(),v.end()

using namespace std;

typedef long long ll;

const ll inf = 2e18;

struct Line{
	ll a, b;
	ll get(ll x){
		return a * x + b;
	}
};

struct Node{
	int l, r; //child
	ll s, e; //range
	Line line;
};

struct Li_Chao{
	vector<Node> tree;

	void init(ll s, ll e){
		tree.push_back({ -1, -1, s, e, { 0, -inf } });
	}

    void update(int node, Line v){
	ll s = tree[node].s, e = tree[node].e;
	ll m = s + e >> 1;

	Line low = tree[node].line, high = v;
	if (low.get(s) > high.get(s)) swap(low, high);

	    if (low.get(e) <= high.get(e)){
	    	tree[node].line = high; return;
	    }

	    if (low.get(m) < high.get(m)){
	    	tree[node].line = high;
	    	if (tree[node].r == -1){
	    		tree[node].r = tree.size();
	    		tree.push_back({ -1, -1, m + 1, e, { 0, -inf } });
	    	}
	    	update(tree[node].r, low);
	    }
	    else{
	    	tree[node].line = low;
		    if (tree[node].l == -1){
	    		tree[node].l = tree.size();
	    		tree.push_back({ -1, -1, s, m, { 0, -inf } });
	    	}
	    	update(tree[node].l, high);
	    }
    }

    ll query(int node, ll x){
        if (node == -1) return -inf;
        ll s = tree[node].s, e = tree[node].e;
        ll m = s + e >> 1;
        if (x <= m) return max(tree[node].line.get(x), query(tree[node].l, x));
        else return max(tree[node].line.get(x), query(tree[node].r, x));
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    Li_Chao seg;
    seg.init(-2e12,2e12);
    int q; cin>>q;
    while(q--)
    {
        int op; cin>>op;
        if(op==1)
        {
            int a; ll b; cin>>a>>b;
            seg.update(0,{(ll)a,b});
        }
        else
        {
            ll x; cin>>x;
            cout<<seg.query(0,x)<<'\n';
        }
    }
    return 0;
}
//세그먼트 트리+직선의 방성식
//간선 삭제가 없는 컨벡스 헐 트릭의 온라인 쿼리
//주어진 코드는 직선의 방정식이 여러개 주어질 때 x좌표 고정시 y좌표의 최댓값
