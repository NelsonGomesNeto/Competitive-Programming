#include <bits/stdc++.h>
char a[(int) 1e5 + 1], b[(int) 1e4 + 1];

int eval(int p)
{
  int i, j, k;
  for (i = 0, j = 0; b[i] && a[j]; i ++)
  {
    for (k = 0; k < p && a[j]; k ++, j ++)
      while (a[j] && a[j] != b[i]) j ++;
    if (k < p || (!a[j] && b[i])) return(0);
  }
  return(!b[i]);
}

int binSearch(int lo, int hi)
{
  if (lo >= hi - 1) return(eval(hi) ? hi : lo);
  int mid = (lo + hi) / 2;
  if (!eval(mid)) return(binSearch(lo, mid - 1));
  return(binSearch(mid, hi));
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));
    scanf("\n%s\n%s", a, b);

    int ans = binSearch(0, 1e5 + 1);
    printf("%d\n", ans);
  }
  return(0);
}