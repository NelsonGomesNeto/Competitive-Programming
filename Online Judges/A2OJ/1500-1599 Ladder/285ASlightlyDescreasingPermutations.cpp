#include <bits/stdc++.h>

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  int now = n;
  if (k) printf("%d", now --);
  for (int i = 1; i < k; i ++) printf(" %d", now --);
  if (k) printf(" ");
  now = 1;
  for (int i = k; i < n; i ++)
    printf("%d%c", now ++, i < n - 1 ? ' ' : '\0');
  printf("\n");

  return(0);
}