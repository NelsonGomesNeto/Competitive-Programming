#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const ldouble eps = 1e-7;
const int maxN = 1e5;
int n, k;
int a[maxN];

ldouble f(ldouble x)
{
  return x - x*k / 100;
}
bool can(ldouble v)
{
  ldouble backup = 0;
  for (int i = 0; i < n; ++i)
  {
    if (a[i] > v) backup += f(a[i] - v);
    else if (v - a[i] > backup) return false;
    else backup -= v - a[i];
  }
  return true;
}
ldouble binarySearch(ldouble lo = 0, ldouble hi = 1e3)
{
  while (abs(hi - lo) > eps)
  {
    ldouble mid = (lo + hi) / 2;
    if (can(mid)) lo = mid;
    else hi = mid;
  }
  return (hi + lo) / 2;
}

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &a[i]);
    sort(a, a+n);
    reverse(a, a+n);

    ldouble ans = binarySearch();
    printf("%.3Lf\n", ans);
  }
  return 0;
}
