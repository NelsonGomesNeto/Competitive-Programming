#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10; int n;
int a[maxN];

double curr[maxN];
double eval2()
{
  double delta = 0;
  for (int i = 0; i < n; i++)
  {
    double best = 1e9;
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++)
        best = min(best, curr[j] - curr[k]);
    delta += best;
  }
  return delta;
}
double ternarySearch(int i);
double eval(int i, double x)
{
  curr[i] = x;
  if (i == n - 1) return eval2();
  else return ternarySearch(i + 1);
}
double ternarySearch(int i = 0)
{
  double lo = -1e5, hi = 1e5;
  while (abs(hi - lo) > 1)
  {
    double midlo = (2*lo + hi) / 3, midhi = (lo + 2*hi) / 3;
    if (eval(i, midlo) < eval(i, midhi)) hi = midhi;
    else lo = midlo;
  }
  double mid = (lo + hi) / 2;
  return eval(i, mid);
}

int main()
{
  int q; scanf("%d", &q);
  for (int tt = 1; tt <= q; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    double ans = ternarySearch();
  }
  return 0;
}
