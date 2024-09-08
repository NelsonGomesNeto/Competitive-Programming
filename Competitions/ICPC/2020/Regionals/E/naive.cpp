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
#define MAXN 100005
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < n; i++)
  {
    int ans = 0, curr = v[i];
    int l = i - 1, r = i + 1;
    while (l >= 0 || r < n)
    {
      int at = curr;
      if (l >= 0)
      {
        at = max(at, v[l]);
        l--;
      }
      if (r < n)
      {
        at = max(at, v[r]);
        r++;
      }
      if (at > curr)
        ans++;
      curr = at;
    }
    cout << ans << " ";
  }
  cout << endl;
  return 0;
}