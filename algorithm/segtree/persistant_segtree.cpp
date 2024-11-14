struct Node{
    Node *l, *r;
    ll v;
    Node(){ l = r = NULL; v = 0; }
};

//root[i] = i번째 세그먼트 트리의 루트
Node *root[101010]; //root[0] 할당 필수
vector<int> arr(101010,0); //초깃값
vector<int> shrinked_arr(101010,0);

void build(Node *node, int s, int e){ //0번 트리 생성
    if(s == e){
        node->v = arr[s]; return;
    }
    int m = s + e >> 1;
    node->l = new Node(); node->r = new Node();
    build(node->l, s, m); build(node->r, m+1, e);
    node->v = node->l->v + node->r->v;
}
void add(Node *prv, Node *now, int s, int e, int x, int v){
    if(s == e){
        now->v = v; return;
    }
    int m = s + e >> 1;
    if(x <= m){ //왼쪽 자식에 업데이트 하는 경우
        //왼쪽 자식은 새로운 정점 생성, 오른쪽 자식은 재활용
        now->l = new Node(); now->r = prv->r;
        add(prv->l, now->l, s, m, x, v);
    }else{
        //오른쪽 자식은 새로운 정점 생송, 왼쪽 자식은 재활용
        now->l = prv->l; now->r = new Node();
        add(prv->r, now->r, m+1, e, x, v);
    }
    now->v = now->l->v + now->r->v;
}

ll sum(Node *node, int s, int e, int l, int r){
    if(r < s || e < l) return 0;
    if(l <= s && e <= r) return node->v;
    int m = s + e >> 1;
    return sum(node->l, s, m, l, r) + sum(node->r, m+1, e, l, r);
}

//여기서 좌표압축은 upper_bound로 진행
//query(root[i-1], root[j], 원소 범위 시작, 원소 범위 끝, k)(모든 원소가 정렬된 기준으로 인덱스를 구해줌)
ll query(Node *l, Node *r, int s, int e, int k){
    if(s == e) return s;
    int diff = r->l->v - l->l->v;
    int m = s + e >> 1;
    if(k <= diff) return query(l->l, r->l, s, m, k);
    else return query(l->r, r->r, m+1, e, k-diff);
}
