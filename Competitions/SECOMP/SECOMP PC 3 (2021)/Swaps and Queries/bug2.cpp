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

struct segtree
{
  int n;
  vector<set<int>> seg;

  void merge(int a, int b, int c)
  {
    for (auto const &i : seg[b])
      seg[a].insert(i);
    for (auto const &i : seg[c])
      seg[a].insert(i);
  }
  int get_first(int i, int x)
  {
    auto it = seg[i].lower_bound(x);
    return (it == seg[i].end()) ? 1e9 : *it;
  }
  int get_last(int i, int x)
  {
    auto it = seg[i].lower_bound(x);
    if (it != seg[i].end() && *it == x)
      return x;
    else if (it == seg[i].begin())
      return -1;
    return *(prev(it));
  }
  segtree(vector<int> &v)
  {
    n = 1;
    while (n < v.size())
      n <<= 1;
    seg.resize(n << 1);
    for (int i = 0; i < v.size(); i++)
      seg[i + n].insert(v[i]);
    for (int i = n - 1; i; i--)
      merge(i, i << 1, (i << 1) | 1);
  }
  void upd(int i, int x, int type)
  {
    i += n;
    for (; i; i >>= 1)
    {
      if (type == 0)
        seg[i].erase(x);
      else
        seg[i].insert(x);
    }
  }
  int qry(int l, int r, int type, int x)
  {
    int ansl = (type == 0) ? 1e9 : -1;
    int ansr = (type == 0) ? 1e9 : -1;
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
    {
      if (l & 1)
      {
        int curr = (type == 0) ? get_first(l, x) : get_last(l, x);
        ansl = (type == 0) ? min(ansl, curr) : max(ansl, curr);
        l++;
      }
      if (r & 1)
      {
        r--;
        int curr = (type == 0) ? get_first(r, x) : get_last(r, x);
        ansr = (type == 0) ? min(curr, ansr) : max(curr, ansr);
      }
    }
    return (type == 0) ? min(ansl, ansr) : max(ansl, ansr);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  segtree s = segtree(v);
  int q;
  cin >> q;
  while (q--)
  {
    int c;
    cin >> c;
    if (c == 1)
    {
      int i, j;
      cin >> i >> j;
      i--, j--;
      s.upd(i, v[i], 0);
      s.upd(j, v[j], 0);
      swap(v[i], v[j]);
      s.upd(i, v[i], 1);
      s.upd(j, v[j], 1);
    }
    else if (c == 2)
    {
      int l, r, x;
      cin >> l >> r >> x;
      l--, r--;
      int ans = s.qry(l, r, 0, x);
      (ans == 1e9) ? cout << -1 << endl : cout << ans << endl;
    }
    else
    {
      int l, r, x;
      cin >> l >> r >> x;
      l--, r--;
      int ans = s.qry(l, r, 1, x);
      (ans == -1) ? cout << -1 << endl : cout << ans << endl;
    }
  }
  return 0;
}
