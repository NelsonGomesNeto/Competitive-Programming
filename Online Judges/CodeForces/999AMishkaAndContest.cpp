#include <bits/stdc++.h>

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  int problem[n], sol = 0, at;
  for (int i = 0; i < n; i ++) scanf("%d", &problem[i]);
  for (int i = 0; i < n; i ++)
  {
    if (problem[i] > k) break;
    at = i;
    sol ++;
  }
  for (int i = n - 1; i >= 0; i --)
  {
    if (i == at || problem[i] > k) break;
    sol ++;
  }
  printf("%d\n", sol);
  return(0);
}