#include <bits/stdc++.h>
int n, m, a[1001], b[1001];

void read(int array[], int size)
{
  for (int i = 0; i < size; i ++) scanf("%d", &array[i]);
  array[size] = array[0];
}

int eval(double fuel)
{
  for (int i = 0; i < n; i ++)
  {
    fuel -= (m + fuel) / a[i];
    fuel -= (m + fuel) / b[(i + 1) % n];
  }
  return(fuel >= 0);
}

double binSearch(double lo, double hi)
{
  if (lo >= hi - 1e-7) return(round(lo * 1e6) / 1e6);
  double mid = (lo + hi) / 2;
  if (eval(mid)) return(binSearch(lo, mid));
  return(binSearch(mid, hi));
}

int main()
{
  scanf("%d %d", &n, &m);
  read(a, n); read(b, n);

  double ans = binSearch(0, 1e9 + 1);
  if (ans > 1e9)
    printf("-1\n");
  else
    printf("%.10lf\n", ans);

  return(0);
}
