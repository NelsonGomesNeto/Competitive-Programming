#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 100000

set<int> seg[4 * MAXN];
int v[MAXN];

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
void update(int i, int l, int r, int q, int x, int type)
{
  if (type == 0)
    seg[i].erase(x);
  else
    seg[i].insert(x);
  if (l == r)
    return;
  int mid = (l + r) >> 1;
  if (q <= mid)
    update(i << 1, l, mid, q, x, type);
  else
    update((i << 1) | 1, mid + 1, r, q, x, type);
}
int query(int l, int r, int ql, int qr, int i, int x, int type)
{
  if (l > r || l > qr || r < ql)
    return (type == 0) ? 1e9 : -1;
  if (l >= ql && r <= qr)
    return (type == 0) ? get_first(i, x) : get_last(i, x);
  int mid = (l + r) >> 1;
  if (type == 0)
    return min(query(l, mid, ql, qr, i << 1, x, type), query(mid + 1, r, ql, qr, (i << 1) | 1, x, type));
  else
    return max(query(l, mid, ql, qr, i << 1, x, type), query(mid + 1, r, ql, qr, (i << 1) | 1, x, type));
}
void build(int l, int r, int i)
{
  if (l == r)
  {
    seg[i].insert(v[l]);
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, i << 1);
  build(mid + 1, r, (i << 1) | 1);
  merge(i, i << 1, (i << 1) | 1);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  build(0, n - 1, 1);
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
      update(1, 0, n - 1, i, v[i], 0);
      update(1, 0, n - 1, j, v[j], 0);
      swap(v[i], v[j]);
      update(1, 0, n - 1, i, v[i], 1);
      update(1, 0, n - 1, j, v[j], 1);
    }
    else if (c == 2)
    {
      int l, r, x;
      cin >> l >> r >> x;
      l--, r--;
      int ans = query(0, n - 1, l, r, 1, x, 0);
      (ans == 1e9) ? cout << -1 << endl : cout << ans << endl;
    }
    else
    {
      int l, r, x;
      cin >> l >> r >> x;
      l--, r--;
      int ans = query(0, n - 1, l, r, 1, x, 1);
      (ans == -1) ? cout << -1 << endl : cout << ans << endl;
    }
  }
  return 0;
}