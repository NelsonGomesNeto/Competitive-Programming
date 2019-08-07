#include <bits/stdc++.h>
using namespace std;
double x; int n;

double pot(double a, int y)
{
  if (!y) return(1);
  double ret = pot(a, y >> 1);
  ret *= ret; if (y & 1) ret *= a;
  return(ret);
}

double binSearch(double lo, double hi)
{
  if (lo >= hi - 1e-6) return(lo);
  double mid = (lo + hi) / 2;
  double a = pot(mid, n);
  if (a > x) return(binSearch(lo, mid));
  return(binSearch(mid, hi));
}

int main()
{
  while (scanf("%lf %d", &x, &n) != EOF)
    printf("%.4g^(1/%d) = %.4g (%.4g)\n", x, n, pow(x, 1.0/n), binSearch(0, max(x, 1.0)));
  return(0);
}
