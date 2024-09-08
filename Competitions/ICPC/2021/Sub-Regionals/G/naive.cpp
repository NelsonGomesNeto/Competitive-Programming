#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007

const int LIM = 1e15;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<int> v;
  v.clear();
  v.pb(2);
  v.pb(3);
  while (1)
  {
    int n = v.size();
    int x = v[n - 1] + v[n - 2];
    if (x <= LIM)
      v.pb(x);
    else
      break;
  }
  int sz = v.size();
  int n;
  cin >> n;
  string s = "";
  for (int i = sz - 1; i >= 0; i--)
  {
    string t = "";
    for (int j = 0; j <= i; j++)
      t.pb('A');
    t.pb('B');
    while (n % v[i] == 0)
    {
      s = s + t;
      n /= v[i];
    }
  }
  (n == 1) ? cout << s << endl : cout << "IMPOSSIBLE\n";
  return 0;
}