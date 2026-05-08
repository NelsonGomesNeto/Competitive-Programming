#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 804
#define mod 1000000007

int n;
int c[MAXN];
int cost[MAXN];
int dp[MAXN][MAXN];  // custo minimo p fazer o intervalo [l, r] ter geral com a cor 0
int dp2[MAXN][MAXN]; // custo minimo p fazer o intervalo [l, r] ter geral com a cor 0 ou a cor c[l]

int solve(int l, int r);

int solve2(int l, int r)
{
  if (l > r)
    return 0;
  if (dp2[l][r] != -1)
    return dp2[l][r];
  int ans = 1e18;
  if (c[l] == c[r])
    ans = min(ans, solve2(l, r - 1));
  for (int i = l; i < r; i++)
    ans = min(ans, solve2(l, i) + solve(i + 1, r));
  return dp2[l][r] = ans;
}
int solve(int l, int r)
{
  if (l > r)
    return 0;
  if (dp[l][r] != -1)
    return dp[l][r];
  int ans = 1e18;
  ans = min(ans, solve2(l, r) + cost[c[l]] + r - l + 1);
  for (int i = l; i < r; i++)
    ans = min(ans, solve(l, i) + solve(i + 1, r));
  return dp[l][r] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  while (cin >> n) {
    for (int i = 0; i < n; i++)
      cin >> c[i];
    for (int i = n; i < 2 * n; i++)
      c[i] = c[i - n];
    for (int i = 1; i <= n; i++)
      cin >> cost[i];
    memset(dp, -1, sizeof(dp));
    memset(dp2, -1, sizeof(dp2));
    int ans = 1e18;
    for (int i = 0; i < n; i++)
    {
      const int res = solve(i, i + n - 1);
      // std::cout << "\t" << i << ": " << res << "\n";
      ans = min(ans, res);
    }
    cout << ans << endl;
  }
}
// pensar no problema reverse eh mais facil
// escolher um segmento que so tem a mesma cor e a cor 0
// e pintar com a cor 0