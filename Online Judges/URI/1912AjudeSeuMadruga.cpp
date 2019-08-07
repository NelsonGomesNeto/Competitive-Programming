#include <bits/stdc++.h>
int n, a;

double eval(int c[], double h)
{
  double area = 0;
  for (int i = 0; i < n; i ++)
    area += h < c[i] ? c[i] - h : 0;
  return(area);
}

double binSearch(int c[], double lo, double hi)
{
  if (lo >= hi - 1e-6) return(round(hi*1e5)/1e5);
  double mid = (hi + lo) / 2;
  // printf("%lf %lf %lf\n", lo, hi, eval(c, mid));
  if (eval(c, mid) <= a) return(binSearch(c, lo, mid));
  return(binSearch(c, mid, hi));
}

int main()
{
  while (scanf("%d %d", &n, &a) && !(!n && !a))
  {
    int c[n]; for (int i = 0; i < n; i ++) scanf("%d", &c[i]);

    double ans = binSearch(c, -1e4, 1e4 + 1);
    if (ans < 0) printf("-.-\n");
    else if (ans == 0) printf(":D\n");
    else printf("%.4lf\n", ans);
  }
  return(0);
}