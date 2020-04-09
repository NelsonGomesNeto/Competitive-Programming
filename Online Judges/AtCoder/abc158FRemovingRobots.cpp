#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const lli mod = 998244353;
struct Robot
{
  lli x, d; int reaches;
  void read() { scanf("%lld %lld", &x, &d); }
  void print() { DEBUG printf("\t"); printf("%lld %lld %d\n", x, d, reaches); }
  bool operator<(const Robot &other) const { return x < other.x; }
};
Robot robots[maxN];

int segtree[4*maxN];
int query(int qlo, int qhi, int i = 1, int lo = 0, int hi = n - 1)
{
  if (hi < qlo || lo > qhi) return 0;
  if (lo >= qlo && hi <= qhi) return segtree[i];
  int mid = (lo + hi) >> 1;
  return max(query(qlo, qhi, 2*i, lo, mid), query(qlo, qhi, 2*i + 1, mid + 1, hi));
}
void update(int pos, int value, int i = 1, int lo = 0, int hi = n - 1)
{
  if (lo == hi)
  {
    segtree[i] = value;
    return;
  }
  int mid = (lo + hi) >> 1;
  if (pos <= mid) update(pos, value, 2*i, lo, mid);
  else update(pos, value, 2*i + 1, mid + 1, hi);
  segtree[i] = max(segtree[2*i], segtree[2*i + 1]);
}

lli memo[maxN + 1];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(memo, 0, sizeof(memo)), memset(segtree, 0, sizeof(segtree));

    for (int i = 0; i < n; i++)
      robots[i].read();
    sort(robots, robots+n);

    robots[n - 1].reaches = n;
    for (int i = n - 2; i >= 0; i--)
    {
      Robot limit = Robot{robots[i].x + robots[i].d - 1, 0, 0};
      int pos = upper_bound(robots, robots+n, limit) - robots;
      if (pos < n) pos -= 1;
      if (pos == n) robots[i].reaches = n;
      else if (pos <= i) robots[i].reaches = i + 1;
      else robots[i].reaches = query(i + 1, pos);
      update(i, robots[i].reaches);
      DEBUG { printf("\t%d %d ||||", i, pos); robots[i].print(); }
    }

    memo[n] = 1;
    for (int i = n - 1; i >= 0; i --)
      memo[i] = (memo[i + 1] + memo[robots[i].reaches]) % mod;

    printf("%lld\n", memo[0]);
  }
  return 0;
}