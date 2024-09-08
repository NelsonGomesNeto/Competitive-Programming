#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const ldouble eps = 1e-12;

bool gte(ldouble a, ldouble b)
{
  return a >= b || abs(b - a) <= eps;
}
bool lte(ldouble a, ldouble b)
{
  return a <= b || abs(b - a) <= eps;
}
bool gt(ldouble a, ldouble b)
{
  return a > b && !(abs(b - a) <= eps);
}

const int maxN = 2e3; int n, a;
struct Fish
{
  int w, x, v;
  void read() { scanf("%d %d %d", &w, &x, &v); }
};
Fish fishes[maxN];
pair<ldouble, int> now[maxN];

int eval(ldouble t)
{
  for (int i = 0; i < n; ++i)
    now[i] = {fishes[i].x + t*fishes[i].v, fishes[i].w};
  sort(now, now+n);

  deque<int> has; int total = 0, ans = 0;
  ldouble lo = now[0].first, hi = now[0].first + a;
  for (int i = 0; i < n; ++i)
  {
    has.push_back(i);
    total += now[i].second;
    while (has.size() >= 2 && gt(now[has.back()].first - now[has[0]].first, a))
    {
      total -= now[has[0]].second;
      has.pop_front();
    }
    ans = max(ans, total);
  }
  return ans;
}

ldouble maxTime()
{
  ldouble ans = 0;
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
    {
      int x0 = fishes[i].x, v0 = fishes[i].v;
      int x1 = fishes[j].x, v1 = fishes[j].v;
      if (v0 == v1) continue;
      if (v0 < v1) swap(x0, x1), swap(v0, v1);
      // v0 > v1
      // x0 + v0*t = x1 + v1*t
      // (v0 - v1)*t = x1 - x0
      // t = (x1 - x0) / (v0 - v1)
      ans = max(ans, (ldouble)(x1 - x0) / (v0 - v1));
    }
  DEBUG printf("\tmax t = %lf\n", ans);
  return ans;
}

int ternarySearch1(ldouble lo = 0, ldouble hi = maxTime())
{
  while (abs(hi - lo) > 1e-6)
  {
    ldouble midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    ldouble elo = eval(midlo), ehi = eval(midhi);
    if (elo > ehi) hi = midhi;
    else lo = midlo;
  }
  DEBUG printf("\tt = %lf\n", lo);
  return max({eval(lo), eval(hi), eval((lo + hi) / 2)});
}

int ternarySearch2(ldouble lo = 0, ldouble hi = maxTime())
{
  while (abs(hi - lo) > 1e-6)
  {
    ldouble midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    ldouble elo = eval(midlo), ehi = eval(midhi);
    if (elo < ehi) lo = midlo;
    else hi = midhi;
  }
  DEBUG printf("\tt = %lf\n", lo);
  return max({eval(lo), eval(hi), eval((lo + hi) / 2)});
}

int main()
{
  while (~scanf("%d %d", &n, &a))
  {
    for (int i = 0; i < n; ++i)
      fishes[i].read();

    // ldouble maxT = maxTime();
    int ans = max(ternarySearch1(), ternarySearch2());
    // for (int d = 1; d <= 100; ++d)
    // {
    //   ldouble flo = maxT * (ldouble)(d - 1) / 100;
    //   ldouble fhi = maxT * (ldouble)d / 100;
    //   ans = max({ans, ternarySearch1(flo, fhi), ternarySearch2(flo, fhi)});
    // }
    printf("%d\n", ans);
  }
  return 0;
}
