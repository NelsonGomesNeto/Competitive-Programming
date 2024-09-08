#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
int a[maxN];
struct Event
{
  int r; double p;
  void read() { scanf("%d %lf", &r, &p); r--; }
};
Event events[maxN];
int suf;

double memo[maxN][2];
double solve(int i = 0, bool done = false)
{
  if (i == m) return done;
  double &ans = memo[i][done];
  if (ans != -1) return ans;

  ans = (events[i].r >= suf ? 1 - events[i].p : 1) * solve(i + 1, done);
  if (events[i].r >= suf)
    ans += events[i].p * solve(i + 1, true);
  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i]--;
    }

    for (int i = 0; i < m; i++)
    {
      events[i].read();
      DEBUG printf("\t%d %lf\n", events[i].r, events[i].p);
    }

    suf = n - 1;
    while (suf >= 0 && a[suf] == suf) suf--;
    DEBUG printf("\t%d\n", suf);

    if (suf == -1) printf("1\n");
    else
    {
      for (int i = 0; i < m; i++)
        memo[i][0] = memo[i][1] = -1;
      double ans = solve();
      printf("%.15lf\n", ans);
    }
  }
  return 0;
}
