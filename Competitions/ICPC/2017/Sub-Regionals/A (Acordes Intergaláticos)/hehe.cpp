#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

struct item
{
  vector<int> v;
};

vector<item> seg(4 * MAXN);
vector<int> lazy(4 * MAXN);

item single(int x)
{
  vector<int> vv(9, 0);
  vv[x] = 1;
  return {vv};
}
item neutral()
{
  vector<int> vv(9, 0);
  return {vv};
}
item merge(item a, item b)
{
  vector<int> vv(9, 0);
  for (int i = 0; i < 9; i++)
    vv[i] = a.v[i] + b.v[i];
  return {vv};
}
void add(int i, int l, int r, int diff)
{
  vector<int> vv(9);
  for (int j = 0; j < 9; j++)
  {
    int at = (j + diff) % 9;
    vv[at] = seg[i].v[j];
  }
  seg[i] = {vv};
  if (l != r)
  {
    lazy[i << 1] += diff;
    lazy[(i << 1) | 1] += diff;
  }
  lazy[i] = 0;
}
void update(int i, int l, int r, int ql, int qr, int diff)
{
  if (lazy[i])
    add(i, l, r, lazy[i]);
  if (l > r || l > qr || r < ql)
    return;
  if (l >= ql && r <= qr)
  {
    add(i, l, r, diff);
    return;
  }
  int mid = (l + r) >> 1;
  update(i << 1, l, mid, ql, qr, diff);
  update((i << 1) | 1, mid + 1, r, ql, qr, diff);
  seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
}
item query(int l, int r, int ql, int qr, int i)
{
  if (lazy[i])
    add(i, l, r, lazy[i]);
  if (l > r || l > qr || r < ql)
    return neutral();
  if (l >= ql && r <= qr)
    return seg[i];
  int mid = (l + r) >> 1;
  return merge(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
}
void build(int l, int r, int i)
{
  if (l == r)
  {
    seg[i] = single(1);
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, i << 1);
  build(mid + 1, r, (i << 1) | 1);
  seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q;
  cin >> n >> q;
  build(0, n - 1, 1);
  while (q--)
  {
    int l, r;
    cin >> l >> r;
    int best = 0, at = 0;
    item ans = query(0, n - 1, l, r, 1);
    for (int i = 0; i < 9; i++)
    {
      if (ans.v[i] >= best)
      {
        best = ans.v[i];
        at = i;
      }
    }
    update(1, 0, n - 1, l, r, at);
  }
  for (int i = 0; i < n; i++)
  {
    item ans = query(0, n - 1, i, i, 1);
    for (int i = 0; i < 9; i++)
      if (ans.v[i])
        cout << i << endl;
  }
}
// n 1,1,1,1...1
// pegar um intervalo l, r
// achar a tecla mais frequente e maior f
// cada tecla do intervalo vira (v[i] + f) % 9
// repetir o processo
// gg