#include <bits/stdc++.h>
using namespace std;
 
#define MAXN (int)(2 * 1e5 + 1)
#define MAXL 20
#define F first
#define S second
#define endl "\n"
#define MOD (lli)(1e9 + 7)
#define lli long long int
#define sz(a) int(a.size())
#define DEBUG if (0) cout << "aqui" << endl;
#define PI 2 * acos(0.0)
typedef pair<int, int> ii;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int dddx[] = {1, -1, 0, 0, 1, 1, -1, -1};
int dddy[] = {0, 0, 1, -1, 1, -1, 1, -1};
 
int t;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    vector<pair<lli, lli > > vec;

    for(int i=0;i<n;i++) {
      lli a, b;
      cin >> a >> b;
      vec.push_back({a, b});
    }

    for(int i=0;i<n;i++) vec.push_back(vec[i]);

    lli cum = 0;
    lli sum = 0;
    lli ans = LLONG_MAX;
    int a = 0, b = 0;
    for(int i=0;i<n;i++) {
      lli resto = (vec[i].F - cum);
      cum = vec[i].S;
      resto = max(resto, 0LL);
      sum += resto;
    }

    ans = min(ans, sum);
    b = n-1;
    while(a < n) {
      
      b++;
      lli resto = vec[b].F - cum;
      cum = vec[b].S;
      resto = max(resto, 0LL);
      sum += resto;

      sum -= vec[a].F;
      sum -= (max(0LL, vec[a+1].F - vec[a].S));
      a++;
      sum += vec[a].F;

      ans = min(ans, sum);
    }
    cout << ans << endl;
  }

  return 0;
}