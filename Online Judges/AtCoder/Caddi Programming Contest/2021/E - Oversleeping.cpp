#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
(2x + 2y)n + x <= t < (2x + 2y)n + x + y
  range = y (max 500)
(p + q)n + p <= t < (p + q)(n + 1)
  range = q (max 500)

try all combinations of mod (500^2)

t - (2x + 2y)n - x == remY
t - (2x + 2y)n = remY + x
t = remY + x + (2x + 2y)n1

t - (p + q)n - p == remQ
t - (p + q)n = remQ + p
t = remQ + p + (p + q)n2

remQ + p + (p + q)n2 = remY + x + (2x + 2y)n1
(p + q)n2 - (2x + 2y)n1 = remY + x - remQ - p

*/

lli gcd(lli a, lli b, lli& x, lli& y)
{
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  lli x1, y1;
  lli d = gcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

bool find_any_solution(lli a, lli b, lli c, lli &x0, lli &y0, lli &g)
{
  g = gcd(abs(a), abs(b), x0, y0);
  if (c % g) {
    return false;
  }

  x0 *= c / g;
  y0 *= c / g;
  if (a < 0) x0 = -x0;
  if (b < 0) y0 = -y0;
  return true;
}

const lli inf = LONG_LONG_MAX;
lli x, y, p, q;

lli eval(lli remQ, lli p, lli q, lli y0, lli a, lli g, lli mid)
{
  if (LONG_LONG_MAX / (a / g) < mid || ((y0 + mid*(a / g)) != 0 && LONG_LONG_MAX / (p + q) < abs(y0 + mid*(a / g))))
    return inf;
  return remQ + p + (p + q)*(y0 + mid*(a / g));
}
lli findMinSolution(lli remY, lli remQ)
{
  // t - (2x + 2y)n - x == remY
  // t - (2x + 2y)n = remY + x
  // t = remY + x + (2x + 2y)x0

  // t - (p + q)n - p == remQ
  // t - (p + q)n = remQ + p
  // t = remQ + p + (p + q)y0

  // remQ + p + (p + q)y0 = remY + x + (2x + 2y)x0
  // -(2x + 2y)x0 + (p + q)y0 = remY + x - remQ - p
  lli x0, y0, g;
  lli a = -(2*x + 2*y), b = p + q, c = remY + x - remQ - p;
  if (find_any_solution(a, b, c, x0, y0, g))
  {
    lli t1 = remY + x + (2*x + 2*y)*x0, t2 = remQ + p + (p + q)*y0;
    bool isNegative = a / g < 0;

    double target = (double)-(y0 + (remQ + p) / (p + q)) / (a / g);
    lli k = round(target);
    DEBUG printf("\t%lld %lld %lld || %lld %lld\n", remY, remQ, k, t1, t2);
    t2 = inf;
    for (lli kk = k - 2; kk <= k + 2; kk++)
    {
      lli aux = remQ + p + (p + q)*(y0 + kk * (a / g));
      if (aux >= 0)
        t2 = min(t2, aux);
    }
    return t2;
  }
  else
    return inf;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %lld %lld %lld", &x, &y, &p, &q);
    lli ans = inf;
    for (int i = 0; i < y; i++)
      for (int j = 0; j < q; j++)
        ans = min(ans, findMinSolution(i, j));

    if (ans == inf) printf("infinity\n");
    else printf("%lld\n", ans);
  }

  return 0;
}