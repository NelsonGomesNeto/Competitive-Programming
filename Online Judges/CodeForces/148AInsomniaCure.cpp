#include <bits/stdc++.h>

int main()
{
  int k, l, m, n, d; scanf("%d %d %d %d %d", &k, &l, &m, &n, &d);
  int total = 0;
  for (int i = 1; i <= d; i ++) total += (i % k == 0) || (i % l == 0) || (i % m == 0) || (i % n == 0);
  printf("%d\n", total);
  return(0);
}