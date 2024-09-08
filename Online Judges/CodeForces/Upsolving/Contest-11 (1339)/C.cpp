#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli maxX = 3e9;
lli a[maxN];

struct Node
{
  lli diff; int pos;
  Node operator+(const Node &other)
  {
    if (diff < other.diff)
      return *this;
    return other;
  }
};
Node segtree[maxN], nil = {maxX, 0};
Node query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (hi < qlo || lo > qhi) return nil;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return query(qlo, qhi, 2*i, lo, mid) + query(qlo, qhi, 2*i + 1, mid + 1, hi);
}
void update(Node value, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (mid <= value.pos) update(value, 2*i, lo, mid);
  else update(value, 2*i + 1, mid + 1, hi);
  segtree[i] = segtree[2*i] + segtree[2*i + 1];
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    update({maxX, 0});
    for (int i = 1; i < n; i++)
    {
      printf("\t\t%d %lld\n", i, a[i] - a[i - 1]);
      update({a[i] - a[i - 1], i});
    }

    int ans = 0; lli pot = 1;
    Node now;
    while ((now = query(0, n - 1)).diff < 0)
    {
      DEBUG printf("\t%d %lld %d\n", ans, now.diff, now.pos);
      now.diff += pot;
      update(now);
      if (pot <= maxX) pot *= 2;
      ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}
