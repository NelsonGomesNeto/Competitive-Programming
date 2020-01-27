#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5 + 1, inf = 1e8; int m, n, k, t;
struct Trap
{
  int l, r, d;
  void read() { scanf("%d %d %d", &l, &r, &d); }
};
Trap traps[maxN];
int soldiers[maxN];

int in[maxN], out[maxN];
bool can(int x)
{
  memset(in, 0, sizeof(in)), memset(out, 0, sizeof(out));
  int d = x == 0 ? inf : soldiers[x - 1];
  for (int i = 0; i < k; i ++)
    if (traps[i].d > d)
      in[traps[i].l] ++, out[traps[i].r] ++;
  int tt = n + 1;
  for (int i = 0, now = 0; i <= n; i ++)
  {
    now += in[i];
    if (now) tt += 2;
    now -= out[i];
  }
  return tt <= t;
}
int binarySearch(int lo = 0, int hi = m)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (can(mid)) lo = mid;
    else hi = mid - 1;
  }
  return lo;
}

int main()
{
  while (scanf("%d %d %d %d", &m, &n, &k, &t) != EOF)
  {
    for (int i = 0; i < m; i ++)
      scanf("%d", &soldiers[i]);
    sort(soldiers, soldiers+m, greater<int>());
    for (int i = 0; i < k; i ++)
      traps[i].read();

    int ans = binarySearch();
    printf("%d\n", ans);
  }
  return 0;
}
