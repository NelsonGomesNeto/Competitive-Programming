#include <bits/stdc++.h>
int n, m, a[101], x;

int eval(int days)
{
  int people = 0;
  for (int i = 0; i < 101; i ++)
    people += a[i] / days;
  return(people >= n);
}

int upperBound(int lo, int hi)
{
  if (lo >= hi) return(lo);
  int mid = (lo + hi) / 2 + ((lo + hi) & 1);
  if (eval(mid)) return(upperBound(mid, hi));
  return(upperBound(lo, mid - 1));
}

int main()
{
  scanf("%d %d", &n, &m);
  memset(a, 0, sizeof(a));
  for (int i = 0; i < m; i ++)
  {
    scanf("%d", &x);
    a[x] ++;
  }

  int ans = upperBound(0, 1000);
  printf("%d\n", ans);

  return(0);
}
