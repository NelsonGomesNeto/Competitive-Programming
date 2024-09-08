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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

struct dsu
{
  int tot;
  vector<int> parent;
  vector<int> sz;
  vector<int> mn;

  dsu(int n)
  {
    parent.resize(n);
    sz.resize(n);
    mn.resize(n);
    tot = n;
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      sz[i] = 1;
      mn[i] = i;
    }
  }
  int find_set(int i)
  {
    return parent[i] = (parent[i] == i) ? i : find_set(parent[i]);
  }
  void make_set(int x, int y)
  {
    x = find_set(x), y = find_set(y);
    if (x != y)
    {
      if (sz[x] > sz[y])
        swap(x, y);
      parent[x] = y;
      sz[y] += sz[x];
      mn[y] = min(mn[y], mn[x]);
      tot--;
    }
  }
};

int p[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int x;
    cin >> x;
    x--;
    p[i] = x;
  }
  int q;
  cin >> q;
  dsu d(n);
  while (q--)
  {
    int t;
    cin >> t;
    if (t == 1)
    {
      int a, b;
      cin >> a >> b;
      a--, b--;
      a = d.mn[d.find_set(a)];
      while (a > b)
      {
        d.make_set(a, b);
        a = p[a];
        a = d.mn[d.find_set(a)];
      }
    }
    else
    {
      int x;
      cin >> x;
      x--;
      x = d.find_set(x);
      cout << d.mn[x] + 1 << endl;
    }
  }
  return 0;
}