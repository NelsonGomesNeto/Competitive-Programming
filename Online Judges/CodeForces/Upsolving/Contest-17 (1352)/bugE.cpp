#include <bits/stdc++.h>
using namespace std;
#define DEBUG  0
const int MAX = 8010;
int v[MAX], sum[MAX];
int ans[MAX];
int res, lf, rg;
int n, tot, mid;
void solve() {
  cin >> n;
  for(int i = 1; i <= n; ++i){
    cin >> v[i];
    ans[v[i]] = -1;
  }
  sum[0] = 0;
  sum[1] = v[1];
  res = 0;
  for(int i = 2; i <= n; ++i)sum[i] = v[i] + sum[i-1];
  for(int i = 1; i <= n; ++i) {
    if(ans[v[i]] != -1){
      res+=ans[v[i]];
    } else {
      bool ok = false;
      if(DEBUG)cout << v[i] << endl;
      if(DEBUG)cout << "----------------------\n";
      for(int j = 1; j <= n && !ok; ++j) {
        lf = j + 1;
        rg = n;
        while(lf <= rg && !ok) {
          mid = (lf+rg)/2;
          tot = sum[mid] - sum[j-1];
          if(DEBUG) cout << tot << " " << j << " " << mid << endl;
          if(tot == v[i]) {
            if(DEBUG)cout << "FOUND " << v[i] << endl;
            ok = true;
            ans[v[i]] = 1;
            res++;
          } 
          else if(tot < v[i]) lf = mid + 1;
          else rg = mid - 1;
        }
      }
      if(!ok)ans[v[i]] = 0;
    }
  }
  cout << res << endl;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tc = 1;
  cin >> tc;
  for(int i = 1; i <= tc; ++i) {
    // cout << "Case #" << i <<": ";
    solve();
  }
  return 0;
}