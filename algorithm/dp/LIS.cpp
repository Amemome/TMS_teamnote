#include <bits/stdc++.h>
#define ref(i,n) for(int i = 0; i < n; i++)
using namespace std;

int main(){
    int N;    cin >> N;
    vector<int> arr(N,0);
    vector<int> dp;
    for(int i = 0;i<N; i++) cin >> arr[i];
    vector<int> index;
    for(auto x : arr){ //dp에서 x가처음나오는위치 이분탐색
        auto it = lower_bound(dp.begin(),dp.end(),x);
        index.push_back(it - dp.begin());//x가부분순열에서
        if(it == dp.end()) {//       위치하는 인덱스(길이-1)
            dp.push_back(x);//만약에dp끝이면pushback.
        } else{            //아니면 바꾸기.
            *it = x;
        }
    }
    int ct = dp.size();//LIS길이
    cout << ct-- <<"\n";vector<int> result;
    for(int i = N-1; i >= 0; i--){
        if(ct == index[i]) {
            result.push_back(arr[i]);
            ct--;
        }
    } //인덱스 배열을 뒤에서부터 보면서 수열복원
    reverse(result.begin(),result.end());
    for(auto x : result) cout << x << " ";
    return 0;
}