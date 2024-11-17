int init(int node, int st, int end) {
    // st   : init 함수가 관심두는 arr의 시작 인덱스
    // end  : init 함수가 관심두는 arr의 끝 인덱스
    // node : segTree의 노드
    // -> node번째 노드가 st ~ end의 합을 저장한다.
    if (st == end) return segTree[node] = arr[st];
    int mid = (st + end) / 2;

    //재귀로 반씩 나눠서 초기화
    return segTree[node] = init(node * 2, st, mid) + init(node * 2 + 1, mid + 1, end);
}

void update(int n, int st, int end, int t, int diff) {
    // st   : 시작 인덱스
    // end  : 끝 인덱스
    // idx  : 수정할 원소의 인덱스
    // diff  : 수정할 값

    // 범위 안에 있을 경우
    if (st <= t && t <= end) segTree[n] += diff;

    // 범위 밖에 있을 경우
    else return;
    if (st == end) return;
    int mid = (st + end) / 2;
    update(n * 2, st, mid, t, diff);
    update(n * 2 + 1, mid + 1, end, t, diff);
}

//sum함수는 구간합 쿼리이다
int sum(int l, int r, int node, int st, int end) {
    // st   : 시작 인덱스
    // end  : 끝 인덱스
    // l~r  : 구하고자 하는 구간 합의 범위

    // [l, r]이 [st, end]를 완전히 포함하는 경우
    if (l <= st && end <= r) return segTree[node];

    // [l, r]와 [st, end]가 겹치지 않는 경우
    if (r < st || end < l) return 0;

    // 나머지 경우 (일부분 겹칠때)
    int m = (st + end) / 2;
    return sum(l, r, node * 2, st, m) + sum(l, r, node * 2 + 1, m + 1, end);
}
