#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int t[maxN];
vector<int> a[maxN];
bool done[maxN];

lli learn(int u)
{
  done[u] = true;
  lli total = t[u];
  for (int v: a[u])
    if (!done[v])
      total += learn(v);
  return total;
}

int main()
{
  while (~scanf("%d", &n))
  {
    fill(done, done+n, false);
    for (int i = 0; i < n; i++)
    {
      int sz; scanf("%d %d", &t[i], &sz);
      a[i].resize(sz);
      for (int &aa: a[i])
      {
        scanf("%d", &aa);
        aa--;
      }
    }

    lli ans = t[n - 1];
    for (int &req: a[n - 1])
      if (!done[req])
        ans += learn(req);
    printf("%lld\n", ans);
  }
  return 0;
}