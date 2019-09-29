#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxX = 1e6; int n;
int a[maxN], b[maxN], ans[maxN], compressed[maxX + 1], c;

int segtree[4*(maxN + 1)];
void update(int pos, int value, int i = 1, int lo = 0, int hi = maxN)
{
  if (lo == hi)
  {
    segtree[i] += value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(pos, value, 2*i, lo, mid);
  else update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}
int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = maxN)
{
  if (qhi < lo || qlo > hi) return 0;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    memset(segtree, 0, sizeof(segtree));
    scanf("%d", &n);
    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]); b[i] = a[i];
      compressed[a[i]] = -1;
    }
    sort(b, b+n); c = 0;
    for (int i = 0; i < n; i ++)
      if (compressed[b[i]] == -1)
        compressed[b[i]] = c ++;

    for (int i = n - 1; i >= 0; i --)
    {
      ans[i] = query(compressed[a[i]] + 1, maxN);
      update(compressed[a[i]], 1);
    }
    for (int i = 0; i < n; i ++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}