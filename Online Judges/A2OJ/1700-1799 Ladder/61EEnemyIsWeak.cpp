#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n;
int a[maxN];
vector<int> x;
map<int, int> compress;
int decompress[maxN];

int memo[maxN];

lli segtree[2][4*maxN];
lli query(int k, int qlo, int qhi, int i = 1, int lo = 0, int hi = x.size() - 1)
{
  if (hi < qlo || lo > qhi) return 0;
  if (lo >= qlo && hi <= qhi) return segtree[k][i];
  int mid = (lo + hi) >> 1;
  return query(k, qlo, qhi, 2*i, lo, mid) + query(k, qlo, qhi, 2*i + 1, mid + 1, hi);
}
void update(int k, int pos, lli value, int i = 1, int lo = 0, int hi = x.size() - 1)
{
  if (lo == hi)
  {
    segtree[k][i] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(k, pos, value, 2*i, lo, mid);
  else update(k, pos, value, 2*i + 1, mid + 1, hi);
  segtree[k][i] = segtree[k][2*i] + segtree[k][2*i + 1];
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(segtree, 0, sizeof(segtree));
    compress.clear();

    x.resize(n);
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &x[i]);
      a[i] = x[i];
    }
    sort(x.begin(), x.end());
    x.resize(distance(x.begin(), unique(x.begin(), x.end())));

    for (int i = 0; i < x.size(); i ++)
      compress[x[i]] = i, decompress[i] = x[i];

    for (int i = 0; i < n; i ++)
      a[i] = compress[a[i]];

    lli ans = 0;
    for (int i = 0; i < n; i ++)
    {
      int got0 = a[i] + 1 < x.size() ? query(0, a[i] + 1, x.size() - 1) : 0;
      lli got1 = a[i] + 1 < x.size() ? query(1, a[i] + 1, x.size() - 1) : 0;
      ans += got1;
      update(0, a[i], 1);
      update(1, a[i], got0);
    }
    printf("%lld\n", ans);
  }
  return 0;
}